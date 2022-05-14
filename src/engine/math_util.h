#ifndef MATH_UTIL_H
#define MATH_UTIL_H

#include <PR/ultratypes.h>

#include "types.h"

/*
 * The sine and cosine tables overlap, but "#define gCosineTable (gSineTable +
 * 0x400)" doesn't give expected codegen; gSineTable and gCosineTable need to
 * be different symbols for code to match. Most likely the tables were placed
 * adjacent to each other, and gSineTable cut short, such that reads overflow
 * into gCosineTable.
 *
 * These kinds of out of bounds reads are undefined behavior, and break on
 * e.g. GCC (which doesn't place the tables next to each other, and probably
 * exploits array sizes for range analysis-based optimizations as well).
 * Thus, for non-IDO compilers we use the standard-compliant version.
 */
extern f32 gSineTable[];
#ifdef AVOID_UB
#define gCosineTable (gSineTable + 0x400)
#else
extern f32 gCosineTable[];
#endif

#define sins(x) gSineTable[(u16) (x) >> 4]
#define coss(x) gCosineTable[(u16) (x) >> 4]

#define min(a, b) ((a) <= (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

#define sqr(x) ((x) * (x))

#define absx(x) ((x) < 0 ? -(x) : (x))

#include "../../include/libc/stdlib.h"

#ifdef NON_MATCHING
#include "math_util.inline.h"
#endif // NON_MATCHING

f32 atan2f(f32 a, f32 b);
void spline_get_weights(Vec4f result, f32 t, UNUSED s32 c);
void anim_spline_init(Vec4s *keyFrames);
s32 anim_spline_poll(Vec3f result);

#endif // MATH_UTIL_H
