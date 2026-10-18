typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

typedef struct LocalObject {
    u8 data[0x20];
} LocalObject;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

extern Color lbl_8064DEB0;
extern Color lbl_8064DEB4;
extern float lbl_8064DEA8;
extern float lbl_8064DEB8;
extern float lbl_8064DEBC;
extern float lbl_8064DEC0;
extern u32 lbl_8064CBA0;
extern s32 lbl_8064CBA4;
extern void* lbl_8064D740;
extern void* lbl_8064D74C;
extern char lbl_8063BEC0[];
extern char lbl_802515D0[];
extern char lbl_802515E0[];

extern void* fn_8012070C(void);
extern void GXSetCopyClear(Color, u32);
extern void fn_801F44B8(void*);
extern void GXSetViewport(float, float, float, float, float, float);
extern void GXSetScissor(s32, s32, s32, s32);
extern void GXSetBlendMode(s32, s32, s32, s32);
extern void GXSetCullMode(s32);
extern void fn_801F10BC(s32, s32, s32);
extern void fn_801F0044(void);
extern void GXSetColorUpdate(s32);
extern void GXSetAlphaUpdate(s32);
extern void GXSetNumChans(s32);
extern void GXSetChanCtrl(s32, s32, s32, s32, s32, s32, s32);
extern void GXSetZMode(s32, s32, s32);
extern void fn_801EF530(void);
extern void fn_801EF580(void*);
extern void* fn_801EB080(void);
extern void GXCopyDisp(void*, s32);
extern void GXSetDrawDone(void);
extern void GXSetDrawSync(s32);
extern void OSSendMessage(void*, s32, s32);
extern void fn_801EFEC4(s32);
extern void fn_8015DB84(void*, LocalObject*, s32);
extern void GXLoadTexObj(LocalObject*, s32);
extern void fn_801ECB40(u8);
extern void GXSetTevColor(s32, Color);
extern void GXSetTevKColorSel(s32, s32);
extern void GXSetTexCoordGen2(s32, s32, s32, s32, s32, s32);
extern void GXSetTevColorOp(s32, s32, s32, s32, s32, s32);
extern void GXSetTevColorIn(s32, s32, s32, s32, s32);
extern void GXSetTevAlphaIn(s32, s32, s32, s32, s32);
extern void GXSetTevAlphaOp(s32, s32, s32, s32, s32, s32);
extern void GXSetNumTexGens(s32);
extern void GXSetNumTevStages(s32);
extern void fn_801A8D38(int);
extern void fn_801A8FE8(void*, void*, s32, s32, s32);

void fn_8001DB04(u32 mode)
{
    LocalObject object;
    s32 i;
    void* destination;
    u32 alpha = 0;
    Color color = lbl_8064DEB0;
    Color tint = lbl_8064DEB4;
    u32 channel;

    destination = fn_8012070C();
    channel = lbl_8064CBA0;

    tint.r = channel;
    tint.g = channel;
    tint.b = channel;
    GXSetCopyClear(tint, 0xFFFFFF);
    fn_801F44B8(lbl_8064D740);
    GXSetViewport(lbl_8064DEA8, lbl_8064DEA8, lbl_8064DEB8,
                lbl_8064DEBC, lbl_8064DEA8, lbl_8064DEC0);
    GXSetScissor(0, 0, 640, 480);
    GXSetBlendMode(1, 4, 5, 0);
    GXSetCullMode(0);
    fn_801F10BC(0, 0, 0);
    fn_801F0044();
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(0);
    GXSetNumChans(1);
    GXSetChanCtrl(4, 0, 0, 0, 0, 0, 2);
    GXSetChanCtrl(5, 0, 0, 0, 0, 0, 2);
    GXSetZMode(1, 3, 1);
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(1);

    for (i = 0; i < 2; i++) {
        void* value;
        fn_801EF530();
        fn_801EF580(lbl_8064D74C);
        value = fn_801EB080();
        GXCopyDisp(value, 1);
        GXSetDrawDone();
        GXSetDrawSync(0xBEEF);
        OSSendMessage(lbl_8063BEC0, 0, 1);
        fn_801EFEC4(1);
    }

    while ((s32)alpha < 255) {
        void* value;
        fn_801EF530();
        fn_801EF580(lbl_8064D74C);
        alpha += 5;
        if ((s32)alpha > 255) {
            alpha = 255;
        }
        color.a = alpha;
        fn_8015DB84(destination, &object, mode);
        GXLoadTexObj(&object, 0);
        fn_801ECB40((u8)(lbl_8064CBA0 + 1));
        fn_801ECB40((u8)lbl_8064CBA0);
        GXSetTevColor(1, color);
        GXSetTevKColorSel(0, 13);
        GXSetTexCoordGen2(0, 1, 4, 60, 0, 125);
        GXSetTevColorOp(0, 0, 0, 0, 1, 0);
        GXSetTevColorIn(0, 15, 12, 8, 14);
        GXSetTevAlphaIn(0, 7, 7, 7, 1);
        GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        fn_801A8D38(5);
        if ((s32)mode == 0 && lbl_8064CBA4 == 1) {
            fn_801A8FE8(lbl_802515D0, lbl_802515E0 + 0x30, 0, 0, 5);
        } else {
            fn_801A8FE8(lbl_802515D0, lbl_802515E0, 0, 0, 5);
        }
        value = fn_801EB080();
        GXCopyDisp(value, 1);
        GXSetDrawDone();
        GXSetDrawSync(0xBEEF);
        OSSendMessage(lbl_8063BEC0, 0, 1);
        fn_801EFEC4(1);
    }
}
