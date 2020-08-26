#include "libultra_internal.h"

OSPri osGetThreadPri(N64_OSThread *thread) {
    if (thread == NULL) {
        thread = D_803348A0;
    }
    return thread->priority;
}
