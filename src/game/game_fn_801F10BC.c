typedef signed long s32;
typedef unsigned char u8;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef float Mtx[3][4];
typedef struct Entry801F10BC {
    Vec3 position;
    u8 pad[0xC];
    void* object;
    float value;
} Entry801F10BC;

extern s32 lbl_8064D6F4;
extern s32 lbl_8064D754;
extern s32 lbl_8064D750;
extern volatile s32 lbl_8064D6F0;
extern s32 lbl_8064C378;
extern s32 lbl_8064D18C;
extern u8 lbl_802FC5BC[];
extern Entry801F10BC lbl_8063C4F8[];
extern Mtx lbl_8063C068;
extern void GXSetChanCtrl(s32, s32, s32, s32, s32, s32, s32);
extern void GXSetChanMatColor(s32, s32*);
extern void GXSetChanAmbColor(s32, s32*);
extern void PSMTXIdentity(Mtx);
extern void PSMTXQuat(Mtx, void*);
extern void PSMTXConcat(Mtx, Mtx, Mtx);
extern void PSMTXInvXpose(Mtx, Mtx);
extern void GXLoadTexMtxImm(Mtx, s32, s32);
extern void fn_801ED434(s32);

void fn_801F10BC(s32 first, s32 mask, s32 unused)
{
    s32 color0;
    s32 color1;
    s32 color2;
    s32 color3;
    s32 color4;
    s32 color5;
    s32 color6;
    s32 color7;
    s32 best;
    s32 i;
    Mtx matrix;
    Mtx position;

    (void)unused;
    lbl_8064D6F4 = 0;
    lbl_8064D754 = first;
    GXSetChanCtrl(0, 1, 0, 0, first, 2, 1);
    GXSetChanCtrl(2, 0, 0, 0, 0, 0, 2);

    if (first == 0) {
        GXSetChanCtrl(0, 0, 0, 0, 0, 0, 2);
        color0 = *(s32*)(lbl_802FC5BC + 0x0);
        GXSetChanMatColor(0, &color0);
        if ((lbl_8064C378 | 2) == 0) {
            color1 = *(s32*)(lbl_802FC5BC + 0xC);
            GXSetChanMatColor(0, &color1);
        }
    } else {
        color2 = *(s32*)(lbl_802FC5BC + 0xC);
        GXSetChanMatColor(0, &color2);
    }

    color3 = *(s32*)(lbl_802FC5BC + 0x38);
    GXSetChanAmbColor(0, &color3);
    lbl_8064D750 = mask;
    GXSetChanCtrl(1, 1, 0, 0, mask, 0, 0);
    GXSetChanCtrl(3, 0, 0, 0, 0, 0, 2);

    if (mask == 0) {
        GXSetChanCtrl(1, 0, 0, 0, 0, 0, 2);
        color4 = *(s32*)(lbl_802FC5BC + 0x0);
        GXSetChanMatColor(1, &color4);
        if ((lbl_8064C378 | 2) == 0) {
            color5 = *(s32*)(lbl_802FC5BC + 0xC);
            GXSetChanMatColor(1, &color5);
        }
        lbl_8064D6F0 = 0;
    } else {
        best = -1;
        for (i = 0; i < 8; i++) {
            if ((mask & (1 << i)) != 0 && lbl_8063C4F8[i].object != 0 &&
                (best == -1 || lbl_8063C4F8[i].value < 0.0f)) {
                lbl_8063C4F8[i].value = 0.0f;
                best = i;
            }
        }
        if (best != -1) {
            PSMTXIdentity(position);
            position[0][0] = 256.0f * lbl_8063C4F8[best].position.x;
            position[0][1] = 256.0f * lbl_8063C4F8[best].position.y;
            position[0][2] = 256.0f * lbl_8063C4F8[best].position.z;
            PSMTXQuat(matrix, lbl_8063C4F8[best].object);
            PSMTXConcat(lbl_8063C068, matrix, matrix);
            PSMTXInvXpose(matrix, matrix);
            PSMTXConcat(position, matrix, matrix);
            GXLoadTexMtxImm(matrix, 0x2D, 1);
        }
        color6 = *(s32*)(lbl_802FC5BC + 0xC);
        GXSetChanMatColor(1, &color6);
        lbl_8064D6F0 = 1;
    }

    color7 = *(s32*)(lbl_802FC5BC + 0x38);
    GXSetChanAmbColor(1, &color7);

    if (lbl_8064D18C == 0x32) {
        fn_801ED434(2);
        GXSetChanCtrl(1, 1, 0, 0, lbl_8064D750, 0, 0);
    } else if (lbl_8064D6F0 != 0) {
        fn_801ED434(2);
        GXSetChanCtrl(1, 1, 0, 0, lbl_8064D750, 0, 0);
    } else {
        fn_801ED434(1);
        GXSetChanCtrl(1, 0, 0, 0, 0, 0, 2);
    }
}
