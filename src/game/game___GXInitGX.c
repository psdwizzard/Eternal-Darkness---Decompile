/* Default GX state established after FIFO and hardware initialization. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef int s32;
typedef float f32;
typedef struct GXColor {
    u8 r, g, b, a;
} GXColor;
typedef f32 Mtx[3][4];
typedef struct GXRenderModeObj {
    u32 viTVmode;
    u16 fbWidth, efbHeight, xfbHeight;
    u16 viXOrigin, viYOrigin, viWidth, viHeight;
    u32 xfbMode;
    u8 fieldRendering, aa;
    u8 samplePattern[12][2];
    u8 vfilter[7];
} GXRenderModeObj;
typedef struct GXData {
    u8 state[0x2C8];
    u32 texRegionIndex, ciRegionIndex;
} GXData;
typedef struct GXTexObj GXTexObj;
typedef struct GXTexRegion GXTexRegion;
typedef struct GXTlutRegion GXTlutRegion;
typedef GXTexRegion *(*GXTexRegionCallback)(GXTexObj *, u32);
typedef GXTlutRegion *(*GXTlutRegionCallback)(u32);
extern GXData *gx;
extern GXRenderModeObj lbl_802FEF98, lbl_802FEFD4, lbl_802FF010, lbl_802FF04C;
extern GXColor lbl_80651660, lbl_80651664, lbl_80651668;
extern f32 lbl_8065166C, lbl_80651670, lbl_80651674;
extern u32 VIGetTvFormat(void);
extern GXTexRegion *fn_80222A90(GXTexObj *, u32);
extern GXTlutRegion *fn_80222B0C(u32);
extern GXTexRegionCallback fn_80228DE4(GXTexRegionCallback);
extern GXTlutRegionCallback fn_80228DF8(GXTlutRegionCallback);
extern void fn_80227290(GXColor, u32);
extern void fn_80227D50(s32, GXColor);
extern void fn_80227EB8(s32, GXColor);
extern void fn_8022A328(s32, GXColor, f32, f32, f32, f32);
extern void fn_8022B690(Mtx, u32);
extern void fn_8022B6CC(Mtx, u32);
extern void fn_8022B748(Mtx, u32, s32);
extern void fn_8022B94C(f32, f32, f32, f32, f32, f32);
extern u32 fn_802271BC(f32);
extern void fn_802272F8(u8, u8 [12][2], u8, u8 [7]);
extern void fn_80225F4C(s32, void *, u8);
extern void fn_802254D0(void);
extern void fn_80225FD8(void);
extern void fn_80225FE8(s32, s32, s32, s32, s32, s32);
extern void fn_802262B8(s32);
extern void fn_802266D4(s32, s32);
extern void fn_802266E8(s32);
extern void fn_802266FC(s32);
extern void fn_80226718(s32, s32, s32, s32);
extern void fn_802267A0(s32);
extern void fn_802267BC(s32, s32);
extern void fn_802267D0(s32);
extern void fn_802267EC(s32, s32, s32);
extern void fn_80226C18(s32, s32);
extern void fn_80226C70(s32, s32);
extern void fn_80226CC4(s32, s32, s32);
extern void fn_80226D28(s32);
extern void fn_80226D78(s32);
extern void fn_80226DE0(s32, s32, u16, u16);
extern void fn_80226F60(u16, u16);
extern void fn_80227114(s32);
extern void fn_80227140(s32);
extern void fn_80227520(s32);
extern void fn_8022783C(void);
extern void fn_80228020(s32);
extern void fn_8022806C(s32, s32, s32, s32, s32, s32, s32);
extern void fn_80228D9C(void);
extern void fn_80229490(s32, s32, s32);
extern void fn_8022979C(s32);
extern void fn_802297C8(u32);
extern void fn_80229964(s32, s32);
extern void fn_80229E74(s32, s32);
extern void fn_80229EE0(s32, s32);
extern void fn_80229F4C(s32, s32, s32);
extern void fn_80229FA4(s32, s32, s32, s32, s32);
extern void fn_8022A044(s32, s32, s32, s32, s32);
extern void fn_8022A094(s32, s32, s32);
extern void fn_8022A118(s32, s32, s32, s32);
extern void fn_8022A2F4(s32);
extern void fn_8022A4D8(s32, s32, s32);
extern void fn_8022A5D8(s32, s32, s32, s32);
extern void fn_8022A6DC(s32);
extern void fn_8022A71C(s32);
extern void fn_8022A75C(s32, s32, s32);
extern void fn_8022A7D4(s32);
extern void fn_8022A814(s32, s32);
extern void fn_8022A924(s32);
extern void fn_8022A964(s32, s32);
extern void fn_8022A9B8(s32, s32);
extern void fn_8022A9F0(u8, s32);
extern void fn_8022B70C(s32);
extern void fn_8022B970(s32, s32, u16, u16);
extern void fn_8022BA20(s32, s32);
extern void fn_8022BA64(s32);
extern void fn_8022BB10(s32, s32);
extern void fn_8022C3A8(void);

void __GXInitGX(void) {
    Mtx identity;
    GXColor clearColor, black, white;
    GXRenderModeObj *mode;
    s32 tvFormat;
    s32 halfAspect;
    register u32 i;
    register s32 attr;

    clearColor = lbl_80651660;
    black = lbl_80651664;
    white = lbl_80651668;
    tvFormat = VIGetTvFormat();
    switch (tvFormat) {
    case 0:
        mode = &lbl_802FEF98;
        break;
    case 1:
        mode = &lbl_802FF010;
        break;
    case 5:
        mode = &lbl_802FF04C;
        break;
    case 2:
        mode = &lbl_802FEFD4;
        break;
    default:
        mode = &lbl_802FEF98;
        break;
    }
    /* Clear color, texture coordinates, and vertex input. */
    fn_80227290(clearColor, 0xFFFFFF);
    fn_80225FE8(0, 1, 4, 0x3C, 0, 0x7D);
    fn_80225FE8(1, 1, 5, 0x3C, 0, 0x7D);
    fn_80225FE8(2, 1, 6, 0x3C, 0, 0x7D);
    fn_80225FE8(3, 1, 7, 0x3C, 0, 0x7D);
    fn_80225FE8(4, 1, 8, 0x3C, 0, 0x7D);
    fn_80225FE8(5, 1, 9, 0x3C, 0, 0x7D);
    fn_80225FE8(6, 1, 0xA, 0x3C, 0, 0x7D);
    fn_80225FE8(7, 1, 0xB, 0x3C, 0, 0x7D);
    fn_802262B8(1);
    fn_802254D0();
    fn_80225FD8();
    for (i = 9; i <= 24; i++) {
        /* ASM: mr copies the loop index into the GX attribute argument.
         * C's induction-variable lowering emits addi instead of retail's mr. */
        asm { mr attr, i }
        fn_80225F4C(attr, gx, 0);
    }
    fn_80226C18(6, 0);
    fn_80226C70(6, 0);
    fn_80226CC4(0, 0, 0);
    fn_80226CC4(1, 0, 0);
    fn_80226CC4(2, 0, 0);
    fn_80226CC4(3, 0, 0);
    fn_80226CC4(4, 0, 0);
    fn_80226CC4(5, 0, 0);
    fn_80226CC4(6, 0, 0);
    fn_80226CC4(7, 0, 0);
    /* Identity transforms and the render-mode viewport. */
    identity[0][0] = lbl_8065166C;
    identity[0][1] = lbl_80651670;
    identity[0][2] = lbl_80651670;
    identity[0][3] = lbl_80651670;
    identity[1][0] = lbl_80651670;
    identity[1][1] = lbl_8065166C;
    identity[1][2] = lbl_80651670;
    identity[1][3] = lbl_80651670;
    identity[2][0] = lbl_80651670;
    identity[2][1] = lbl_80651670;
    identity[2][2] = lbl_8065166C;
    identity[2][3] = lbl_80651670;
    fn_8022B690(identity, 0);
    fn_8022B6CC(identity, 0);
    fn_8022B70C(0);
    fn_8022B748(identity, 0x3C, 0);
    fn_8022B748(identity, 0x7D, 0);
    fn_8022B94C(lbl_80651670, lbl_80651670, (f32) mode->fbWidth, (f32) mode->xfbHeight, lbl_80651670, lbl_8065166C);
    fn_80226D78(0);
    fn_80226D28(2);
    fn_8022BA64(0);
    fn_8022B970(0, 0, mode->fbWidth, mode->efbHeight);
    fn_8022BA20(0, 0);
    /* Default lighting channels. */
    fn_80228020(0);
    fn_8022806C(4, 0, 0, 1, 0, 0, 2);
    fn_80227D50(4, black);
    fn_80227EB8(4, white);
    fn_8022806C(5, 0, 0, 1, 0, 0, 2);
    fn_80227D50(5, black);
    fn_80227EB8(5, white);
    /* Texture cache and region allocation callbacks. */
    fn_80228D9C();
    i = 0;
    gx->texRegionIndex = i;
    gx->ciRegionIndex = i;
    fn_80228DE4(fn_80222A90);
    fn_80228DF8(fn_80222B0C);
    /* TEV stage orders, constant selections, and swap tables. */
    fn_8022A118(0, 0, 0, 4);
    fn_8022A118(1, 1, 1, 4);
    fn_8022A118(2, 2, 2, 4);
    fn_8022A118(3, 3, 3, 4);
    fn_8022A118(4, 4, 4, 4);
    fn_8022A118(5, 5, 5, 4);
    fn_8022A118(6, 6, 6, 4);
    fn_8022A118(7, 7, 7, 4);
    fn_8022A118(8, 0xFF, 0xFF, 0xFF);
    fn_8022A118(9, 0xFF, 0xFF, 0xFF);
    fn_8022A118(0xA, 0xFF, 0xFF, 0xFF);
    fn_8022A118(0xB, 0xFF, 0xFF, 0xFF);
    fn_8022A118(0xC, 0xFF, 0xFF, 0xFF);
    fn_8022A118(0xD, 0xFF, 0xFF, 0xFF);
    fn_8022A118(0xE, 0xFF, 0xFF, 0xFF);
    fn_8022A118(0xF, 0xFF, 0xFF, 0xFF);
    fn_8022A2F4(1);
    fn_80229964(0, 3);
    fn_8022A044(7, 0, 0, 7, 0);
    fn_8022A094(0, 0x11, 0);
    for (; i < 16; i++) {
        fn_80229E74((s32)i, 6);
        fn_80229EE0((s32)i, 0);
        fn_80229F4C((s32)i, 0, 0);
    }
    fn_80229FA4(0, 0, 1, 2, 3);
    fn_80229FA4(1, 0, 0, 0, 3);
    fn_80229FA4(2, 1, 1, 1, 3);
    fn_80229FA4(3, 2, 2, 2, 3);
    for (i = 0; i < 16; i++) {
        fn_802297C8(i);
    }
    fn_8022979C(0);
    fn_80229490(0, 0, 0);
    fn_80229490(1, 0, 0);
    fn_80229490(2, 0, 0);
    fn_80229490(3, 0, 0);
    /* Fog, blending, depth, and EFB pixel state. */
    fn_8022A328(0, black, lbl_80651670, lbl_8065166C, lbl_80651674, lbl_8065166C);
    fn_8022A4D8(0, 0, 0);
    fn_8022A5D8(0, 4, 5, 0);
    fn_8022A6DC(1);
    fn_8022A71C(1);
    fn_8022A75C(1, 3, 1);
    fn_8022A7D4(1);
    fn_8022A924(1);
    fn_8022A964(0, 0);
    fn_8022A814(0, 0);
    fn_8022A9B8(1, 1);
    if ((s32) mode->viHeight == (s32) (mode->xfbHeight * 2)) {
        halfAspect = 1;
    } else {
        halfAspect = 0;
    }
    fn_8022A9F0(mode->fieldRendering, halfAspect);
    /* Display-copy dimensions, filtering, and clear behavior. */
    fn_80226DE0(0, 0, mode->fbWidth, mode->efbHeight);
    fn_80226F60(mode->fbWidth, mode->efbHeight);
    fn_802271BC((f32) mode->xfbHeight / (f32) mode->efbHeight);
    fn_80227140(3);
    fn_802272F8(mode->aa, mode->samplePattern, 1, mode->vfilter);
    fn_80227520(0);
    fn_80227114(0);
    fn_8022783C();
    /* Direct EFB pixel operations and performance counters. */
    fn_802267A0(1);
    fn_802266FC(1);
    fn_802267D0(0);
    fn_80226718(0, 0, 1, 0xF);
    fn_802266D4(7, 0);
    fn_802266E8(1);
    fn_802267BC(0, 0);
    fn_802267EC(1, 7, 1);
    fn_8022BB10(0x23, 0x16);
    fn_8022C3A8();
}
