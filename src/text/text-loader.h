#ifndef TXTLOADER
#define TXTLOADER

#include "types.h"
#include "game/ingame_menu.h"
#include "pc/fs/fs.h"

extern char* currentLanguage;
extern u8 languagesAmount;

extern struct DialogEntry* * dialogPool;
extern u8* * seg2_course_name_table;
extern u8* * seg2_act_name_table;
extern struct LanguageEntry* * languages;

struct StringTable {
    char* key;
    u8* value;
};

struct LanguageEntry {
    char * name;
    char * logo;
    struct DialogEntry* * dialogs;
    struct StringTable* * strings;
    int num_strings;
    u8* * courses;
    u8* * acts;
};

extern u8* get_key_string(char* id);
extern struct LanguageEntry* get_language_by_name(char* name);
extern struct LanguageEntry* get_language();
extern void set_language(struct LanguageEntry* new_language);
extern void alloc_dialog_pool(char* exePath, char* gamedir);
extern void dealloc_dialog_pool(void);
#endif
