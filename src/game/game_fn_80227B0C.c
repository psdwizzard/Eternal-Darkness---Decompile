/* fn_80227B0C: GXInitSpecularDir - sets a light's position to a point far
 * along the negated direction and its direction to the normalized half-angle
 * vector between the light direction and the viewer (0,0,1). */

typedef unsigned char u8;
typedef float f32;

extern f32 lbl_80651688; /* 0.0f */
extern f32 lbl_806516A0; /* 1.0f */
extern const f32 lbl_806516D0; /* large distance */
extern double __frsqrte(double);

typedef struct {
    u8 pad[0x28];
    f32 lpos[3];
    f32 ldir[3];
} GXLightObjInt;

/* math.h sqrtf: three Newton-Raphson refinements of frsqrte */
static inline f32 sqrtf(f32 x)
{
    if (x > lbl_80651688) {
        volatile f32 y;
        double guess = __frsqrte((double)x);
        double t;
        t = x * (guess * guess);
        guess = 0.5 * guess * (3.0 - t);
        t = x * (guess * guess);
        guess = 0.5 * guess * (3.0 - t);
        t = x * (guess * guess);
        guess = 0.5 * guess * (3.0 - t);
        y = (f32)(x * guess);
        return y;
    }
    return x;
}

void fn_80227B0C(GXLightObjInt *lt_obj, f32 nx, f32 ny, f32 nz)
{
    f32 vx;
    f32 vy;
    f32 vz;
    f32 sx;
    f32 sy;
    f32 sz;
    f32 inv;
    f32 mag;

    vx = -nx;
    vy = -ny;
    vz = lbl_806516A0 - nz;
    sx = vx * vx;
    sy = vy * vy;
    sz = vz * vz;
    mag = sqrtf(sz + (sx + sy));
    inv = lbl_806516A0 / mag;
    lt_obj->ldir[0] = vx * inv;
    lt_obj->ldir[1] = vy * inv;
    lt_obj->ldir[2] = vz * inv;
    lt_obj->lpos[0] = lbl_806516D0 * vx;
    lt_obj->lpos[1] = lbl_806516D0 * vy;
    lt_obj->lpos[2] = lbl_806516D0 * -nz;
}
