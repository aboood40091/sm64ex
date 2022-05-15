#ifndef _ULTRA64_H_
#define _ULTRA64_H_

#include <math.h>

#ifndef WII_U_FAST_SQRT
#define WII_U_FAST_SQRT

#ifdef TARGET_WII_U

static __attribute__((always_inline)) inline
float rsqrtf(float x)
{
    // Optimized, inline assembly version

    if (x <= 0.0f)
        return 0.0f;

    // Temporary registers
    float v0;
    float v1;
    float v2;

    // Constants
    const float HALF  = 0.5f;
    const float THREE = 3.0f;

    asm ("frsqrte %[v0], %[x]                 " : [v0] "=f"(v0) : [ x] "f"( x));
    asm ("fmuls   %[v1], %[v0], %[v0]         " : [v1] "=f"(v1) : [v0] "f"(v0));
    asm ("fmuls   %[v2], %[v0], %[HALF]       " : [v2] "=f"(v2) : [v0] "f"(v0), [ HALF] "f"( HALF));
    asm ("fnmsubs %[v1], %[v1], %[x], %[THREE]" : [v1] "+f"(v1) : [ x] "f"( x), [THREE] "f"(THREE));
    asm ("fmuls   %[v0], %[v1], %[v2]         " : [v0] "=f"(v0) : [v1] "f"(v1), [   v2] "f"(   v2));

    return v0;
}

static __attribute__((always_inline)) inline
float fast_sqrtf(float x)
{
    return rsqrtf(x) * x;
}

#define sqrtf fast_sqrtf

#else

static inline
float rsqrtf(float x)
{
    return 1.0 / sqrtf(x);
}

#endif // TARGET_WII_U

#endif // WII_U_FAST_SQRT

#ifndef _LANGUAGE_C
#define _LANGUAGE_C
#endif

#include <PR/ultratypes.h>
#include <PR/os_exception.h>
#include <PR/os_misc.h>
#include <PR/os_rdp.h>
#include <PR/os_thread.h>
#include <PR/os_time.h>
#include <PR/os_message.h>
#include <PR/os_cont.h>
#include <PR/os_tlb.h>
#include <PR/sptask.h>
#include <PR/ucode.h>
#include <PR/os_cache.h>
#include <PR/os_vi.h>
#include <PR/os_pi.h>
#include <PR/os_internal.h>
#include <PR/mbi.h>
#include <PR/os_eeprom.h>
#include <PR/os_libc.h>
#include <PR/gu.h>
#include <PR/os_ai.h>
#include <PR/libaudio.h>
#include <PR/libultra.h>

#if defined(__MINGW32__)
#include <_mingw.h>
#if !defined(__MINGW64_VERSION_MAJOR)
#include <string.h>
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)
#define bcopy(s1, s2, n) memmove((s2), (s1), (n))
#endif
#endif

#endif
