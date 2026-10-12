typedef unsigned char u8;
typedef int s32;

/* Per-row helpers for a 4-pixel-wide block. */
#define COPY_ROW(d, s)                                                  \
    (d)[0] = (s)[0];                                                    \
    (d)[1] = (s)[1];                                                    \
    (d)[2] = (s)[2];                                                    \
    (d)[3] = (s)[3]

#define AVG2_ROW(d, a, b)                                               \
    (d)[0] = ((a)[0] + (b)[0] + 1) >> 1;                                \
    (d)[1] = ((a)[1] + (b)[1] + 1) >> 1;                                \
    (d)[2] = ((a)[2] + (b)[2] + 1) >> 1;                                \
    (d)[3] = ((a)[3] + (b)[3] + 1) >> 1

#define AVG4_ROW(d, a, b)                                               \
    (d)[0] = ((a)[0] + (a)[1] + (b)[0] + (b)[1] + 2) >> 2;              \
    (d)[1] = ((a)[1] + (a)[2] + (b)[1] + (b)[2] + 2) >> 2;              \
    (d)[2] = ((a)[2] + (a)[3] + (b)[2] + (b)[3] + 2) >> 2;              \
    (d)[3] = ((a)[3] + (a)[4] + (b)[3] + (b)[4] + 2) >> 2

/* 4x4 block copy with optional half-pel interpolation in x and/or y. */
void fn_80104BBC(u8 *dst, s32 dstStride, u8 *src, s32 srcStride, s32 halfX, s32 halfY) {
    u8 *s;
    u8 *s2;

    if (halfX == 0 && halfY == 0) {
        u8 *d;

        COPY_ROW(dst, src);
        s = src + srcStride;
        d = dst + dstStride;
        COPY_ROW(d, s);
        s += srcStride;
        d += dstStride;
        COPY_ROW(d, s);
        s += srcStride;
        d += dstStride;
        COPY_ROW(d, s);
        return;
    }
    if (halfX != 0 && halfY == 0) {
        u8 *d;

        AVG2_ROW(dst, src, src + 1);
        s = src + srcStride;
        d = dst + dstStride;
        AVG2_ROW(d, s, s + 1);
        s += srcStride;
        d += dstStride;
        AVG2_ROW(d, s, s + 1);
        s += srcStride;
        d += dstStride;
        AVG2_ROW(d, s, s + 1);
        return;
    }
    if (halfX == 0 && halfY != 0) {
        u8 *d;

        s2 = src + srcStride;
        d = dst + dstStride;
        AVG2_ROW(dst, src, s2);
        s = s2;
        s2 += srcStride;
        AVG2_ROW(d, s, s2);
        s2 += srcStride;
        s += srcStride;
        d += dstStride;
        AVG2_ROW(d, s, s2);
        s2 += srcStride;
        s += srcStride;
        d += dstStride;
        AVG2_ROW(d, s, s2);
        return;
    }
    if (halfX != 0 && halfY != 0) {
        u8 *d;

        s2 = src + srcStride;
        s = s2;
        d = dst + dstStride;
        AVG4_ROW(dst, src, s2);
        s2 += srcStride;
        AVG4_ROW(d, s, s2);
        s2 += srcStride;
        d += dstStride;
        s += srcStride;
        AVG4_ROW(d, s, s2);
        s2 += srcStride;
        d += dstStride;
        s += srcStride;
        AVG4_ROW(d, s, s2);
    }
}
