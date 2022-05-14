#include "libultra_internal.h"

void guPerspectiveF(float mf[4][4], u16 *perspNorm, float fovy, float aspect, float near, float far,
                    float scale) {
    float yscale;
#ifndef TARGET_WII_U
    int row;
    int col;
#endif // TARGET_WII_U
    guMtxIdentF(mf);
    fovy *= GU_PI / 180.0;
    yscale = cosf(fovy / 2) / sinf(fovy / 2);
    mf[0][0] = yscale / aspect;
    mf[1][1] = yscale;
    mf[2][2] = (near + far) / (near - far);
    mf[2][3] = -1;
    mf[3][2] = 2 * near * far / (near - far);
    mf[3][3] = 0.0f;
#ifdef TARGET_WII_U
    f32* const pDst = &(mf[0][0]);

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
            mf[row][col] *= scale;
        }
    }
#endif // TARGET_WII_U
    if (perspNorm != NULL) {
        if (near + far <= 2.0) {
            *perspNorm = 65535;
        } else {
            *perspNorm = (double) (1 << 17) / (near + far);
            if (*perspNorm <= 0) {
                *perspNorm = 1;
            }
        }
    }
}
void guPerspective(Mtx *m, u16 *perspNorm, float fovy, float aspect, float near, float far,
                   float scale) {
#if defined(NON_MATCHING) && defined(GBI_FLOATS)
    guPerspectiveF(m->m, perspNorm, fovy, aspect, near, far, scale);
#else
    float mat[4][4];
    guPerspectiveF(mat, perspNorm, fovy, aspect, near, far, scale);
    guMtxF2L(mat, m);
#endif
}
