typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3 { float x, y, z; } Vec3;

extern Vec3 lbl_805B12B0[];
extern float lbl_8064D030[2];
extern u16 lbl_8064D02C[2];
extern u16 lbl_8064D028[2];
extern float lbl_80650410;
extern void fn_80179AEC(Vec3*, const Vec3*);
extern float fn_800ED720(float);

/* Transform one triangle, derive its normalized face plane, and select the
 * two projection axes used by the following overlap tests. */
void fn_80141EA8(Vec3* a, Vec3* b, Vec3* c, u8 triangle)
{
    Vec3* base = &lbl_805B12B0[triangle];
    Vec3* first;
    Vec3* second;
    Vec3* third;
    Vec3* normal;
    float ux, uy, uz, vx, vy, vz, length;
    float ax, ay, az;

    second = base + 2;
    fn_80179AEC(a, second);
    first = base;
    fn_80179AEC(b, first);
    third = base + 4;
    fn_80179AEC(c, third);
    ux = first->x - second->x;
    uy = first->y - second->y;
    uz = first->z - second->z;
    vx = third->x - second->x;
    vy = third->y - second->y;
    vz = third->z - second->z;
    normal = first + 6;
    normal->x = uy * vz - uz * vy;
    normal->y = uz * vx - ux * vz;
    normal->z = ux * vy - uy * vx;
    length = normal->x * normal->x + normal->y * normal->y + normal->z * normal->z;
    if (length != lbl_80650410) {
        length = fn_800ED720(length);
        normal->x /= length;
        normal->y /= length;
        normal->z /= length;
    }
    lbl_8064D030[triangle] = normal->x * second->x +
                            normal->y * second->y - normal->z * second->z;
    ax = normal->x < lbl_80650410 ? -normal->x : normal->x;
    ay = normal->y < lbl_80650410 ? -normal->y : normal->y;
    az = normal->z < lbl_80650410 ? -normal->z : normal->z;
    if (ax > ay) {
        if (ax > az) { lbl_8064D02C[triangle] = 1; lbl_8064D028[triangle] = 2; }
        else         { lbl_8064D02C[triangle] = 0; lbl_8064D028[triangle] = 1; }
    } else {
        if (az > ay) { lbl_8064D02C[triangle] = 0; lbl_8064D028[triangle] = 1; }
        else         { lbl_8064D02C[triangle] = 0; lbl_8064D028[triangle] = 2; }
    }
}
