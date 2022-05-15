#include "text-loader.h"
#include "txtconv.h"
#include <stdio.h>
#include <string.h>
#include "dialog_ids.h"
#include <limits.h>
#include "libs/io_utils.h"
#include <stdlib.h>
#include <dirent.h>
#include "libs/cJSON.h"
#include "pc/configfile.h"
#include "audio_defines.h"

struct LanguageEntry **languages = NULL;

struct LanguageEntry *current_language = NULL;
struct DialogEntry **dialogPool = NULL;
u8 **seg2_course_name_table = NULL;
u8 **seg2_act_name_table = NULL;

#define cJSON_ArrayForEachElement(element, array) const cJSON *element = NULL; cJSON_ArrayForEach(element, array)

static char *strmakecopy(const char *str) {
    char *s = calloc(strlen(str) + 1, sizeof(char));
    memcpy(s, str, strlen(str) + 1);
    return s;
}

static u32 parse_sound_param(const char *str) {
    u32 a0 = 0, a1 = 0, a2 = 0, a3 = 0, a4 = 0;
    sscanf(str, "%u, %u, %X, %X, %u", &a0, &a1, &a2, &a3, &a4);
    return SOUND_ARG_LOAD(a0, a1, a2, a3, a4);
}

static int get_index_first_null(void **arrayOfPtrs) {
    for (int i = 0;; ++i) {
        if (!arrayOfPtrs[i]) {
            return i;
        }
    }
    return 0;
}

struct StringTable *get_pair_from_key(struct LanguageEntry *lang, const char *key) {
    for (int i = 0; i < lang->num_strings; i++) {
        struct StringTable *str = lang->strings[i];
        if (strcmp(str->key, key) == 0) {
            return str;
        }
    }
    return NULL;
}

static void add_language(struct LanguageEntry *lang) {
    for (int i = 0;; ++i) {
        if (languages[i] == NULL) {
            languages[i] = lang;
            return;
        }
    }
}

static void load_language(char *jsonTxt) {

    // Parsing
    const char *endTxt;
    cJSON *json = cJSON_ParseWithOpts(jsonTxt, &endTxt, 1);
    if (*endTxt != 0) {
        fprintf(stderr, "Loading File: Error before: %s\n", endTxt);
        exit(1);
    }

    // Sections
    const cJSON *manifest = cJSON_GetObjectItemCaseSensitive(json, "manifest");
    const cJSON *dialogs = cJSON_GetObjectItemCaseSensitive(json, "dialogs");
    const cJSON *courses = cJSON_GetObjectItemCaseSensitive(json, "courses");
    const cJSON *secrets = cJSON_GetObjectItemCaseSensitive(json, "secrets");
    const cJSON *options = cJSON_GetObjectItemCaseSensitive(json, "options");
    const cJSON *strings = cJSON_GetObjectItemCaseSensitive(json, "strings");

    // Language identification
    char *langName = cJSON_GetObjectItemCaseSensitive(manifest, "langName")->valuestring;
    char *langLogo = cJSON_GetObjectItemCaseSensitive(manifest, "langLogo")->valuestring;
    struct LanguageEntry *lang = get_language_by_name(langName);
    if (!lang) {
        lang = (struct LanguageEntry *) calloc(1, sizeof(struct LanguageEntry));
        add_language(lang);
    }
    if (!lang->name) {
        lang->name = strmakecopy(langName);
    }
    if (!lang->logo) {
        lang->logo = strmakecopy(langLogo);
    }

    // Dialogs
    if (!lang->dialogs) {
        lang->dialogs = (struct DialogEntry **) calloc(256, sizeof(struct DialogEntry *));
    }
    char *dialogBuffer = calloc(0x10000, sizeof(char));
    cJSON_ArrayForEachElement(dialog, dialogs) {

        // Dialog identification
        int id = cJSON_GetObjectItemCaseSensitive(dialog, "ID")->valueint;
        if (id >= 256) {
            continue;
        }

        struct DialogEntry *dialogEntry = lang->dialogs[id];
        if (!dialogEntry) {
            dialogEntry = (struct DialogEntry *) calloc(1, sizeof(struct DialogEntry));
            lang->dialogs[id] = dialogEntry;
        }

        // Dialog params
        dialogEntry->linesPerBox = cJSON_GetObjectItemCaseSensitive(dialog, "linesPerBox")->valueint;
        dialogEntry->leftOffset = cJSON_GetObjectItemCaseSensitive(dialog, "leftOffset")->valueint;
        dialogEntry->width = cJSON_GetObjectItemCaseSensitive(dialog, "width")->valueint;

        // Dialog sound
        const cJSON *soundParam = cJSON_GetObjectItemCaseSensitive(dialog, "sound");
        if (soundParam) {
            dialogEntry->unused = parse_sound_param(cJSON_GetObjectItemCaseSensitive(dialog, "sound")->valuestring);
        } else {
            dialogEntry->unused = 1;
        }

        // Dialog lines
        const cJSON *lines = cJSON_GetObjectItemCaseSensitive(dialog, "lines");
        dialogBuffer[0] = 0;
        cJSON_ArrayForEachElement(line, lines) {
            char *str = line->valuestring;
            strcat(dialogBuffer, str);
            strcat(dialogBuffer, "\n");
        }
        dialogBuffer[strlen(dialogBuffer) - 1] = 0;

        // Replace the existing dialog by the new one
        if (dialogEntry->str) {
            free((u8 *) dialogEntry->str);
        }
        dialogEntry->str = getTranslatedText(dialogBuffer);
    }
    free(dialogBuffer);

    // Course name table
    // Course acts table
    if (!lang->courses) {
        lang->courses = (u8 **) calloc(64, sizeof(u8 *));
    }
    if (!lang->acts) {
        lang->acts = (u8 **) calloc(256, sizeof(u8 *));
    }
    int courseIdx = get_index_first_null((void **) lang->courses);
    int actIdx = get_index_first_null((void **) lang->acts);
    cJSON_ArrayForEachElement(course, courses) {

        // Course name
        // Don't add "CASTLE" to the course name table
        if (course->next != NULL) {
            char *courseName = cJSON_GetObjectItemCaseSensitive(course, "course")->valuestring;
            lang->courses[courseIdx++] = getTranslatedText(courseName);
        }

        // Course acts
        const cJSON *acts = cJSON_GetObjectItemCaseSensitive(course, "acts");
        cJSON_ArrayForEachElement(act, acts) {
            char *actName = act->valuestring;
            lang->acts[actIdx++] = getTranslatedText(actName);
        }
    }

    // Secret courses
    cJSON_ArrayForEachElement(secret, secrets) {

        // There must be an empty string between "THE SECRET AQUARIUM" and "CASTLE SECRET STARS"
        if (courseIdx == 24) {
            lang->courses[courseIdx++] = getTranslatedText("");
        }

        char *secretName = secret->valuestring;
        lang->courses[courseIdx++] = getTranslatedText(secretName);
    }

    // Strings (options, common text...)
    // Those are key/value pairs, and each key is unique
    // If a key already exists, its value is replaced by the new one
    cJSON_ArrayForEachElement(option, options) {
        add_key_value_string(lang, option->string, option->valuestring);
    }
    cJSON_ArrayForEachElement(str, strings) {
        add_key_value_string(lang, str->string, str->valuestring);
    }

    cJSON_Delete(json);
}

static void alloc_languages(char *exePath, char *gameDir) {
    if (!languages) {
        languages = (struct LanguageEntry **) calloc(32, sizeof(struct LanguageEntry *));
    }

    // Executable directory
    char exeDir[FILENAME_MAX];
    snprintf(exeDir, FILENAME_MAX, "%s", exePath);
    char *lastSlash = MAX(strrchr(exeDir, '\\'), strrchr(exeDir, '/'));
    if (lastSlash) *lastSlash = 0;

    // Languages directory
    char languagesDir[FILENAME_MAX];
    snprintf(languagesDir, FILENAME_MAX, "%s/%s/texts/", exeDir, gameDir);

    // Scan directory for JSON files
    DIR *dir = opendir(languagesDir);
    if (dir) {
        struct dirent *de;
        while ((de = readdir(dir)) != NULL) {
            const char *extension = get_filename_ext(de->d_name);
            if (strcmp(extension, "json") == 0) {

                // Load JSON
                char filename[FILENAME_MAX];
                snprintf(filename, FILENAME_MAX, "%s%s", languagesDir, de->d_name);
                printf("Loading File: %s\n", filename);
                char *jsonTxt = read_file(filename);
                if (jsonTxt != NULL) {
                    load_language(jsonTxt);
                    free(jsonTxt);
                } else {
                    fprintf(stderr, "Loading File: Error reading '%s'\n", filename);
                    exit(1);
                }
            }
        }
        closedir(dir);
    }

    // Abort if no file loaded
    if (!languages[0]) {
        fprintf(stderr, "Loading File: No language files found, aborting.\n");
        exit(1);
    }
}

struct LanguageEntry *get_language_by_name(char *name) {
    for (int i = 0; languages[i] != NULL; i++) {
        if (strcmp(languages[i]->name, name) == 0) {
            return languages[i];
        }
    }
    return NULL;
}

struct LanguageEntry *get_language() {
    return current_language;
}

void set_language(struct LanguageEntry *new_language) {
    current_language = new_language;
    dialogPool = new_language->dialogs;
    seg2_act_name_table = new_language->acts;
    seg2_course_name_table = new_language->courses;
}

u8 *get_key_string(const char *id) {
    for (int i = 0; i < current_language->num_strings; i++) {
        struct StringTable *str = current_language->strings[i];
        if (strcmp(str->key, id) == 0) {
            return str->value;
        }
    }
    if (!current_language->none) {
        current_language->none = getTranslatedText("NONE");
    }
    return current_language->none;
}

void add_key_value_string(struct LanguageEntry *lang, const char *key, const char *value) {

    // String identification
    struct StringTable *entry = get_pair_from_key(lang, key);
    if (!entry) {
        entry = (struct StringTable *) calloc(1, sizeof(struct StringTable));
        entry->key = strmakecopy(key);
        lang->strings = (struct StringTable **) realloc(lang->strings, (lang->num_strings + 1) * sizeof(struct StringTable *));
        lang->strings[lang->num_strings++] = entry;
    }

    // Value
    if (entry->value) {
        free(entry->value);
    }
    entry->value = getTranslatedText((char *) value);
}

void load_language_file(const char *filename) {
    if (!languages) {
        languages = (struct LanguageEntry **) calloc(32, sizeof(struct LanguageEntry *));
    }

    // Load JSON
    printf("Loading File: %s\n", filename);
    char *jsonTxt = read_file((char *) filename);
    if (jsonTxt != NULL) {
        load_language(jsonTxt);
        free(jsonTxt);
    } else {
        fprintf(stderr, "Loading File: Error reading '%s'\n", filename);
        exit(1);
    }
}

void alloc_dialog_pool(char *exePath, char *gamedir) {
    alloc_languages(exePath, gamedir);
    if ((int) configLanguage >= get_num_languages()) {
        printf("Loading File: Configured language doesn't exist, resetting to defaults.\n");
        configLanguage = 0;
    }
    set_language(languages[configLanguage]);
}

void dealloc_dialog_pool(void) {
    int numLanguages = get_num_languages();
    for (int l = 0; l < numLanguages; l++) {
        struct LanguageEntry *entry = languages[l];
        
        // Strings
        for (int i = 0; i < entry->num_strings; i++) {
            free(entry->strings[i]);
        }
        free(entry->strings);

        // Acts
        for (int i = 0; entry->acts[i] != NULL; i++) {
            free(entry->acts[i]);
        }
        free(entry->acts);

        // Courses
        for (int i = 0; entry->courses[i] != NULL; i++) {
            free(entry->courses[i]);
        }
        free(entry->courses);

        // Dialogs
        for (int i = 0; i < 256; i++) {
            if (entry->dialogs[i]) {
                free(entry->dialogs[i]);
            }
        }
        free(entry->dialogs);

        // Language
        free(entry->logo);
        free(entry->name);
        free(languages[l]); 
    }
    free(languages);
}

int get_num_languages() {
    for (int i = 0;; ++i) {
        if (!languages[i]) {
            return i;
        }
    }
    return 0;
}
