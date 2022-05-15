#include "libultra_internal.h"

void guOrthoF(float m[4][4], float left, float right, float bottom, float top, float near, float far,
              float scale) {
#ifndef TARGET_WII_U
    int row;
    int col;
#endif // TARGET_WII_U
    guMtxIdentF(m);
    m[0][0] = 2 / (right - left);
    m[1][1] = 2 / (top - bottom);
    m[2][2] = -2 / (far - near);
    m[3][0] = -(right + left) / (right - left);
    m[3][1] = -(top + bottom) / (top - bottom);
    m[3][2] = -(far + near) / (far - near);
    m[3][3] = 1;
#ifdef TARGET_WII_U
    f32* const pDst = &(m[0][0]);

    // Temporary variable
    f32 v0;

    asm volatile ("psq_l  %[v0],  0(%[pDst]), 0, 0" : [v0] "=f"(v0) : [pDst] "b"(pDst));
    asm volatile ("ps_muls0 %[v0], %[v0], %[scale]" : [v0] "+f"(v0) : [scale] "f"(scale));
    asm volatile ("psq_st %[v0],  0(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_l  %[v0],  8(%[pDst]), 0, 0" : [v0] "=f"(v0) : [pDst] "b"(pDst));
    asm volatile ("ps_muls0 %[v0], %[v0], %[scale]" : [v0] "+f"(v0) : [scale] "f"(scale));
    asm volatile ("psq_st %[v0],  8(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");

    asm volatile ("psq_l  %[v0], 16(%[pDst]), 0, 0" : [v0] "=f"(v0) : [pDst] "b"(pDst));
    asm volatile ("ps_muls0 %[v0], %[v0], %[scale]" : [v0] "+f"(v0) : [scale] "f"(scale));
    asm volatile ("psq_st %[v0], 16(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_l  %[v0], 24(%[pDst]), 0, 0" : [v0] "=f"(v0) : [pDst] "b"(pDst));
    asm volatile ("ps_muls0 %[v0], %[v0], %[scale]" : [v0] "+f"(v0) : [scale] "f"(scale));
    asm volatile ("psq_st %[v0], 24(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");

    asm volatile ("psq_l  %[v0], 32(%[pDst]), 0, 0" : [v0] "=f"(v0) : [pDst] "b"(pDst));
    asm volatile ("ps_muls0 %[v0], %[v0], %[scale]" : [v0] "+f"(v0) : [scale] "f"(scale));
    asm volatile ("psq_st %[v0], 32(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_l  %[v0], 40(%[pDst]), 0, 0" : [v0] "=f"(v0) : [pDst] "b"(pDst));
    asm volatile ("ps_muls0 %[v0], %[v0], %[scale]" : [v0] "+f"(v0) : [scale] "f"(scale));
    asm volatile ("psq_st %[v0], 40(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");

    asm volatile ("psq_l  %[v0], 48(%[pDst]), 0, 0" : [v0] "=f"(v0) : [pDst] "b"(pDst));
    asm volatile ("ps_muls0 %[v0], %[v0], %[scale]" : [v0] "+f"(v0) : [scale] "f"(scale));
    asm volatile ("psq_st %[v0], 48(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_l  %[v0], 56(%[pDst]), 0, 0" : [v0] "=f"(v0) : [pDst] "b"(pDst));
    asm volatile ("ps_muls0 %[v0], %[v0], %[scale]" : [v0] "+f"(v0) : [scale] "f"(scale));
    asm volatile ("psq_st %[v0], 56(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
#else
    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            m[row][col] *= scale;
        }
    }
#endif // TARGET_WII_U
}

void guOrtho(Mtx *m, float left, float right, float bottom, float top, float near, float far,
             float scale) {
#if defined(NON_MATCHING) && defined(GBI_FLOATS)
    guOrthoF(m->m, left, right, bottom, top, near, far, scale);
#else
    float sp28[4][4];
    guOrthoF(sp28, left, right, bottom, top, near, far, scale);
    guMtxF2L(sp28, m);
#endif
}
