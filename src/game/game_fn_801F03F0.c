typedef unsigned char u8;
typedef unsigned long u32;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct BoundsCamera {
    float min_x, min_y, unused_8;
    float max_x, max_y, unused_14;
    Vec3 eye;
    float projection;
} BoundsCamera;

extern u8 lbl_8063BEA0[];
extern float lbl_8023B78C[3];
extern int lbl_8064D738, lbl_8064CBA4, lbl_8064D6F8;
extern int lbl_8064CB50, lbl_8064CBA0, lbl_8064D638;
extern float lbl_8064D6C8, lbl_8064D6CC;
extern const float lbl_80651348, lbl_8065134C, lbl_80651368, lbl_8065136C;
extern const float lbl_80651370, lbl_80651374, lbl_80651378, lbl_8065137C;
extern const float lbl_80651380, lbl_80651384, lbl_80651388, lbl_8065138C;
extern const float lbl_80651390;
extern u8 lbl_802FC5BC[];

extern void fn_802118E0(void*, float, float, float, float);
extern void fn_8022B94C(float, float, float, float, float, float);
extern void fn_8022B970(int, int, int, int);
extern void fn_8022B4B8(void*, int);
extern void fn_8017AD7C(void*, void*);
extern void fn_80211584(void*, void*, void*, void*);
extern void fn_802110A8(void*, void*);
extern void fn_80212154(void*, void*);
extern float fn_80211B08(void*);
extern void fn_8022B690(void*, int);
extern void fn_8022B6CC(void*, int);
extern void fn_80227290(void*, int);
extern void fn_8022A5D8(int, int, int, int);
extern void fn_80226D28(int);
extern void fn_801F10BC(int, int, int);
extern void fn_801ECF50(int);
extern void fn_801F0044(void);
extern void fn_801ECC4C(void);
extern void fn_801ECEC8(int, int, int);
extern void fn_80225F4C(int, void*, int);
extern void fn_801ECD74(void*);
extern Vec3* fn_8015AB00(int);
extern void fn_80211484(void*, float, float, float);
extern void fn_80210FDC(void*, void*, void*);
extern void DCFlushRange(void*, u32);
extern void fn_8022A6DC(int);
extern void fn_8022A71C(int);
extern void fn_80228020(int);
extern void fn_8022806C(int, int, int, int, int, int, int);
extern void fn_80229FA4(int, int, int, int, int);
extern void fn_801ECD48(int);
extern void fn_801ECD50(float);

void fn_801F03F0(BoundsCamera* in, int alternate)
{
    Vec3 target;
    float* matrix;
    float* normalized;
    Vec3* motion;
    u32 color;
    float projection = lbl_80651368;

    target.x = lbl_8023B78C[0];
    target.y = lbl_8023B78C[1];
    target.z = lbl_8023B78C[2];
    matrix = (float*)(lbl_8063BEA0 + 0xC8 + lbl_8064D738 * 0x60);
    if (lbl_8064CBA4 == 1)
        projection = lbl_8065136C;
    target = in->eye;
    lbl_8064D6F8 = 0;
    if (alternate)
        fn_802118E0(lbl_8063BEA0 + 0x88, in->projection, projection,
                    lbl_8065134C, lbl_80651370);
    else
        fn_802118E0(lbl_8063BEA0 + 0x88, in->projection, projection,
                    lbl_8065134C, lbl_80651374);
    fn_8022B94C(lbl_80651348, lbl_80651348, lbl_80651378,
                lbl_8065137C, lbl_80651348, lbl_8065134C);
    fn_8022B970(0, 0, 0x280, 0x1E0);
    fn_8022B4B8(lbl_8063BEA0 + 0x88, 0);
    fn_8017AD7C(lbl_8063BEA0 + 0x88, lbl_8063BEA0 + 0x188);

    if (in->min_x == in->max_x && in->min_y == in->max_y &&
        target.z == lbl_8065134C) {
        in->min_x += lbl_80651380;
        in->min_y += lbl_80651380;
    }
    fn_80211584(lbl_8063BEA0 + 0x1C8, in, &target, &in->max_x);
    fn_802110A8(lbl_8063BEA0 + 0x1C8, lbl_8063BEA0 + 0x1F8);
    fn_80212154(lbl_8063BEA0 + 0x1C8, lbl_8063BEA0 + 0x228);

    normalized = (float*)(lbl_8063BEA0 + 0x7C);
    normalized[0] = in->max_x - in->min_x;
    normalized[1] = in->max_y - in->min_y;
    normalized[2] = lbl_80651348;
    projection = fn_80211B08(normalized);
    normalized[0] /= projection;
    normalized[1] /= projection;
    fn_8022B690(lbl_8063BEA0 + 0x1C8, 0x1B);
    fn_8022B6CC(lbl_8063BEA0 + 0x1C8, 0x1B);

    if (lbl_8064CB50) {
        color = *(u32*)(lbl_802FC5BC + 0x28);
    } else {
        color = ((lbl_8064CBA0 & 0xFF) << 24) | ((lbl_8064CBA0 & 0xFF) << 16) |
                ((lbl_8064CBA0 & 0xFF) << 8) | 0xFF;
    }
    fn_80227290(&color, 0xFFFFFF);
    fn_8022A5D8(1, 4, 5, 0);
    fn_80226D28(1);
    fn_801F10BC(0, 0, 0);
    fn_801ECF50(2);
    fn_801F0044();
    fn_801ECC4C();
    fn_801ECEC8(1, 3, 1);
    fn_80225F4C(0x18, lbl_8063BEA0 + 0x258 + lbl_8064D738 * 0x200, 0x40);
    color = *(u32*)(lbl_802FC5BC + 0xC);
    fn_801ECD74(&color);

    motion = fn_8015AB00(2);
    if (motion != 0) {
        float rotation[12];
        fn_80211484(rotation, lbl_80651348, lbl_80651348,
                    lbl_80651384 - motion->x);
        matrix[0] = -((float*)(lbl_8063BEA0 + 0x1C8))[8] / lbl_80651388;
        matrix[1] = -((float*)(lbl_8063BEA0 + 0x1C8))[9] / lbl_80651388;
        matrix[2] = -((float*)(lbl_8063BEA0 + 0x1C8))[10] / lbl_80651388;
        matrix[3] = -((float*)(lbl_8063BEA0 + 0x1C8))[11] / lbl_80651388;
        matrix[4] = lbl_80651348;
        matrix[5] = lbl_80651348;
        matrix[6] = lbl_8065138C;
        matrix[7] = lbl_80651348;
        matrix[8] = lbl_80651348;
        matrix[9] = lbl_80651348;
        matrix[10] = lbl_80651348;
        matrix[11] = lbl_80651348;
        fn_80210FDC(matrix, rotation, matrix);

        matrix = (float*)(lbl_8063BEA0 + 0xF8 + lbl_8064D738 * 0x60);
        matrix[0] = lbl_80651390;
        matrix[1] = lbl_80651348;
        matrix[2] = lbl_80651348;
        matrix[3] = lbl_80651348;
        matrix[4] = lbl_80651348;
        matrix[5] = lbl_80651390;
        matrix[6] = lbl_80651348;
        matrix[7] = lbl_80651348;
        matrix[8] = lbl_80651348;
        matrix[9] = lbl_80651348;
        matrix[10] = lbl_80651348;
        matrix[11] = lbl_80651348;
        fn_80211484(rotation, lbl_8064D6C8, lbl_8064D6CC, lbl_80651348);
        fn_80210FDC(matrix, rotation, matrix);
        DCFlushRange(lbl_8063BEA0 + 0xC8 + lbl_8064D738 * 0x60, 0x60);
        fn_80225F4C(0x17, lbl_8063BEA0 + 0xC8 + lbl_8064D738 * 0x60, 0x30);
    }
    fn_8022A6DC(1);
    fn_8022A71C(0);
    fn_80228020(1);
    lbl_8064D638 = 1;
    fn_8022806C(4, 0, 0, 0, 0, 0, 2);
    fn_8022806C(5, 0, 0, 0, 0, 0, 2);
    fn_80229FA4(0, 0, 1, 2, 3);
    fn_80229FA4(1, 0, 0, 0, 0);
    fn_801ECD48(0);
    fn_801ECD50(lbl_8065134C);
}
