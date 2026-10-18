typedef short s16;
typedef int s32;
typedef unsigned int u32;
typedef float f32;

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef f32 Mtx[3][4];

extern const Vec3 lbl_80238C60;
extern const f32 lbl_8064DFB8;
extern const f32 lbl_8064DFBC;
extern const f32 lbl_8064DFC0;
extern const f32 lbl_8064DFC4;
extern volatile const f32 lbl_8064DFC8;
extern const f32 lbl_8064DFCC;
extern const f32 lbl_8064DFD0;
extern unsigned char lbl_8063D378[];

extern s16 fn_80144A2C(u32, s32, s32, s32);
extern u32 fn_80144710(u32, s32, s32);
extern void PSVECSubtract();
extern f32 PSVECMag(const Vec3*);
extern void PSVECScale(const Vec3*, Vec3*, f32);
extern void PSVECAdd(const Vec3*, const Vec3*, Vec3*);
extern void PSMTXRotRad(Mtx, s32, f32);
extern void PSMTXRotAxisRad(Mtx, const Vec3*, f32);
extern void PSMTXMultVec(Mtx, const Vec3*, Vec3*);
extern void PSVECCrossProduct(const Vec3*, const Vec3*, Vec3*);
extern void PSVECNormalize(const Vec3*, Vec3*);
extern f32 fn_80027614(f32);

void fn_800272B4(Vec3* from, Vec3* to)
{
    Vec3 direction;
    Vec3 offset = lbl_80238C60;
    Vec3 axis;
    Mtx roll_matrix;
    Mtx vertical_matrix;
    s16 horizontal = fn_80144A2C(0x30000, 31, 8, 0);
    s16 forward = fn_80144A2C(0xC0000, 31, 15, 0);
    s16 roll = fn_80144A2C(0x300000, 31, -3, 0);
    s16 vertical = fn_80144A2C(0xC00000, 31, 3, 0);
    f32 sum;
    f32 clamped;
    f32 z;
    f32 result;

    if (!fn_80144710(0x1000000, 1, 0)) {
        horizontal *= 4;
        forward *= 4;
        roll *= 4;
        vertical *= 4;
    }

    PSVECSubtract(to, from, &direction);
    PSVECScale(&direction, &direction, lbl_8064DFB8 / PSVECMag(&direction));

    sum = fn_80027614(direction.x) + fn_80027614(direction.y);
    if ((s16)horizontal && lbl_8064DFBC != sum) {
        offset.x += (s16)horizontal * (direction.y / sum);
        offset.y -= (s16)horizontal * (direction.x / sum);
    }

    if ((s16)forward) {
        offset.x += (s16)forward * direction.x;
        offset.y += (s16)forward * direction.y;
        offset.z += (s16)forward * direction.z;
    }
    PSVECAdd(from, &offset, from);

    if ((s16)roll) {
        PSMTXRotRad(roll_matrix, 90, lbl_8064DFC0 * (s16)roll);
        PSMTXMultVec(roll_matrix, &direction, &direction);
    }

    if ((s16)vertical) {
        PSVECCrossProduct(&direction, (Vec3*)(lbl_8063D378 + 0x48), &axis);
        PSVECNormalize(&axis, &axis);
        PSMTXRotAxisRad(vertical_matrix, &axis, lbl_8064DFC4 * (s16)vertical);
        PSMTXMultVec(vertical_matrix, &direction, &direction);
        z = direction.z;
        clamped = lbl_8064DFC8;
        if (z > clamped) {
            clamped = z;
        }
        if (lbl_8064DFCC < clamped) {
            result = lbl_8064DFCC;
        } else {
            result = lbl_8064DFC8;
            if (z > result) {
                result = z;
            }
        }
        direction.z = result;
    }

    to->x = from->x + direction.x * lbl_8064DFD0;
    to->y = from->y + direction.y * lbl_8064DFD0;
    to->z = from->z + direction.z * lbl_8064DFD0;
}
