#ifndef MATH_H
#define MATH_H

#define M_PI 3.14159265358979323846

float sinf(float);
double sin(double);
float cosf(float);
double cos(double);

float sqrtf(float);

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

#endif
