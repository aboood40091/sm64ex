#include "libultra_internal.h"

// these don't feel like they belong here
// but it makes the most logical since there was printf data before
#ifndef AVOID_UB
N64_OSThread *D_80334890 = NULL;
u32 D_80334894 = -1;
N64_OSThread *D_80334898 = (N64_OSThread *) &D_80334890;
N64_OSThread *D_8033489C = (N64_OSThread *) &D_80334890;
N64_OSThread *D_803348A0 = NULL;
u32 D_803348A4 = 0; // UNKNOWN
#else
OSThread_ListHead D_80334890_fix = {NULL, -1, (N64_OSThread *) &D_80334890_fix, (N64_OSThread *) &D_80334890_fix, NULL, 0};
#endif

void __osDequeueThread(N64_OSThread **queue, N64_OSThread *thread) {
    register N64_OSThread **a2;
    register N64_OSThread *a3;
    a2 = queue;
    a3 = *a2;
    while (a3 != NULL) {
        if (a3 == thread) {
            *a2 = thread->next;
            return;
        }
        a2 = &a3->next;
        a3 = *a2;
    }
}
