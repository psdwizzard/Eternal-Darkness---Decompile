typedef unsigned char u8;
typedef signed int s32;

extern u8 lbl_8032CC08[];

/* Expand a DC value and four coefficients into a clamped 4x4 block. */
void WeightImBlock(u8 *dst, s32 stride, u8 dc, u8 a, u8 b, u8 c, u8 d)
{
    s32 bias, twiceDc, ab, cd, sum, difference;
    s32 topLeft, topRight, bottomRight, bottomLeft;
    s32 first, second, third, fourth;
    s32 ac, ad, bc, bd;
    u8 *row;
    u8 *clamp;

    twiceDc = dc * 2;
    ab = a - b;
    cd = c - d;
    bias = ((dc + 0x80) * 8) + 4;
    topLeft = (a + c) - twiceDc;
    topRight = (a + d) - twiceDc;
    sum = ab + cd;
    difference = ab - cd;
    first = bias + sum;
    bottomRight = (b + d) - twiceDc;
    clamp = lbl_8032CC08;
    ac = a - c;
    ad = a - d;
    dst[0] = clamp[(topLeft + first) >> 3];
    second = bias + difference;
    bottomLeft = (b + c) - twiceDc;
    dst[1] = clamp[(ac + first) >> 3];
    dst[2] = clamp[(ad + second) >> 3];
    dst[3] = clamp[(topRight + second) >> 3];
    third = bias - difference;
    bc = b - c;
    row = dst + stride;
    row[0] = clamp[(first - ac) >> 3];
    row[1] = clamp[(bias - bottomRight) >> 3];
    row[2] = clamp[(bias - bottomLeft) >> 3];
    row[3] = clamp[(second - ad) >> 3];
    fourth = bias - sum;
    bd = b - d;
    row += stride;
    row[0] = clamp[(third - bc) >> 3];
    row[1] = clamp[(bias - topRight) >> 3];
    row[2] = clamp[(bias - topLeft) >> 3];
    row[3] = clamp[(fourth - bd) >> 3];
    row += stride;
    row[0] = clamp[(bottomLeft + third) >> 3];
    row[1] = clamp[(bc + third) >> 3];
    row[2] = clamp[(bd + fourth) >> 3];
    row[3] = clamp[(bottomRight + fourth) >> 3];
}
