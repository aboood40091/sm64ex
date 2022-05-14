#include "surface_collision.h"

#ifdef NON_MATCHING
#define MATH_DO_INLINE static __attribute__((always_inline)) inline
#else
#define MATH_DO_INLINE
#endif // NON_MATCHING

MATH_DO_INLINE void *vec3f_copy(Vec3f dest, Vec3f src);
MATH_DO_INLINE void *vec3f_set(Vec3f dest, f32 x, f32 y, f32 z);
MATH_DO_INLINE void *vec3f_add(Vec3f dest, Vec3f a);
MATH_DO_INLINE void *vec3f_sum(Vec3f dest, Vec3f a, Vec3f b);
MATH_DO_INLINE void *vec3f_dif(Vec3f dest, Vec3f a, Vec3f b);
MATH_DO_INLINE void *vec3f_mul(Vec3f dest, f32 a);
MATH_DO_INLINE void *vec3s_copy(Vec3s dest, Vec3s src);
MATH_DO_INLINE void *vec3s_set(Vec3s dest, s16 x, s16 y, s16 z);
MATH_DO_INLINE void *vec3s_add(Vec3s dest, Vec3s a);
MATH_DO_INLINE void *vec3s_sum(Vec3s dest, Vec3s a, Vec3s b);
MATH_DO_INLINE void *vec3s_sub(Vec3s dest, Vec3s a);
MATH_DO_INLINE void *vec3s_to_vec3f(Vec3f dest, Vec3s a);
MATH_DO_INLINE void *vec3f_to_vec3s(Vec3s dest, Vec3f a);
MATH_DO_INLINE void *find_vector_perpendicular_to_plane(Vec3f dest, Vec3f a, Vec3f b, Vec3f c);
MATH_DO_INLINE void *vec3f_cross(Vec3f dest, Vec3f a, Vec3f b);
MATH_DO_INLINE void *vec3f_normalize(Vec3f dest);
MATH_DO_INLINE f32 vec3f_length(Vec3f a);
MATH_DO_INLINE f32 vec3f_dot(Vec3f a, Vec3f b);
MATH_DO_INLINE void mtxf_copy(Mat4 dest, Mat4 src);
MATH_DO_INLINE void mtxf_identity(Mat4 mtx);
MATH_DO_INLINE void mtxf_translate(Mat4 dest, Vec3f b);
MATH_DO_INLINE void mtxf_lookat(Mat4 mtx, Vec3f from, Vec3f to, s16 roll);
MATH_DO_INLINE void mtxf_rotate_zxy_and_translate(Mat4 dest, Vec3f translate, Vec3s rotate);
MATH_DO_INLINE void mtxf_rotate_xyz_and_translate(Mat4 dest, Vec3f b, Vec3s c);
MATH_DO_INLINE void mtxf_billboard(Mat4 dest, Mat4 mtx, Vec3f position, s16 angle);
MATH_DO_INLINE void mtxf_cylboard(Mat4 dest, Mat4 mtx, Vec3f position, s16 angle);
MATH_DO_INLINE void mtxf_align_terrain_normal(Mat4 dest, Vec3f upDir, Vec3f pos, s16 yaw);
MATH_DO_INLINE void mtxf_align_terrain_triangle(Mat4 mtx, Vec3f pos, s16 yaw, f32 radius);
MATH_DO_INLINE void mtxf_mul(Mat4 dest, Mat4 a, Mat4 b);
MATH_DO_INLINE void mtxf_scale_vec3f(Mat4 dest, Mat4 mtx, Vec3f s);
MATH_DO_INLINE void mtxf_mul_vec3s(Mat4 mtx, Vec3s b);
MATH_DO_INLINE void mtxf_to_mtx(Mtx *dest, Mat4 src);
MATH_DO_INLINE void mtxf_rotate_xy(Mtx *mtx, s16 angle);
MATH_DO_INLINE void get_pos_from_transform_mtx(Vec3f dest, Mat4 objMtx, Mat4 camMtx);
MATH_DO_INLINE void vec3f_get_dist_and_angle(Vec3f from, Vec3f to, f32 *dist, s16 *pitch, s16 *yaw);
MATH_DO_INLINE void vec3f_set_dist_and_angle(Vec3f from, Vec3f to, f32  dist, s16  pitch, s16  yaw);
MATH_DO_INLINE s32 approach_s32(s32 current, s32 target, s32 inc, s32 dec);
MATH_DO_INLINE f32 approach_f32(f32 current, f32 target, f32 inc, f32 dec);
MATH_DO_INLINE s16 atan2s(f32 y, f32 x);

// These functions have bogus return values.
// Disable the compiler warning.
#pragma GCC diagnostic push

#ifdef __GNUC__
#if defined(__clang__)
  #pragma GCC diagnostic ignored "-Wreturn-stack-address"
#else
  #pragma GCC diagnostic ignored "-Wreturn-local-addr"
#endif
#endif

/// Copy vector 'src' to 'dest'
MATH_DO_INLINE void *vec3f_copy(Vec3f dest, Vec3f src) {
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    return &dest; //! warning: function returns address of local variable
}

/// Set vector 'dest' to (x, y, z)
MATH_DO_INLINE void *vec3f_set(Vec3f dest, f32 x, f32 y, f32 z) {
    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
    return &dest; //! warning: function returns address of local variable
}

/// Add vector 'a' to 'dest'
MATH_DO_INLINE void *vec3f_add(Vec3f dest, Vec3f a) {
#ifdef NON_MATCHING
    return vec3f_sum(dest, dest, a);
#else
    dest[0] += a[0];
    dest[1] += a[1];
    dest[2] += a[2];
    return &dest; //! warning: function returns address of local variable
#endif // NON_MATCHING
}

/// Make 'dest' the sum of vectors a and b.
MATH_DO_INLINE void *vec3f_sum(Vec3f dest, Vec3f a, Vec3f b) {
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
    dest[2] = a[2] + b[2];
    return &dest; //! warning: function returns address of local variable
}

/// Make 'dest' the difference of vectors a and b.
MATH_DO_INLINE void *vec3f_dif(Vec3f dest, Vec3f a, Vec3f b) {
    dest[0] = a[0] - b[0];
    dest[1] = a[1] - b[1];
    dest[2] = a[2] - b[2];
    return &dest; //! warning: function returns address of local variable
}

/// Multiply vector 'dest' by a
MATH_DO_INLINE void *vec3f_mul(Vec3f dest, f32 a) {
    dest[0] *= a;
    dest[1] *= a;
    dest[2] *= a;
    return &dest; //! warning: function returns address of local variable
}

/// Copy vector src to dest
MATH_DO_INLINE void *vec3s_copy(Vec3s dest, Vec3s src) {
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    return &dest; //! warning: function returns address of local variable
}

/// Set vector 'dest' to (x, y, z)
MATH_DO_INLINE void *vec3s_set(Vec3s dest, s16 x, s16 y, s16 z) {
    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
    return &dest; //! warning: function returns address of local variable
}

/// Add vector a to 'dest'
MATH_DO_INLINE void *vec3s_add(Vec3s dest, Vec3s a) {
    dest[0] += a[0];
    dest[1] += a[1];
    dest[2] += a[2];
    return &dest; //! warning: function returns address of local variable
}

/// Make 'dest' the sum of vectors a and b.
MATH_DO_INLINE void *vec3s_sum(Vec3s dest, Vec3s a, Vec3s b) {
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
    dest[2] = a[2] + b[2];
    return &dest; //! warning: function returns address of local variable
}

/// Subtract vector a from 'dest'
MATH_DO_INLINE void *vec3s_sub(Vec3s dest, Vec3s a) {
    dest[0] -= a[0];
    dest[1] -= a[1];
    dest[2] -= a[2];
    return &dest; //! warning: function returns address of local variable
}

/// Convert short vector a to float vector 'dest'
MATH_DO_INLINE void *vec3s_to_vec3f(Vec3f dest, Vec3s a) {
#ifdef TARGET_WII_U
    f32*       const pDst = &(dest[0]);
    const s16* const pSrc = &(a[0]);

    // Temporary variable
    f32 v0;

    asm volatile ("psq_l %[v0], 0(%[pSrc]), 0, 5" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
    asm volatile ("psq_st %[v0], 0(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_l %[v0], 4(%[pSrc]), 1, 5" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
    asm volatile ("psq_st %[v0], 8(%[pDst]), 1, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
#else
    dest[0] = a[0];
    dest[1] = a[1];
    dest[2] = a[2];
#endif // TARGET_WII_U
    return &dest; //! warning: function returns address of local variable
}

/**
 * Convert float vector a to a short vector 'dest' by rounding the components
 * to the nearest integer.
 */
MATH_DO_INLINE void *vec3f_to_vec3s(Vec3s dest, Vec3f a) {
#ifdef TARGET_WII_U
    s16*       const pDst = &(dest[0]);
    const f32* const pSrc = &(a[0]);

    // Temporary variable
    f32 v0;

    // TODO: Rounding

    asm volatile ("psq_l %[v0], 0(%[pSrc]), 0, 0" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
    asm volatile ("psq_st %[v0], 0(%[pDst]), 0, 5" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_l %[v0], 8(%[pSrc]), 1, 0" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
    asm volatile ("psq_st %[v0], 4(%[pDst]), 1, 5" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
#else
    // add/subtract 0.5 in order to round to the nearest s32 instead of truncating
    dest[0] = a[0] + ((a[0] > 0) ? 0.5f : -0.5f);
    dest[1] = a[1] + ((a[1] > 0) ? 0.5f : -0.5f);
    dest[2] = a[2] + ((a[2] > 0) ? 0.5f : -0.5f);
#endif // TARGET_WII_U
    return &dest; //! warning: function returns address of local variable
}

/**
 * Set 'dest' the normal vector of a triangle with vertices a, b and c.
 * It is similar to vec3f_cross, but it calculates the vectors (c-b) and (b-a)
 * at the same time.
 */
MATH_DO_INLINE void *find_vector_perpendicular_to_plane(Vec3f dest, Vec3f a, Vec3f b, Vec3f c) {
#ifdef TARGET_WII_U
    f32*       const pDst = &(dest[0]);
    const f32* const pA   = &(a[0]);
    const f32* const pB   = &(b[0]);
    const f32* const pC   = &(c[0]);

    // Temporary variables
    register f32 v0;
    register f32 v1;
    register f32 v2;
    register f32 v3;
    register f32 v4;
    register f32 v5;
    register f32 v6;
    register f32 v7;
    register f32 v8;
    register f32 v9;
    register f32 v10;

    asm volatile ("psq_l      %[v0],  0(%[pA]), 0, 0     " : [v0 ] "=f"(v0 ) : [pA] "b"(pA));
    asm volatile ("psq_l      %[v1],  0(%[pB]), 0, 0     " : [v1 ] "=f"(v1 ) : [pB] "b"(pB));
    asm volatile ("psq_l      %[v4],  0(%[pC]), 0, 0     " : [v4 ] "=f"(v4 ) : [pC] "b"(pC));
    asm volatile ("lfs        %[v2],  8(%[pA])           " : [v2 ] "=f"(v2 ) : [pA] "b"(pA));
    asm volatile ("lfs        %[v3],  8(%[pB])           " : [v3 ] "=f"(v3 ) : [pB] "b"(pB));
    asm volatile ("lfs        %[v5],  8(%[pC])           " : [v5 ] "=f"(v5 ) : [pC] "b"(pC));

    asm volatile ("ps_sub     %[v0],  %[v1], %[v0]       " : [v0 ] "+f"(v0 ) : [v1] "f"(v1));
    asm volatile ("ps_sub     %[v1],  %[v4], %[v1]       " : [v1 ] "+f"(v1 ) : [v4] "f"(v4));
    asm volatile ("fsubs      %[v2],  %[v3], %[v2]       " : [v2 ] "+f"(v2 ) : [v3] "f"(v3));
    asm volatile ("fsubs      %[v3],  %[v5], %[v3]       " : [v3 ] "+f"(v3 ) : [v5] "f"(v5));
    asm volatile ("ps_mul     %[v4],  %[v1], %[v2]       " : [v4 ] "=f"(v4 ) : [v1] "f"(v1), [v2] "f"(v2));
    asm volatile ("ps_msub    %[v5],  %[v0], %[v3], %[v4]" : [v5 ] "=f"(v5 ) : [v0] "f"(v0), [v3] "f"(v3), [v4] "f"(v4));
    asm volatile ("ps_merge10 %[v6],  %[v1], %[v1]       " : [v6 ] "=f"(v6 ) : [v1] "f"(v1));
    asm volatile ("ps_muls0   %[v7],  %[v1], %[v0]       " : [v7 ] "=f"(v7 ) : [v1] "f"(v1), [v0] "f"(v0));
    asm volatile ("ps_msub    %[v8],  %[v0], %[v6], %[v7]" : [v8 ] "=f"(v8 ) : [v0] "f"(v0), [v6] "f"(v6), [v7] "f"(v7));
    asm volatile ("ps_merge11 %[v9],  %[v5], %[v5]       " : [v9 ] "=f"(v9 ) : [v5] "f"(v5));
    asm volatile ("ps_merge01 %[v10], %[v5], %[v8]       " : [v10] "=f"(v10) : [v5] "f"(v5), [v8] "f"(v8));
    asm volatile ("ps_neg     %[v10], %[v10]             " : [v10] "+f"(v10) : );

    asm volatile ("psq_st     %[v9],  0(%[pDst]), 1, 0   " : : [v9 ] "f"(v9 ), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_st     %[v10], 4(%[pDst]), 0, 0   " : : [v10] "f"(v10), [pDst] "b"(pDst) : "memory");
#else
    dest[0] = (b[1] - a[1]) * (c[2] - b[2]) - (c[1] - b[1]) * (b[2] - a[2]);
    dest[1] = (b[2] - a[2]) * (c[0] - b[0]) - (c[2] - b[2]) * (b[0] - a[0]);
    dest[2] = (b[0] - a[0]) * (c[1] - b[1]) - (c[0] - b[0]) * (b[1] - a[1]);
#endif // TARGET_WII_U
    return &dest; //! warning: function returns address of local variable
}

/// Make vector 'dest' the cross product of vectors a and b.
MATH_DO_INLINE void *vec3f_cross(Vec3f dest, Vec3f a, Vec3f b) {
    dest[0] = a[1] * b[2] - b[1] * a[2];
    dest[1] = a[2] * b[0] - b[2] * a[0];
    dest[2] = a[0] * b[1] - b[0] * a[1];
    return &dest; //! warning: function returns address of local variable
}

/// Scale vector 'dest' so it has length 1
MATH_DO_INLINE void *vec3f_normalize(Vec3f dest) {
    //! Possible division by zero
    f32 invsqrt = rsqrtf(dest[0] * dest[0] + dest[1] * dest[1] + dest[2] * dest[2]);

    dest[0] *= invsqrt;
    dest[1] *= invsqrt;
    dest[2] *= invsqrt;
    return &dest; //! warning: function returns address of local variable
}

/// Get length of vector 'a'
MATH_DO_INLINE f32 vec3f_length(Vec3f a)
{
	return sqrtf(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}

/// Get dot product of vectors 'a' and 'b'
MATH_DO_INLINE f32 vec3f_dot(Vec3f a, Vec3f b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

#pragma GCC diagnostic pop

#if !defined(TARGET_WII_U) && defined(NON_MATCHING)
extern void* memcpy(void*, const void*, size_t);
#endif

/// Copy matrix 'src' to 'dest'
MATH_DO_INLINE void mtxf_copy(Mat4 dest, Mat4 src) {
#ifdef TARGET_WII_U
    f32*       const pDst = &(dest[0][0]);
    const f32* const pSrc = &(src[0][0]);

    // Temporary variable
    f32 v0;

    asm volatile ("psq_l  %[v0],  0(%[pSrc]), 0, 0" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
    asm volatile ("psq_st %[v0],  0(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_l  %[v0],  8(%[pSrc]), 0, 0" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
    asm volatile ("psq_st %[v0],  8(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_l  %[v0], 16(%[pSrc]), 0, 0" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
    asm volatile ("psq_st %[v0], 16(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_l  %[v0], 24(%[pSrc]), 0, 0" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
    asm volatile ("psq_st %[v0], 24(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_l  %[v0], 32(%[pSrc]), 0, 0" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
    asm volatile ("psq_st %[v0], 32(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_l  %[v0], 40(%[pSrc]), 0, 0" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
    asm volatile ("psq_st %[v0], 40(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_l  %[v0], 48(%[pSrc]), 0, 0" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
    asm volatile ("psq_st %[v0], 48(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_l  %[v0], 56(%[pSrc]), 0, 0" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
    asm volatile ("psq_st %[v0], 56(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
#elif defined(NON_MATCHING)
    memcpy(dest, src, sizeof(Mat4));
#else
    register s32 i;
    register u32 *d = (u32 *) dest;
    register u32 *s = (u32 *) src;

    for (i = 0; i < 16; i++) {
        *d++ = *s++;
    }
#endif
}

/**
 * Set mtx to the identity matrix
 */
MATH_DO_INLINE void mtxf_identity(Mat4 mtx) {
#ifdef TARGET_WII_U
    f32* const pDst = &(mtx[0][0]);

    // Constants
    register const f32 v00 = 0.0f;
    register const f32 v11 = 1.0f;
    register       f32 v01;
    register       f32 v10;

    asm volatile ("ps_merge00 %[v01], %[v00], %[v11]" : [v01] "=f"(v01) : [v00] "f"(v00), [v11] "f"(v11));
    asm volatile ("ps_merge00 %[v10], %[v11], %[v00]" : [v10] "=f"(v10) : [v00] "f"(v00), [v11] "f"(v11));

    asm volatile ("psq_st %[v10],  0(%[pDst]), 0, 0" : : [v10] "f"(v10), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_st %[v00],  8(%[pDst]), 0, 0" : : [v00] "f"(v00), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_st %[v01], 16(%[pDst]), 0, 0" : : [v01] "f"(v01), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_st %[v00], 24(%[pDst]), 0, 0" : : [v00] "f"(v00), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_st %[v00], 32(%[pDst]), 0, 0" : : [v00] "f"(v00), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_st %[v10], 40(%[pDst]), 0, 0" : : [v10] "f"(v10), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_st %[v00], 48(%[pDst]), 0, 0" : : [v00] "f"(v00), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_st %[v01], 56(%[pDst]), 0, 0" : : [v01] "f"(v01), [pDst] "b"(pDst) : "memory");
#else
    register s32 i;
    register f32 *dest;
    // Note: These loops need to be on one line to match on PAL

    // initialize everything except the first and last cells to 0
    for (dest = (f32 *) mtx + 1, i = 0; i < 14; dest++, i++) *dest = 0;

    // initialize the diagonal cells to 1
    for (dest = (f32 *) mtx, i = 0; i < 4; dest += 5, i++) *dest = 1;
#endif // TARGET_WII_U
}

/**
 * Set dest to a translation matrix of vector b
 */
MATH_DO_INLINE void mtxf_translate(Mat4 dest, Vec3f b) {
    mtxf_identity(dest);
#ifdef NON_MATCHING
    (void)vec3f_copy(dest[3], b);
#else
    dest[3][0] = b[0];
    dest[3][1] = b[1];
    dest[3][2] = b[2];
#endif // NON_MATCHING
}

/**
 * Set mtx to a look-at matrix for the camera. The resulting transformation
 * transforms the world as if there exists a camera at position 'from' pointed
 * at the position 'to'. The up-vector is assumed to be (0, 1, 0), but the 'roll'
 * angle allows a bank rotation of the camera.
 */
MATH_DO_INLINE void mtxf_lookat(Mat4 mtx, Vec3f from, Vec3f to, s16 roll) {
    register f32 invLength;
    f32 dx;
    f32 dz;
    f32 xColY;
    f32 yColY;
    f32 zColY;
    f32 xColZ;
    f32 yColZ;
    f32 zColZ;
    f32 xColX;
    f32 yColX;
    f32 zColX;

    dx = to[0] - from[0];
    dz = to[2] - from[2];

    invLength = -rsqrtf(dx * dx + dz * dz);
    dx *= invLength;
    dz *= invLength;

    yColY = coss(roll);
    xColY = sins(roll) * dz;
    zColY = -sins(roll) * dx;

    xColZ = to[0] - from[0];
    yColZ = to[1] - from[1];
    zColZ = to[2] - from[2];

    invLength = -rsqrtf(xColZ * xColZ + yColZ * yColZ + zColZ * zColZ);
    xColZ *= invLength;
    yColZ *= invLength;
    zColZ *= invLength;

    xColX = yColY * zColZ - zColY * yColZ;
    yColX = zColY * xColZ - xColY * zColZ;
    zColX = xColY * yColZ - yColY * xColZ;

    invLength = rsqrtf(xColX * xColX + yColX * yColX + zColX * zColX);

    xColX *= invLength;
    yColX *= invLength;
    zColX *= invLength;

    xColY = yColZ * zColX - zColZ * yColX;
    yColY = zColZ * xColX - xColZ * zColX;
    zColY = xColZ * yColX - yColZ * xColX;

    invLength = rsqrtf(xColY * xColY + yColY * yColY + zColY * zColY);
    xColY *= invLength;
    yColY *= invLength;
    zColY *= invLength;

    mtx[0][0] = xColX;
    mtx[1][0] = yColX;
    mtx[2][0] = zColX;
    mtx[3][0] = -(from[0] * xColX + from[1] * yColX + from[2] * zColX);

    mtx[0][1] = xColY;
    mtx[1][1] = yColY;
    mtx[2][1] = zColY;
    mtx[3][1] = -(from[0] * xColY + from[1] * yColY + from[2] * zColY);

    mtx[0][2] = xColZ;
    mtx[1][2] = yColZ;
    mtx[2][2] = zColZ;
    mtx[3][2] = -(from[0] * xColZ + from[1] * yColZ + from[2] * zColZ);

    mtx[0][3] = 0;
    mtx[1][3] = 0;
    mtx[2][3] = 0;
    mtx[3][3] = 1;
}

/**
 * Build a matrix that rotates around the z axis, then the x axis, then the y
 * axis, and then translates.
 */
MATH_DO_INLINE void mtxf_rotate_zxy_and_translate(Mat4 dest, Vec3f translate, Vec3s rotate) {
    register f32 sx = sins(rotate[0]);
    register f32 cx = coss(rotate[0]);

    register f32 sy = sins(rotate[1]);
    register f32 cy = coss(rotate[1]);

    register f32 sz = sins(rotate[2]);
    register f32 cz = coss(rotate[2]);

    dest[0][0] = cy * cz + sx * sy * sz;
    dest[1][0] = -cy * sz + sx * sy * cz;
    dest[2][0] = cx * sy;
    dest[3][0] = translate[0];

    dest[0][1] = cx * sz;
    dest[1][1] = cx * cz;
    dest[2][1] = -sx;
    dest[3][1] = translate[1];

    dest[0][2] = -sy * cz + sx * cy * sz;
    dest[1][2] = sy * sz + sx * cy * cz;
    dest[2][2] = cx * cy;
    dest[3][2] = translate[2];

    dest[0][3] = dest[1][3] = dest[2][3] = 0.0f;
    dest[3][3] = 1.0f;
}

/**
 * Build a matrix that rotates around the x axis, then the y axis, then the z
 * axis, and then translates.
 */
MATH_DO_INLINE void mtxf_rotate_xyz_and_translate(Mat4 dest, Vec3f b, Vec3s c) {
    register f32 sx = sins(c[0]);
    register f32 cx = coss(c[0]);

    register f32 sy = sins(c[1]);
    register f32 cy = coss(c[1]);

    register f32 sz = sins(c[2]);
    register f32 cz = coss(c[2]);

    dest[0][0] = cy * cz;
    dest[0][1] = cy * sz;
    dest[0][2] = -sy;
    dest[0][3] = 0;

    dest[1][0] = sx * sy * cz - cx * sz;
    dest[1][1] = sx * sy * sz + cx * cz;
    dest[1][2] = sx * cy;
    dest[1][3] = 0;

    dest[2][0] = cx * sy * cz + sx * sz;
    dest[2][1] = cx * sy * sz - sx * cz;
    dest[2][2] = cx * cy;
    dest[2][3] = 0;

    dest[3][0] = b[0];
    dest[3][1] = b[1];
    dest[3][2] = b[2];
    dest[3][3] = 1;
}

/**
 * Set 'dest' to a transformation matrix that turns an object to face the camera.
 * 'mtx' is the look-at matrix from the camera
 * 'position' is the position of the object in the world
 * 'angle' rotates the object while still facing the camera.
 */
MATH_DO_INLINE void mtxf_billboard(Mat4 dest, Mat4 mtx, Vec3f position, s16 angle) {
    dest[0][0] = coss(angle);
    dest[0][1] = sins(angle);
    dest[0][2] = 0;
    dest[0][3] = 0;

    dest[1][0] = -dest[0][1];
    dest[1][1] = dest[0][0];
    dest[1][2] = 0;
    dest[1][3] = 0;

    dest[2][0] = 0;
    dest[2][1] = 0;
    dest[2][2] = 1;
    dest[2][3] = 0;

    dest[3][0] =
        mtx[0][0] * position[0] + mtx[1][0] * position[1] + mtx[2][0] * position[2] + mtx[3][0];
    dest[3][1] =
        mtx[0][1] * position[0] + mtx[1][1] * position[1] + mtx[2][1] * position[2] + mtx[3][1];
    dest[3][2] =
        mtx[0][2] * position[0] + mtx[1][2] * position[1] + mtx[2][2] * position[2] + mtx[3][2];
    dest[3][3] = 1;
}

// straight up mtxf_billboard but minus the dest[1][n] lines. transform for cylindrical billboards
MATH_DO_INLINE void mtxf_cylboard(Mat4 dest, Mat4 mtx, Vec3f position, s16 angle) {
    dest[0][0] = coss(angle);
    dest[0][1] = sins(angle);
    dest[0][2] = 0;
    dest[0][3] = 0;

    dest[1][0] = mtx[1][0];
    dest[1][1] = mtx[1][1];
    dest[1][2] = mtx[1][2];
    dest[1][3] = 0;

    dest[2][0] = 0;
    dest[2][1] = 0;
    dest[2][2] = 1;
    dest[2][3] = 0;

    dest[3][0] =
        mtx[0][0] * position[0] + mtx[1][0] * position[1] + mtx[2][0] * position[2] + mtx[3][0];
    dest[3][1] =
        mtx[0][1] * position[0] + mtx[1][1] * position[1] + mtx[2][1] * position[2] + mtx[3][1];
    dest[3][2] =
        mtx[0][2] * position[0] + mtx[1][2] * position[1] + mtx[2][2] * position[2] + mtx[3][2];
    dest[3][3] = 1;
}

/**
 * Set 'dest' to a transformation matrix that aligns an object with the terrain
 * based on the normal. Used for enemies.
 * 'upDir' is the terrain normal
 * 'yaw' is the angle which it should face
 * 'pos' is the object's position in the world
 */
MATH_DO_INLINE void mtxf_align_terrain_normal(Mat4 dest, Vec3f upDir, Vec3f pos, s16 yaw) {
    Vec3f lateralDir;
    Vec3f leftDir;
    Vec3f forwardDir;

    vec3f_set(lateralDir, sins(yaw), 0, coss(yaw));
    vec3f_normalize(upDir);

    vec3f_cross(leftDir, upDir, lateralDir);
    vec3f_normalize(leftDir);

    vec3f_cross(forwardDir, leftDir, upDir);
    vec3f_normalize(forwardDir);

#ifdef NON_MATCHING
    (void)vec3f_copy(dest[0], leftDir);
    (void)vec3f_copy(dest[1], upDir);
    (void)vec3f_copy(dest[2], forwardDir);
    (void)vec3f_copy(dest[3], pos);
#else
    dest[0][0] = leftDir[0];
    dest[0][1] = leftDir[1];
    dest[0][2] = leftDir[2];
    dest[3][0] = pos[0];

    dest[1][0] = upDir[0];
    dest[1][1] = upDir[1];
    dest[1][2] = upDir[2];
    dest[3][1] = pos[1];

    dest[2][0] = forwardDir[0];
    dest[2][1] = forwardDir[1];
    dest[2][2] = forwardDir[2];
    dest[3][2] = pos[2];
#endif // NON_MATCHING

    dest[0][3] = 0.0f;
    dest[1][3] = 0.0f;
    dest[2][3] = 0.0f;
    dest[3][3] = 1.0f;
}

/**
 * Set 'mtx' to a transformation matrix that aligns an object with the terrain
 * based on 3 height samples in an equilateral triangle around the object.
 * Used for Mario when crawling or sliding.
 * 'yaw' is the angle which it should face
 * 'pos' is the object's position in the world
 * 'radius' is the distance from each triangle vertex to the center
 */
MATH_DO_INLINE void mtxf_align_terrain_triangle(Mat4 mtx, Vec3f pos, s16 yaw, f32 radius) {
    struct Surface *sp74;
    Vec3f point0;
    Vec3f point1;
    Vec3f point2;
    Vec3f forward;
    Vec3f xColumn;
    Vec3f yColumn;
    Vec3f zColumn;
    f32 avgY;
    f32 minY = -radius * 3;

    point0[0] = pos[0] + radius * sins(yaw + 0x2AAA);
    point0[2] = pos[2] + radius * coss(yaw + 0x2AAA);
    point1[0] = pos[0] + radius * sins(yaw + 0x8000);
    point1[2] = pos[2] + radius * coss(yaw + 0x8000);
    point2[0] = pos[0] + radius * sins(yaw + 0xD555);
    point2[2] = pos[2] + radius * coss(yaw + 0xD555);

    point0[1] = find_floor(point0[0], pos[1] + 150, point0[2], &sp74);
    point1[1] = find_floor(point1[0], pos[1] + 150, point1[2], &sp74);
    point2[1] = find_floor(point2[0], pos[1] + 150, point2[2], &sp74);

    if (point0[1] - pos[1] < minY) {
        point0[1] = pos[1];
    }

    if (point1[1] - pos[1] < minY) {
        point1[1] = pos[1];
    }

    if (point2[1] - pos[1] < minY) {
        point2[1] = pos[1];
    }

    avgY = (point0[1] + point1[1] + point2[1]) / 3;

    vec3f_set(forward, sins(yaw), 0, coss(yaw));
    find_vector_perpendicular_to_plane(yColumn, point0, point1, point2);
    vec3f_normalize(yColumn);
    vec3f_cross(xColumn, yColumn, forward);
    vec3f_normalize(xColumn);
    vec3f_cross(zColumn, xColumn, yColumn);
    vec3f_normalize(zColumn);

#ifdef NON_MATCHING
    (void)vec3f_copy(mtx[0], xColumn);
    (void)vec3f_copy(mtx[1], yColumn);
    (void)vec3f_copy(mtx[2], zColumn);

    if (avgY < pos[1])
        (void)vec3f_copy(mtx[3], pos);

    else
    {
        mtx[3][0] = pos[0];
        mtx[3][1] = avgY;
        mtx[3][2] = pos[2];
    }
#else
    mtx[0][0] = xColumn[0];
    mtx[0][1] = xColumn[1];
    mtx[0][2] = xColumn[2];
    mtx[3][0] = pos[0];

    mtx[1][0] = yColumn[0];
    mtx[1][1] = yColumn[1];
    mtx[1][2] = yColumn[2];
    mtx[3][1] = (avgY < pos[1]) ? pos[1] : avgY;

    mtx[2][0] = zColumn[0];
    mtx[2][1] = zColumn[1];
    mtx[2][2] = zColumn[2];
    mtx[3][2] = pos[2];
#endif // NON_MATCHING

    mtx[0][3] = 0;
    mtx[1][3] = 0;
    mtx[2][3] = 0;
    mtx[3][3] = 1;
}

/**
 * Sets matrix 'dest' to the matrix product a * b assuming they are both
 * transformation matrices with a w-component of 1. Since the bottom row
 * is assumed to equal [0, 0, 0, 1], it saves some multiplications and
 * addition.
 * The resulting matrix represents first applying transformation b and
 * then a.
 */
MATH_DO_INLINE void mtxf_mul(Mat4 dest, Mat4 a, Mat4 b) {
#ifdef TARGET_WII_U
    f32*       const pDst = &(dest[0][0]);
    const f32* const pA   = &(a[0][0]);
    const f32* const pB   = &(b[0][0]);

    // Temporary variables
    register f32 v0;
    register f32 v1;
    register f32 v2;
    register f32 v3;
    register f32 v4;
    register f32 v5;
    register f32 v6;
    register f32 v7;
    register f32 v8;
    register f32 v9;
    register f32 v10;
    register f32 v11;
    register f32 v12;
    register f32 v13;

    asm volatile (
        "psq_l %[v0],  0(%[pA]), 0, 0           \n\t"
        "psq_l %[v2],  0(%[pB]), 0, 0           \n\t"
        "ps_muls0 %[v6], %[v2], %[v0]           \n\t"
        "psq_l %[v3], 16(%[pB]), 0, 0           \n\t"
        "psq_l %[v4], 32(%[pB]), 0, 0           \n\t"
        "ps_madds1 %[v6], %[v3], %[v0], %[v6]   \n\t"
        "psq_l %[v1],  8(%[pA]), 0, 0           \n\t"
        "psq_l %[v5], 48(%[pB]), 0, 0           \n\t"
        "ps_madds0 %[v6], %[v4], %[v1], %[v6]   \n\t"
        "psq_l %[v0], 16(%[pA]), 0, 0           \n\t"
        "ps_madds1 %[v6], %[v5], %[v1], %[v6]   \n\t"
        "psq_l %[v1], 24(%[pA]), 0, 0           \n\t"
        "ps_muls0 %[v8], %[v2], %[v0]           \n\t"
        "ps_madds1 %[v8], %[v3], %[v0], %[v8]   \n\t"
        "psq_l %[v0], 32(%[pA]), 0, 0           \n\t"
        "ps_madds0 %[v8], %[v4], %[v1], %[v8]   \n\t"
        "ps_madds1 %[v8], %[v5], %[v1], %[v8]   \n\t"
        "psq_l %[v1], 40(%[pA]), 0, 0           \n\t"
        "ps_muls0 %[v10], %[v2], %[v0]          \n\t"
        "ps_madds1 %[v10], %[v3], %[v0], %[v10] \n\t"
        "psq_l %[v0], 48(%[pA]), 0, 0           \n\t"
        "ps_madds0 %[v10], %[v4], %[v1], %[v10] \n\t"
        "ps_madds1 %[v10], %[v5], %[v1], %[v10] \n\t"
        "psq_l %[v1], 56(%[pA]), 0, 0           \n\t"
        "ps_muls0 %[v12], %[v2], %[v0]          \n\t"
        "psq_l %[v2],  8(%[pB]), 0, 0           \n\t"
        "ps_madds1 %[v12], %[v3], %[v0], %[v12] \n\t"
        "psq_l %[v0],  0(%[pA]), 0, 0           \n\t"
        "ps_madds0 %[v12], %[v4], %[v1], %[v12] \n\t"
        "psq_l %[v3], 24(%[pB]), 0, 0           \n\t"
        "ps_madds1 %[v12], %[v5], %[v1], %[v12] \n\t"
        "psq_l %[v1],  8(%[pA]), 0, 0           \n\t"
        "ps_muls0 %[v7], %[v2], %[v0]           \n\t"
        "psq_l %[v4], 40(%[pB]), 0, 0           \n\t"
        "ps_madds1 %[v7], %[v3], %[v0], %[v7]   \n\t"
        "psq_l %[v5], 56(%[pB]), 0, 0           \n\t"
        "ps_madds0 %[v7], %[v4], %[v1], %[v7]   \n\t"
        "psq_l %[v0], 16(%[pA]), 0, 0           \n\t"
        "ps_madds1 %[v7], %[v5], %[v1], %[v7]   \n\t"
        "psq_l %[v1], 24(%[pA]), 0, 0           \n\t"
        "ps_muls0 %[v9], %[v2], %[v0]           \n\t"
        "psq_st  %[v6],  0(%[pDst]), 0, 0       \n\t"
        "ps_madds1 %[v9], %[v3], %[v0], %[v9]   \n\t"
        "psq_l %[v0], 32(%[pA]), 0, 0           \n\t"
        "ps_madds0 %[v9], %[v4], %[v1], %[v9]   \n\t"
        "psq_st  %[v8], 16(%[pDst]), 0, 0       \n\t"
        "ps_madds1 %[v9], %[v5], %[v1], %[v9]   \n\t"
        "psq_l %[v1], 40(%[pA]), 0, 0           \n\t"
        "ps_muls0 %[v11], %[v2], %[v0]          \n\t"
        "psq_st %[v10], 32(%[pDst]), 0, 0       \n\t"
        "ps_madds1 %[v11], %[v3], %[v0], %[v11] \n\t"
        "psq_l %[v0], 48(%[pA]), 0, 0           \n\t"
        "ps_madds0 %[v11], %[v4], %[v1], %[v11] \n\t"
        "psq_st %[v12], 48(%[pDst]), 0, 0       \n\t"
        "ps_madds1 %[v11], %[v5], %[v1], %[v11] \n\t"
        "psq_l %[v1], 56(%[pA]), 0, 0           \n\t"
        "ps_muls0 %[v13], %[v2], %[v0]          \n\t"
        "psq_st  %[v7],  8(%[pDst]), 0, 0       \n\t"
        "ps_madds1 %[v13], %[v3], %[v0], %[v13] \n\t"
        "psq_st  %[v9], 24(%[pDst]), 0, 0       \n\t"
        "ps_madds0 %[v13], %[v4], %[v1], %[v13] \n\t"
        "psq_st %[v11], 40(%[pDst]), 0, 0       \n\t"
        "ps_madds1 %[v13], %[v5], %[v1], %[v13] \n\t"
        "psq_st %[v13], 56(%[pDst]), 0, 0       \n\t"
        : [v0 ] "=f"(v0 ),
          [v1 ] "=f"(v1 ),
          [v2 ] "=f"(v2 ),
          [v3 ] "=f"(v3 ),
          [v4 ] "=f"(v4 ),
          [v5 ] "=f"(v5 ),
          [v6 ] "=f"(v6 ),
          [v7 ] "=f"(v7 ),
          [v8 ] "=f"(v8 ),
          [v9 ] "=f"(v9 ),
          [v10] "=f"(v10),
          [v11] "=f"(v11),
          [v12] "=f"(v12),
          [v13] "=f"(v13)
        : [pA ]  "b"(pA ),
          [pB ]  "b"(pB ),
          [pDst] "b"(pDst)
        : "memory"
    );
#else
    Mat4 temp;
    register f32 entry0;
    register f32 entry1;
    register f32 entry2;

    // column 0
    entry0 = a[0][0];
    entry1 = a[0][1];
    entry2 = a[0][2];
    temp[0][0] = entry0 * b[0][0] + entry1 * b[1][0] + entry2 * b[2][0];
    temp[0][1] = entry0 * b[0][1] + entry1 * b[1][1] + entry2 * b[2][1];
    temp[0][2] = entry0 * b[0][2] + entry1 * b[1][2] + entry2 * b[2][2];

    // column 1
    entry0 = a[1][0];
    entry1 = a[1][1];
    entry2 = a[1][2];
    temp[1][0] = entry0 * b[0][0] + entry1 * b[1][0] + entry2 * b[2][0];
    temp[1][1] = entry0 * b[0][1] + entry1 * b[1][1] + entry2 * b[2][1];
    temp[1][2] = entry0 * b[0][2] + entry1 * b[1][2] + entry2 * b[2][2];

    // column 2
    entry0 = a[2][0];
    entry1 = a[2][1];
    entry2 = a[2][2];
    temp[2][0] = entry0 * b[0][0] + entry1 * b[1][0] + entry2 * b[2][0];
    temp[2][1] = entry0 * b[0][1] + entry1 * b[1][1] + entry2 * b[2][1];
    temp[2][2] = entry0 * b[0][2] + entry1 * b[1][2] + entry2 * b[2][2];

    // column 3
    entry0 = a[3][0];
    entry1 = a[3][1];
    entry2 = a[3][2];
    temp[3][0] = entry0 * b[0][0] + entry1 * b[1][0] + entry2 * b[2][0] + b[3][0];
    temp[3][1] = entry0 * b[0][1] + entry1 * b[1][1] + entry2 * b[2][1] + b[3][1];
    temp[3][2] = entry0 * b[0][2] + entry1 * b[1][2] + entry2 * b[2][2] + b[3][2];

    temp[0][3] = temp[1][3] = temp[2][3] = 0;
    temp[3][3] = 1;

    mtxf_copy(dest, temp);
#endif // TARGET_WII_U
}

/**
 * Set matrix 'dest' to 'mtx' scaled by vector s
 */
MATH_DO_INLINE void mtxf_scale_vec3f(Mat4 dest, Mat4 mtx, Vec3f s) {
#ifdef TARGET_WII_U
    f32*       const pDst = &(dest[0][0]);
    const f32* const pSrc = &(mtx[0][0]);
    const f32* const pS   = &(s[0]);

    // Temporary variable
    f32 v0;
    f32 v1;
    f32 v2;

    asm volatile ("psq_l %[v1], 0(%[pS]), 0, 0" : [v1] "=f"(v1) : [pS] "b"(pS));
    asm volatile ("psq_l %[v2], 8(%[pS]), 1, 0" : [v2] "=f"(v2) : [pS] "b"(pS));

    asm volatile ("psq_l  %[v0],  0(%[pSrc]), 0, 0" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
    asm volatile ("ps_muls0 %[v0], %[v0], %[v1]" : [v0] "+f"(v0) : [v1] "f"(v1));
    asm volatile ("psq_st %[v0],  0(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_l  %[v0],  8(%[pSrc]), 0, 0" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
    asm volatile ("ps_muls0 %[v0], %[v0], %[v1]" : [v0] "+f"(v0) : [v1] "f"(v1));
    asm volatile ("psq_st %[v0],  8(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");

    asm volatile ("psq_l  %[v0], 16(%[pSrc]), 0, 0" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
    asm volatile ("ps_muls1 %[v0], %[v0], %[v1]" : [v0] "+f"(v0) : [v1] "f"(v1));
    asm volatile ("psq_st %[v0], 16(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_l  %[v0], 24(%[pSrc]), 0, 0" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
    asm volatile ("ps_muls1 %[v0], %[v0], %[v1]" : [v0] "+f"(v0) : [v1] "f"(v1));
    asm volatile ("psq_st %[v0], 24(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");

    asm volatile ("psq_l  %[v0], 32(%[pSrc]), 0, 0" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
    asm volatile ("ps_muls0 %[v0], %[v0], %[v2]" : [v0] "+f"(v0) : [v2] "f"(v2));
    asm volatile ("psq_st %[v0], 32(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_l  %[v0], 40(%[pSrc]), 0, 0" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
    asm volatile ("ps_muls0 %[v0], %[v0], %[v2]" : [v0] "+f"(v0) : [v2] "f"(v2));
    asm volatile ("psq_st %[v0], 40(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");

    asm volatile ("psq_l  %[v0], 48(%[pSrc]), 0, 0" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
  //asm volatile ("ps_muls1 %[v0], %[v0], %[v2]" : [v0] "+f"(v0) : [v2] "f"(v2));
    asm volatile ("psq_st %[v0], 48(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
    asm volatile ("psq_l  %[v0], 56(%[pSrc]), 0, 0" : [v0] "=f"(v0) : [pSrc] "b"(pSrc));
  //asm volatile ("ps_muls1 %[v0], %[v0], %[v2]" : [v0] "+f"(v0) : [v2] "f"(v2));
    asm volatile ("psq_st %[v0], 56(%[pDst]), 0, 0" : : [v0] "f"(v0), [pDst] "b"(pDst) : "memory");
#else
    register s32 i;

    for (i = 0; i < 4; i++) {
        dest[0][i] = mtx[0][i] * s[0];
        dest[1][i] = mtx[1][i] * s[1];
        dest[2][i] = mtx[2][i] * s[2];
        dest[3][i] = mtx[3][i];
    }
#endif // TARGET_WII_U
}

/**
 * Multiply a vector with a transformation matrix, which applies the transformation
 * to the point. Note that the bottom row is assumed to be [0, 0, 0, 1], which is
 * true for transformation matrices if the translation has a w component of 1.
 */
MATH_DO_INLINE void mtxf_mul_vec3s(Mat4 mtx, Vec3s b) {
    register f32 x = b[0];
    register f32 y = b[1];
    register f32 z = b[2];

    b[0] = x * mtx[0][0] + y * mtx[1][0] + z * mtx[2][0] + mtx[3][0];
    b[1] = x * mtx[0][1] + y * mtx[1][1] + z * mtx[2][1] + mtx[3][1];
    b[2] = x * mtx[0][2] + y * mtx[1][2] + z * mtx[2][2] + mtx[3][2];
}

/**
 * Convert float matrix 'src' to fixed point matrix 'dest'.
 * The float matrix may not contain entries larger than 65536 or the console
 * crashes. The fixed point matrix has entries with a 16-bit integer part, so
 * the floating point numbers are multiplied by 2^16 before being cast to a s32
 * integer. If this doesn't fit, the N64 and iQue consoles will throw an
 * exception. On Wii and Wii U Virtual Console the value will simply be clamped
 * and no crashes occur.
 */
MATH_DO_INLINE void mtxf_to_mtx(Mtx *dest, Mat4 src) {
#if defined(NON_MATCHING) && defined(GBI_FLOATS)
    mtxf_copy(dest->m, src);
#elif defined(AVOID_UB)
    // Avoid type-casting which is technically UB by calling the equivalent
    // guMtxF2L function. This helps little-endian systems, as well.
    guMtxF2L(src, dest);
#else
    s32 asFixedPoint;
    register s32 i;
    register s16 *a3 = (s16 *) dest;      // all integer parts stored in first 16 bytes
    register s16 *t0 = (s16 *) dest + 16; // all fraction parts stored in last 16 bytes
    register f32 *t1 = (f32 *) src;

    for (i = 0; i < 16; i++) {
        asFixedPoint = *t1++ * (1 << 16); //! float-to-integer conversion responsible for PU crashes
        *a3++ = GET_HIGH_S16_OF_32(asFixedPoint); // integer part
        *t0++ = GET_LOW_S16_OF_32(asFixedPoint);  // fraction part
    }
#endif
}

/**
 * Set 'mtx' to a transformation matrix that rotates around the z axis.
 */
MATH_DO_INLINE void mtxf_rotate_xy(Mtx *mtx, s16 angle) {
    Mat4 temp;

    mtxf_identity(temp);
    temp[0][0] = coss(angle);
    temp[0][1] = sins(angle);
    temp[1][0] = -temp[0][1];
    temp[1][1] = temp[0][0];
    mtxf_to_mtx(mtx, temp);
}

/**
 * Extract a position given an object's transformation matrix and a camera matrix.
 * This is used for determining the world position of the held object: since objMtx
 * inherits the transformation from both the camera and Mario, it calculates this
 * by taking the camera matrix and inverting its transformation by first rotating
 * objMtx back from screen orientation to world orientation, and then subtracting
 * the camera position.
 */
MATH_DO_INLINE void get_pos_from_transform_mtx(Vec3f dest, Mat4 objMtx, Mat4 camMtx) {
    f32 camX = camMtx[3][0] * camMtx[0][0] + camMtx[3][1] * camMtx[0][1] + camMtx[3][2] * camMtx[0][2];
    f32 camY = camMtx[3][0] * camMtx[1][0] + camMtx[3][1] * camMtx[1][1] + camMtx[3][2] * camMtx[1][2];
    f32 camZ = camMtx[3][0] * camMtx[2][0] + camMtx[3][1] * camMtx[2][1] + camMtx[3][2] * camMtx[2][2];

    dest[0] =
        objMtx[3][0] * camMtx[0][0] + objMtx[3][1] * camMtx[0][1] + objMtx[3][2] * camMtx[0][2] - camX;
    dest[1] =
        objMtx[3][0] * camMtx[1][0] + objMtx[3][1] * camMtx[1][1] + objMtx[3][2] * camMtx[1][2] - camY;
    dest[2] =
        objMtx[3][0] * camMtx[2][0] + objMtx[3][1] * camMtx[2][1] + objMtx[3][2] * camMtx[2][2] - camZ;
}

/**
 * Take the vector starting at 'from' pointed at 'to' an retrieve the length
 * of that vector, as well as the yaw and pitch angles.
 * Basically it converts the direction to spherical coordinates.
 */
MATH_DO_INLINE void vec3f_get_dist_and_angle(Vec3f from, Vec3f to, f32 *dist, s16 *pitch, s16 *yaw) {
    register f32 x = to[0] - from[0];
    register f32 y = to[1] - from[1];
    register f32 z = to[2] - from[2];

    *dist = sqrtf(x * x + y * y + z * z);
    *pitch = atan2s(sqrtf(x * x + z * z), y);
    *yaw = atan2s(z, x);
}

/**
 * Construct the 'to' point which is distance 'dist' away from the 'from' position,
 * and has the angles pitch and yaw.
 */
MATH_DO_INLINE void vec3f_set_dist_and_angle(Vec3f from, Vec3f to, f32 dist, s16 pitch, s16 yaw) {
    to[0] = from[0] + dist * coss(pitch) * sins(yaw);
    to[1] = from[1] + dist * sins(pitch);
    to[2] = from[2] + dist * coss(pitch) * coss(yaw);
}

/**
 * Return the value 'current' after it tries to approach target, going up at
 * most 'inc' and going down at most 'dec'.
 */
MATH_DO_INLINE s32 approach_s32(s32 current, s32 target, s32 inc, s32 dec) {
    //! If target is close to the max or min s32, then it's possible to overflow
    // past it without stopping.

    if (current < target) {
        current += inc;
        if (current > target) {
            current = target;
        }
    } else {
        current -= dec;
        if (current < target) {
            current = target;
        }
    }
    return current;
}

/**
 * Return the value 'current' after it tries to approach target, going up at
 * most 'inc' and going down at most 'dec'.
 */
MATH_DO_INLINE f32 approach_f32(f32 current, f32 target, f32 inc, f32 dec) {
    if (current < target) {
        current += inc;
        if (current > target) {
            current = target;
        }
    } else {
        current -= dec;
        if (current < target) {
            current = target;
        }
    }
    return current;
}

extern s16 gArctanTable[];

/**
 * Helper function for atan2s. Does a look up of the arctangent of y/x assuming
 * the resulting angle is in range [0, 0x2000] (1/8 of a circle).
 */
MATH_DO_INLINE u16 atan2_lookup(f32 y, f32 x) {
    u16 ret;

    if (x == 0) {
        ret = gArctanTable[0];
    } else {
        ret = gArctanTable[(s32)(y / x * 1024 + 0.5f)];
    }
    return ret;
}

/**
 * Compute the angle from (0, 0) to (x, y) as a s16. Given that terrain is in
 * the xz-plane, this is commonly called with (z, x) to get a yaw angle.
 */
MATH_DO_INLINE s16 atan2s(f32 y, f32 x) {
    u16 ret;

    if (x >= 0) {
        if (y >= 0) {
            if (y >= x) {
                ret = atan2_lookup(x, y);
            } else {
                ret = 0x4000 - atan2_lookup(y, x);
            }
        } else {
            y = -y;
            if (y < x) {
                ret = 0x4000 + atan2_lookup(y, x);
            } else {
                ret = 0x8000 - atan2_lookup(x, y);
            }
        }
    } else {
        x = -x;
        if (y < 0) {
            y = -y;
            if (y >= x) {
                ret = 0x8000 + atan2_lookup(x, y);
            } else {
                ret = 0xC000 - atan2_lookup(y, x);
            }
        } else {
            if (y < x) {
                ret = 0xC000 + atan2_lookup(y, x);
            } else {
                ret = -atan2_lookup(x, y);
            }
        }
    }
    return ret;
}

#undef MATH_DO_INLINE
