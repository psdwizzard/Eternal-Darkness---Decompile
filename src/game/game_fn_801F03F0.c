typedef unsigned char u8;
typedef unsigned long u32;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Color { u8 r, g, b, a; } Color;
typedef struct BoundsCamera {
    float min_x, min_y, unused_8;
    float max_x, max_y, unused_14;
    Vec3 eye;
    float unused_24[3];
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

extern void C_MTXPerspective(void*, float, float, float, float);
extern void GXSetViewport(float, float, float, float, float, float);
extern void GXSetScissor(int, int, int, int);
extern void GXSetProjection(void*, int);
extern void fn_8017AD7C(void*, void*);
extern void C_MTXLookAt(void*, void*, void*, void*);
extern void PSMTXInverse(void*, void*);
extern void PSMTXReorder(void*, void*);
extern float PSVECMag(void*);
extern void GXLoadPosMtxImm(void*, int);
extern void GXLoadNrmMtxImm(void*, int);
extern void GXSetCopyClear(Color*, int);
extern void GXSetBlendMode(int, int, int, int);
extern void GXSetCullMode(int);
extern void fn_801F10BC(int, int, int);
extern void fn_801ECF50(int);
extern void fn_801F0044(void);
extern void fn_801ECC4C(void);
extern void fn_801ECEC8(int, int, int);
extern void GXSetArray(int, void*, int);
extern void fn_801ECD74(void*);
extern Vec3* fn_8015AB00(int);
extern void PSMTXTrans(void*, float, float, float);
extern void PSMTXConcat(void*, void*, void*);
extern void DCFlushRange(void*, u32);
extern void GXSetColorUpdate(int);
extern void GXSetAlphaUpdate(int);
extern void GXSetNumChans(int);
extern void GXSetChanCtrl(int, int, int, int, int, int, int);
extern void GXSetTevSwapModeTable(int, int, int, int, int);
extern void fn_801ECD48(int);
extern void fn_801ECD50(float);

/* NonMatching: behavior-complete camera/render setup reconstruction. GC/1.3
 * emits 1216 bytes versus retail's 1224 with the correct 0x70-byte frame and
 * color temporaries; remaining differences are load scheduling and register
 * selection in the target, normalization, and matrix-construction blocks.
 * Attempt 5: canonical/relocation-strict 92.05556%; preserve NonMatching. */
void fn_801F03F0(BoundsCamera* in, int alternate)
{
    u8* state = lbl_8063BEA0;
    Vec3 target;
    float* matrix;
    float* normalized;
    Vec3* motion;
    Color constructedColor;
    float projection = lbl_80651368;

    target = *(Vec3*)lbl_8023B78C;
    matrix = (float*)(state + 0xC8);
    matrix += lbl_8064D738 * 24;
    if (lbl_8064CBA4 == 1)
        projection = lbl_8065136C;
    {
        /* Snapshot the vector bits before resetting render state. */
        u32 b = ((u32*)&in->eye)[1];
        u32 c = ((u32*)&in->eye)[2];
        u32 a = ((u32*)&in->eye)[0];
        lbl_8064D6F8 = 0;
        ((u32*)&target)[0] = a;
        ((u32*)&target)[1] = b;
        ((u32*)&target)[2] = c;
    }
    if (alternate)
        C_MTXPerspective(state + 0x88, in->projection, projection,
                    lbl_8065134C, lbl_80651370);
    else
        C_MTXPerspective(state + 0x88, in->projection, projection,
                    lbl_8065134C, lbl_80651374);
    GXSetViewport(lbl_80651348, lbl_80651348, lbl_80651378,
                lbl_8065137C, lbl_80651348, lbl_8065134C);
    GXSetScissor(0, 0, 0x280, 0x1E0);
    GXSetProjection(state + 0x88, 0);
    fn_8017AD7C(state + 0x88, state + 0x188);

    if (in->min_x == in->max_x && in->min_y == in->max_y &&
        target.z == lbl_8065134C) {
        in->min_x += lbl_80651380;
        in->min_y += lbl_80651380;
    }
    C_MTXLookAt(state + 0x1C8, in, &target, &in->max_x);
    PSMTXInverse(state + 0x1C8, state + 0x1F8);
    PSMTXReorder(state + 0x1C8, state + 0x228);

    {
        float delta_x = in->max_x - in->min_x;
        float delta_y = in->max_y - in->min_y;
        normalized = (float*)(state + 0x7C);
        normalized[1] = delta_y;
        *(float*)(state + 0x7C) = delta_x;
        normalized[2] = lbl_80651348;
    }
    projection = PSVECMag(normalized);
    *(float*)(state + 0x7C) /= projection;
    normalized[1] /= projection;
    GXLoadPosMtxImm(state + 0x1C8, 0x1B);
    GXLoadNrmMtxImm(state + 0x1C8, 0x1B);

    if (lbl_8064CB50) {
        Color enabledColor = *(Color*)(lbl_802FC5BC + 0x28);
        GXSetCopyClear(&enabledColor, 0xFFFFFF);
    } else {
        Color fallbackColor;
        constructedColor.r = lbl_8064CBA0;
        constructedColor.g = lbl_8064CBA0;
        constructedColor.b = lbl_8064CBA0;
        constructedColor.a = 0xFF;
        fallbackColor = constructedColor;
        GXSetCopyClear(&fallbackColor, 0xFFFFFF);
    }
    GXSetBlendMode(1, 4, 5, 0);
    GXSetCullMode(1);
    fn_801F10BC(0, 0, 0);
    fn_801ECF50(2);
    fn_801F0044();
    fn_801ECC4C();
    fn_801ECEC8(1, 3, 1);
    {
        u8* command = state + 0x258;
        int command_offset = lbl_8064D738 * 0x200;
        GXSetArray(0x18, command + command_offset, 0x40);
    }
    {
        Color color = *(Color*)(lbl_802FC5BC + 0xC);
        fn_801ECD74(&color);
    }

    motion = fn_8015AB00(2);
    if (motion != 0) {
        float rotation[12];
        float* view = (float*)(state + 0x1C8);
        float y, x, z, w, divisor;
        float* matrix2;
        PSMTXTrans(rotation, lbl_80651348, lbl_80651348,
                    lbl_80651384 - motion->x);
        divisor = lbl_80651388;
        y = -view[9];
        x = -view[8];
        w = -view[11];
        z = -view[10];
        x /= divisor;
        y /= divisor;
        z /= divisor;
        w /= divisor;
        matrix[0] = x;
        matrix[1] = y;
        matrix[2] = z;
        matrix[3] = w;
        matrix[4] = lbl_80651348;
        matrix[5] = lbl_80651348;
        matrix[6] = lbl_8065138C;
        matrix[7] = lbl_80651348;
        matrix[8] = lbl_80651348;
        matrix[9] = lbl_80651348;
        matrix[10] = lbl_80651348;
        matrix[11] = lbl_80651348;
        PSMTXConcat(matrix, rotation, matrix);

        matrix2 = (float*)(state + 0xF8 + lbl_8064D738 * 0x60);
        matrix2[0] = lbl_80651390;
        matrix2[1] = lbl_80651348;
        matrix2[2] = lbl_80651348;
        matrix2[3] = lbl_80651348;
        matrix2[4] = lbl_80651348;
        matrix2[5] = lbl_80651390;
        matrix2[6] = lbl_80651348;
        matrix2[7] = lbl_80651348;
        matrix2[8] = lbl_80651348;
        matrix2[9] = lbl_80651348;
        matrix2[10] = lbl_80651348;
        matrix2[11] = lbl_80651348;
        PSMTXTrans(rotation, lbl_8064D6C8, lbl_8064D6CC, lbl_80651348);
        PSMTXConcat(matrix2, rotation, matrix2);
        {
            u8* base = state + 0xC8;
            int offset = lbl_8064D738 * 0x60;
            DCFlushRange(base + offset, 0x60);
        }
        GXSetArray(0x17, state + 0xC8 + lbl_8064D738 * 0x60, 0x30);
    }
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(0);
    GXSetNumChans(1);
    lbl_8064D638 = 1;
    GXSetChanCtrl(4, 0, 0, 0, 0, 0, 2);
    GXSetChanCtrl(5, 0, 0, 0, 0, 0, 2);
    GXSetTevSwapModeTable(0, 0, 1, 2, 3);
    GXSetTevSwapModeTable(1, 0, 0, 0, 0);
    fn_801ECD48(0);
    fn_801ECD50(lbl_8065134C);
}
