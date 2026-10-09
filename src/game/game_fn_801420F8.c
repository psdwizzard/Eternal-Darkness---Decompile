typedef unsigned char u8;
typedef signed short s16;

typedef struct Vec3 { float x, y, z; } Vec3;

extern u8 lbl_8064D020;
extern s16 lbl_8064D022, lbl_8064D024;
extern s16 lbl_8064D028[2], lbl_8064D02C[2];
extern float lbl_8064D030[2];
extern Vec3 lbl_805B12B0[];
extern int fn_801415B4(Vec3*, Vec3*, Vec3*);

/* Triangle/triangle plane and interval overlap test. */
int fn_801420F8(Vec3* p0, Vec3* p1, Vec3* p2, u8 triangle)
{
    Vec3 *u0, *u1, *u2;
    /* Retail keeps these in stack slots 0x8-0x2C (the original asm named
     * them as memory operands) and re-reads dv* from the stack later. */
    volatile float n1[3];
    volatile float d1;
    volatile float dv0, dv1, dv2;
    volatile float dv0dv1, dv0dv2;
    volatile float d2;
    float n2[3];
    float t0, t1, t2, td2, td1;
    float du0, du1, du2;
    float du0du1, du0du2;
    float dir[3];
    float adx, ady, adz;
    float vp0, vp1, vp2, up0, up1, up2;
    float a, b, c, x0, x1, d, e, f, y0, y1;
    float xx, yy, xxyy, tmp, i10, i11, i20, i21;
    float len;
    register float ax, ay, az, ex2, ey2, ez2;
    register float nx, ny, nz;
    register Vec3 *q1 = p1;
    signed char index;

    index = 0;
    lbl_8064D020 = triangle;
    lbl_8064D024 = lbl_8064D02C[triangle];
    lbl_8064D022 = lbl_8064D028[triangle];
    n2[0] = lbl_805B12B0[triangle + 6].x;
    n2[1] = lbl_805B12B0[triangle + 6].y;
    n2[2] = lbl_805B12B0[triangle + 6].z;
    td2 = lbl_8064D030[triangle];
    d2 = td2;

    t0 = p0->z * n2[2] + td2;
    t0 = p0->y * n2[1] + t0;
    t0 = p0->x * n2[0] + t0;
    if (__fabs(t0) < 0.000001f) t0 = 0.0f;
    dv0 = t0;
    t1 = p1->z * n2[2] + td2;
    t1 = p1->y * n2[1] + t1;
    t1 = p1->x * n2[0] + t1;
    if (__fabs(t1) < 0.000001f) t1 = 0.0f;
    dv1 = t1;
    t2 = p2->z * n2[2] + td2;
    t2 = p2->y * n2[1] + t2;
    t2 = p2->x * n2[0] + t2;
    if (__fabs(t2) < 0.000001f) t2 = 0.0f;
    dv2 = t2;
    dv0dv1 = t0 * t1;
    dv0dv2 = t0 * t2;
    if (dv0dv1 > 0.0f && dv0dv2 > 0.0f) return 0;

    ax = p0->x; ay = p0->y; az = p0->z;
    /* ASM: lfs/fsubs into f13-f15 keep the first edge in the fixed
     * registers the hand-written cross product reads; C cannot pin floats. */
    asm {
        lfs   f13, 0(q1)
        fsubs f13, f13, ax
        lfs   f14, 4(q1)
        fsubs f14, f14, ay
        lfs   f15, 8(q1)
        fsubs f15, f15, az
    }
    ex2 = p2->x - ax; ey2 = p2->y - ay; ez2 = p2->z - az;
    /* ASM: fmuls/fmsub cross product; the double-precision fmsub with no
     * frsp cannot be produced from float C expressions. */
    asm {
        fmuls nx, f15, ey2
        fmsub nx, f14, ez2, nx
        fmuls ny, f13, ez2
        fmsub ny, f15, ex2, ny
        fmuls nz, f14, ex2
        fmsub nz, f13, ey2, nz
    }
    len = nz * nz;
    len = ny * ny + len;
    len = nx * nx + len;
    if (len != 0.0f) {
        len = __frsqrte(len);
        nx *= len; ny *= len; nz *= len;
    }
    n1[0] = nx; n1[1] = ny; n1[2] = nz;
    td1 = -(nz * az + (ny * ay + nx * ax));
    d1 = td1;

    /* The stored triangle is visited in the order +2, +0, +4. */
    u0 = (&lbl_805B12B0[2] + lbl_8064D020);
    u1 = &lbl_805B12B0[lbl_8064D020];
    u2 = (&lbl_805B12B0[4] + lbl_8064D020);
    /* Evaluate the three plane distances together, then apply the offset. */
    du0 = ny * u0->y;
    du1 = ny * u1->y;
    du2 = ny * u2->y;
    du0 = nx * u0->x + du0;
    du1 = nx * u1->x + du1;
    du2 = nx * u2->x + du2;
    du0 = nz * u0->z + du0;
    du1 = nz * u1->z + du1;
    du2 = nz * u2->z + du2;
    du0 = td1 + du0;
    du1 = td1 + du1;
    du2 = td1 + du2;
    if ((du0 < 0.0f ? -du0 : du0) < 0.000001f) du0 = 0.0f;
    if ((du1 < 0.0f ? -du1 : du1) < 0.000001f) du1 = 0.0f;
    if ((du2 < 0.0f ? -du2 : du2) < 0.000001f) du2 = 0.0f;
    du0du1 = du0 * du1;
    du0du2 = du0 * du2;
    if (du0du1 > 0.0f && du0du2 > 0.0f) return 0;

    n2[0] = lbl_805B12B0[lbl_8064D020 + 6].x;
    n2[1] = lbl_805B12B0[lbl_8064D020 + 6].y;
    n2[2] = lbl_805B12B0[lbl_8064D020 + 6].z;
    dir[0] = nz * n2[1] - ny * n2[2];
    dir[1] = nx * n2[2] - nz * n2[0];
    dir[2] = ny * n2[0] - nx * n2[1];
    adx = dir[0]; ady = dir[1]; adz = dir[2];
    if (adx < 0.0f) adx = -adx;
    if (ady < 0.0f) ady = -ady;
    if (adz < 0.0f) adz = -adz;
    if (ady > adx) { adx = ady; index = 1; }
    if (adz > adx) index = 2;
    up0 = ((float*)u0)[index]; up1 = ((float*)u1)[index]; up2 = ((float*)u2)[index];
    vp0 = ((float*)p0)[index]; vp1 = ((float*)p1)[index]; vp2 = ((float*)p2)[index];

    /* Retail forms the stored triangle's interval before the input interval. */
    if (du0du1 > 0.0f) {
        a = up2; b = (up0-up2)*du2; c = (up1-up2)*du2; x0 = du2-du0; x1 = du2-du1;
    } else if (du0du2 > 0.0f) {
        a = up1; b = (up0-up1)*du1; c = (up2-up1)*du1; x0 = du1-du0; x1 = du1-du2;
    } else if (du1*du2 > 0.0f || du0 != 0.0f) {
        a = up0; b = (up1-up0)*du0; c = (up2-up0)*du0; x0 = du0-du1; x1 = du0-du2;
    } else if (du1 != 0.0f) {
        a = up1; b = (up0-up1)*du1; c = (up2-up1)*du1; x0 = du1-du0; x1 = du1-du2;
    } else if (du2 != 0.0f) {
        a = up2; b = (up0-up2)*du2; c = (up1-up2)*du2; x0 = du2-du0; x1 = du2-du1;
    } else return fn_801415B4(p0, p1, p2);

    if (dv0dv1 > 0.0f) {
        t2 = dv2; t0 = dv0; t1 = dv1;
        d = vp2; e = (vp0-vp2)*t2; f = (vp1-vp2)*t2; y0 = t2-t0; y1 = t2-t1;
    } else if (dv0dv2 > 0.0f) {
        t1 = dv1; t0 = dv0; t2 = dv2;
        d = vp1; e = (vp0-vp1)*t1; f = (vp2-vp1)*t1; y0 = t1-t0; y1 = t1-t2;
    } else {
        t1 = dv1; t2 = dv2;
        if (t1*t2 > 0.0f || (t0 = dv0) != 0.0f) {
            t0 = dv0;
            d = vp0; e = (vp1-vp0)*t0; f = (vp2-vp0)*t0; y0 = t0-t1; y1 = t0-t2;
        } else if (t1 != 0.0f) {
            d = vp1; e = (vp0-vp1)*t1; f = (vp2-vp1)*t1; y0 = t1-t0; y1 = t1-t2;
        } else if (t2 != 0.0f) {
            d = vp2; e = (vp0-vp2)*t2; f = (vp1-vp2)*t2; y0 = t2-t0; y1 = t2-t1;
        } else return fn_801415B4(p0, p1, p2);
    }

    xx = x0*x1; yy = y0*y1; xxyy = xx*yy;
    tmp = a*xxyy; i10 = tmp+b*x1*yy; i11 = tmp+c*x0*yy;
    tmp = d*xxyy; i20 = tmp+e*xx*y1; i21 = tmp+f*xx*y0;
    if (i10 > i11) { tmp=i10; i10=i11; i11=tmp; }
    if (i20 > i21) { tmp=i20; i20=i21; i21=tmp; }
    if (i11 < i20 || i21 < i10) return 0;
    return 1;
}
