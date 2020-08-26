#ifndef _ULTRA64_TIME_H_
#define _ULTRA64_TIME_H_

#include <PR/ultratypes.h>
#include <PR/os_message.h>

/* Types */

typedef struct OSTimer_str
{
    struct OSTimer_str *next;
    struct OSTimer_str *prev;
    u64 interval;
    u64 remaining;
    OSMesgQueue *mq;
    OSMesg *msg;
} OSTimer;

#ifndef __WIIU__
typedef u64 OSTime;
#endif

/* Functions */

OSTime osGetTime(void);
void osSetTime(OSTime time);
u32 osSetTimer(OSTimer *, OSTime, u64, OSMesgQueue *, OSMesg);

#endif
