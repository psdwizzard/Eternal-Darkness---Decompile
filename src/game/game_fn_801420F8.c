typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3 { float x, y, z; } Vec3;

extern u8 lbl_8064D020;
extern u16 lbl_8064D022, lbl_8064D024;
extern u16 lbl_8064D028[], lbl_8064D02C[];
extern float lbl_8064D030[];
extern Vec3 lbl_805B12B0[];
extern float lbl_80650410, lbl_80650420;
extern int fn_801415B4(Vec3*, Vec3*, Vec3*);

/* Triangle/triangle plane and interval overlap test. */
int fn_801420F8(Vec3* v0, Vec3* v1, Vec3* v2, u8 triangle)
{
    Vec3 *u0, *u1, *u2;
    float e1x, e1y, e1z, e2x, e2y, e2z;
    float n1x, n1y, n1z, n2x, n2y, n2z, d1, d2;
    float du0, du1, du2, dv0, dv1, dv2;
    float du0du1, du0du2, dv0dv1, dv0dv2;
    float dx, dy, dz, adx, ady, adz;
    float vp0, vp1, vp2, up0, up1, up2;
    float a, b, c, x0, x1, d, e, f, y0, y1;
    float xx, yy, xxyy, tmp, i10, i11, i20, i21, len;
    int index;

    lbl_8064D020 = triangle;
    lbl_8064D024 = lbl_8064D02C[triangle];
    lbl_8064D022 = lbl_8064D028[triangle];
    n2x = lbl_805B12B0[triangle + 6].x;
    n2y = lbl_805B12B0[triangle + 6].y;
    n2z = lbl_805B12B0[triangle + 6].z;
    d2 = lbl_8064D030[triangle];

    dv0 = v0->z * n2z + d2;
    dv0 = v0->y * n2y + dv0;
    dv0 = v0->x * n2x + dv0;
    if (__fabs(dv0) < lbl_80650420) dv0 = lbl_80650410;
    dv1 = v1->z * n2z + d2;
    dv1 = v1->y * n2y + dv1;
    dv1 = v1->x * n2x + dv1;
    if (__fabs(dv1) < lbl_80650420) dv1 = lbl_80650410;
    dv2 = v2->z * n2z + d2;
    dv2 = v2->y * n2y + dv2;
    dv2 = v2->x * n2x + dv2;
    if (__fabs(dv2) < lbl_80650420) dv2 = lbl_80650410;
    dv0dv1 = dv0 * dv1;
    dv0dv2 = dv0 * dv2;
    if (dv0dv1 > lbl_80650410 && dv0dv2 > lbl_80650410) return 0;

    e1x = v1->x - v0->x; e1y = v1->y - v0->y; e1z = v1->z - v0->z;
    e2x = v2->x - v0->x; e2y = v2->y - v0->y; e2z = v2->z - v0->z;
    n1x = e1y * e2z - e1z * e2y;
    n1y = e1z * e2x - e1x * e2z;
    n1z = e1x * e2y - e1y * e2x;
    len = n1x * n1x + n1y * n1y + n1z * n1z;
    if (len != lbl_80650410) len = __frsqrte(len);
    n1x *= len; n1y *= len; n1z *= len;
    d1 = -(n1x * v0->x + n1y * v0->y + n1z * v0->z);

    u0 = &lbl_805B12B0[triangle];
    u1 = &lbl_805B12B0[triangle + 2];
    u2 = &lbl_805B12B0[triangle + 4];
    du0 = n1x * u0->x + n1y * u0->y + n1z * u0->z + d1;
    du1 = n1x * u1->x + n1y * u1->y + n1z * u1->z + d1;
    du2 = n1x * u2->x + n1y * u2->y + n1z * u2->z + d1;
    if (__fabs(du0) < lbl_80650420) du0 = lbl_80650410;
    if (__fabs(du1) < lbl_80650420) du1 = lbl_80650410;
    if (__fabs(du2) < lbl_80650420) du2 = lbl_80650410;
    du0du1 = du0 * du1;
    du0du2 = du0 * du2;
    if (du0du1 > lbl_80650410 && du0du2 > lbl_80650410) return 0;

    dx = n1y * n2z - n1z * n2y;
    dy = n1z * n2x - n1x * n2z;
    dz = n1x * n2y - n1y * n2x;
    adx = __fabs(dx); ady = __fabs(dy); adz = __fabs(dz);
    index = 0;
    if (ady > adx) { adx = ady; index = 1; }
    if (adz > adx) index = 2;
    vp0 = ((float*)v0)[index]; vp1 = ((float*)v1)[index]; vp2 = ((float*)v2)[index];
    up0 = ((float*)u0)[index]; up1 = ((float*)u1)[index]; up2 = ((float*)u2)[index];

    if (dv0dv1 > lbl_80650410) {
        a = vp2; b = (vp0-vp2)*dv2; c = (vp1-vp2)*dv2; x0 = dv2-dv0; x1 = dv2-dv1;
    } else if (dv0dv2 > lbl_80650410) {
        a = vp1; b = (vp0-vp1)*dv1; c = (vp2-vp1)*dv1; x0 = dv1-dv0; x1 = dv1-dv2;
    } else if (dv1*dv2 > lbl_80650410 || dv0 != lbl_80650410) {
        a = vp0; b = (vp1-vp0)*dv0; c = (vp2-vp0)*dv0; x0 = dv0-dv1; x1 = dv0-dv2;
    } else if (dv1 != lbl_80650410) {
        a = vp1; b = (vp0-vp1)*dv1; c = (vp2-vp1)*dv1; x0 = dv1-dv0; x1 = dv1-dv2;
    } else if (dv2 != lbl_80650410) {
        a = vp2; b = (vp0-vp2)*dv2; c = (vp1-vp2)*dv2; x0 = dv2-dv0; x1 = dv2-dv1;
    } else return fn_801415B4(v0, v1, v2);

    if (du0du1 > lbl_80650410) {
        d = up2; e = (up0-up2)*du2; f = (up1-up2)*du2; y0 = du2-du0; y1 = du2-du1;
    } else if (du0du2 > lbl_80650410) {
        d = up1; e = (up0-up1)*du1; f = (up2-up1)*du1; y0 = du1-du0; y1 = du1-du2;
    } else if (du1*du2 > lbl_80650410 || du0 != lbl_80650410) {
        d = up0; e = (up1-up0)*du0; f = (up2-up0)*du0; y0 = du0-du1; y1 = du0-du2;
    } else if (du1 != lbl_80650410) {
        d = up1; e = (up0-up1)*du1; f = (up2-up1)*du1; y0 = du1-du0; y1 = du1-du2;
    } else if (du2 != lbl_80650410) {
        d = up2; e = (up0-up2)*du2; f = (up1-up2)*du2; y0 = du2-du0; y1 = du2-du1;
    } else return fn_801415B4(v0, v1, v2);

    xx = x0*x1; yy = y0*y1; xxyy = xx*yy;
    tmp = a*xxyy; i10 = tmp+b*x1*yy; i11 = tmp+c*x0*yy;
    tmp = d*xxyy; i20 = tmp+e*xx*y1; i21 = tmp+f*xx*y0;
    if (i10 > i11) { tmp=i10; i10=i11; i11=tmp; }
    if (i20 > i21) { tmp=i20; i20=i21; i21=tmp; }
    if (i11 < i20 || i21 < i10) return 0;
    return 1;
}
