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
extern GXRenderModeObj GXNtsc480IntDf, GXMpal480IntDf, GXPal528IntDf, GXEurgb60Hz480IntDf;
extern GXColor lbl_80651660, lbl_80651664, lbl_80651668;
extern f32 lbl_8065166C, lbl_80651670, lbl_80651674;
extern u32 VIGetTvFormat(void);
extern GXTexRegion *__GXDefaultTexRegionCallback(GXTexObj *, u32);
extern GXTlutRegion *__GXDefaultTlutRegionCallback(u32);
extern GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback);
extern GXTlutRegionCallback GXSetTlutRegionCallback(GXTlutRegionCallback);
extern void GXSetCopyClear(GXColor, u32);
extern void GXSetChanAmbColor(s32, GXColor);
extern void GXSetChanMatColor(s32, GXColor);
extern void GXSetFog(s32, GXColor, f32, f32, f32, f32);
extern void GXLoadPosMtxImm(Mtx, u32);
extern void GXLoadNrmMtxImm(Mtx, u32);
extern void GXLoadTexMtxImm(Mtx, u32, s32);
extern void GXSetViewport(f32, f32, f32, f32, f32, f32);
extern u32 GXSetDispCopyYScale(f32);
extern void GXSetCopyFilter(u8, u8 [12][2], u8, u8 [7]);
extern void GXSetArray(s32, void *, u8);
extern void GXClearVtxDesc(void);
extern void GXInvalidateVtxCache(void);
extern void GXSetTexCoordGen2(s32, s32, s32, s32, s32, s32);
extern void GXSetNumTexGens(s32);
extern void GXPokeAlphaMode(s32, s32);
extern void GXPokeAlphaRead(s32);
extern void GXPokeAlphaUpdate(s32);
extern void GXPokeBlendMode(s32, s32, s32, s32);
extern void GXPokeColorUpdate(s32);
extern void GXPokeDstAlpha(s32, s32);
extern void GXPokeDither(s32);
extern void GXPokeZMode(s32, s32, s32);
extern void GXSetLineWidth(s32, s32);
extern void GXSetPointSize(s32, s32);
extern void GXEnableTexOffsets(s32, s32, s32);
extern void GXSetCullMode(s32);
extern void GXSetCoPlanar(s32);
extern void GXSetDispCopySrc(s32, s32, u16, u16);
extern void GXSetDispCopyDst(u16, u16);
extern void GXSetDispCopyFrame2Field(s32);
extern void GXSetCopyClamp(s32);
extern void GXSetDispCopyGamma(s32);
extern void GXClearBoundingBox(void);
extern void GXSetNumChans(s32);
extern void GXSetChanCtrl(s32, s32, s32, s32, s32, s32, s32);
extern void GXInvalidateTexAll(void);
extern void GXSetIndTexCoordScale(s32, s32, s32);
extern void GXSetNumIndStages(s32);
extern void GXSetTevDirect(u32);
extern void GXSetTevOp(s32, s32);
extern void GXSetTevKColorSel(s32, s32);
extern void GXSetTevKAlphaSel(s32, s32);
extern void GXSetTevSwapMode(s32, s32, s32);
extern void GXSetTevSwapModeTable(s32, s32, s32, s32, s32);
extern void GXSetAlphaCompare(s32, s32, s32, s32, s32);
extern void GXSetZTexture(s32, s32, s32);
extern void GXSetTevOrder(s32, s32, s32, s32);
extern void GXSetNumTevStages(s32);
extern void GXSetFogRangeAdj(s32, s32, s32);
extern void GXSetBlendMode(s32, s32, s32, s32);
extern void GXSetColorUpdate(s32);
extern void GXSetAlphaUpdate(s32);
extern void GXSetZMode(s32, s32, s32);
extern void GXSetZCompLoc(s32);
extern void GXSetPixelFmt(s32, s32);
extern void GXSetDither(s32);
extern void GXSetDstAlpha(s32, s32);
extern void GXSetFieldMask(s32, s32);
extern void GXSetFieldMode(u8, s32);
extern void GXSetCurrentMtx(s32);
extern void GXSetScissor(s32, s32, u16, u16);
extern void GXSetScissorBoxOffset(s32, s32);
extern void GXSetClipMode(s32);
extern void GXSetGPMetric(s32, s32);
extern void GXClearGPMetric(void);

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
        mode = &GXNtsc480IntDf;
        break;
    case 1:
        mode = &GXPal528IntDf;
        break;
    case 5:
        mode = &GXEurgb60Hz480IntDf;
        break;
    case 2:
        mode = &GXMpal480IntDf;
        break;
    default:
        mode = &GXNtsc480IntDf;
        break;
    }
    /* Clear color, texture coordinates, and vertex input. */
    GXSetCopyClear(clearColor, 0xFFFFFF);
    GXSetTexCoordGen2(0, 1, 4, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2(1, 1, 5, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2(2, 1, 6, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2(3, 1, 7, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2(4, 1, 8, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2(5, 1, 9, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2(6, 1, 0xA, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2(7, 1, 0xB, 0x3C, 0, 0x7D);
    GXSetNumTexGens(1);
    GXClearVtxDesc();
    GXInvalidateVtxCache();
    for (i = 9; i <= 24; i++) {
        /* ASM: mr copies the loop index into the GX attribute argument.
         * C's induction-variable lowering emits addi instead of retail's mr. */
        asm { mr attr, i }
        GXSetArray(attr, gx, 0);
    }
    GXSetLineWidth(6, 0);
    GXSetPointSize(6, 0);
    GXEnableTexOffsets(0, 0, 0);
    GXEnableTexOffsets(1, 0, 0);
    GXEnableTexOffsets(2, 0, 0);
    GXEnableTexOffsets(3, 0, 0);
    GXEnableTexOffsets(4, 0, 0);
    GXEnableTexOffsets(5, 0, 0);
    GXEnableTexOffsets(6, 0, 0);
    GXEnableTexOffsets(7, 0, 0);
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
    GXLoadPosMtxImm(identity, 0);
    GXLoadNrmMtxImm(identity, 0);
    GXSetCurrentMtx(0);
    GXLoadTexMtxImm(identity, 0x3C, 0);
    GXLoadTexMtxImm(identity, 0x7D, 0);
    GXSetViewport(lbl_80651670, lbl_80651670, (f32) mode->fbWidth, (f32) mode->xfbHeight, lbl_80651670, lbl_8065166C);
    GXSetCoPlanar(0);
    GXSetCullMode(2);
    GXSetClipMode(0);
    GXSetScissor(0, 0, mode->fbWidth, mode->efbHeight);
    GXSetScissorBoxOffset(0, 0);
    /* Default lighting channels. */
    GXSetNumChans(0);
    GXSetChanCtrl(4, 0, 0, 1, 0, 0, 2);
    GXSetChanAmbColor(4, black);
    GXSetChanMatColor(4, white);
    GXSetChanCtrl(5, 0, 0, 1, 0, 0, 2);
    GXSetChanAmbColor(5, black);
    GXSetChanMatColor(5, white);
    /* Texture cache and region allocation callbacks. */
    GXInvalidateTexAll();
    i = 0;
    gx->texRegionIndex = i;
    gx->ciRegionIndex = i;
    GXSetTexRegionCallback(__GXDefaultTexRegionCallback);
    GXSetTlutRegionCallback(__GXDefaultTlutRegionCallback);
    /* TEV stage orders, constant selections, and swap tables. */
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevOrder(1, 1, 1, 4);
    GXSetTevOrder(2, 2, 2, 4);
    GXSetTevOrder(3, 3, 3, 4);
    GXSetTevOrder(4, 4, 4, 4);
    GXSetTevOrder(5, 5, 5, 4);
    GXSetTevOrder(6, 6, 6, 4);
    GXSetTevOrder(7, 7, 7, 4);
    GXSetTevOrder(8, 0xFF, 0xFF, 0xFF);
    GXSetTevOrder(9, 0xFF, 0xFF, 0xFF);
    GXSetTevOrder(0xA, 0xFF, 0xFF, 0xFF);
    GXSetTevOrder(0xB, 0xFF, 0xFF, 0xFF);
    GXSetTevOrder(0xC, 0xFF, 0xFF, 0xFF);
    GXSetTevOrder(0xD, 0xFF, 0xFF, 0xFF);
    GXSetTevOrder(0xE, 0xFF, 0xFF, 0xFF);
    GXSetTevOrder(0xF, 0xFF, 0xFF, 0xFF);
    GXSetNumTevStages(1);
    GXSetTevOp(0, 3);
    GXSetAlphaCompare(7, 0, 0, 7, 0);
    GXSetZTexture(0, 0x11, 0);
    for (; i < 16; i++) {
        GXSetTevKColorSel((s32)i, 6);
        GXSetTevKAlphaSel((s32)i, 0);
        GXSetTevSwapMode((s32)i, 0, 0);
    }
    GXSetTevSwapModeTable(0, 0, 1, 2, 3);
    GXSetTevSwapModeTable(1, 0, 0, 0, 3);
    GXSetTevSwapModeTable(2, 1, 1, 1, 3);
    GXSetTevSwapModeTable(3, 2, 2, 2, 3);
    for (i = 0; i < 16; i++) {
        GXSetTevDirect(i);
    }
    GXSetNumIndStages(0);
    GXSetIndTexCoordScale(0, 0, 0);
    GXSetIndTexCoordScale(1, 0, 0);
    GXSetIndTexCoordScale(2, 0, 0);
    GXSetIndTexCoordScale(3, 0, 0);
    /* Fog, blending, depth, and EFB pixel state. */
    GXSetFog(0, black, lbl_80651670, lbl_8065166C, lbl_80651674, lbl_8065166C);
    GXSetFogRangeAdj(0, 0, 0);
    GXSetBlendMode(0, 4, 5, 0);
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(1);
    GXSetZMode(1, 3, 1);
    GXSetZCompLoc(1);
    GXSetDither(1);
    GXSetDstAlpha(0, 0);
    GXSetPixelFmt(0, 0);
    GXSetFieldMask(1, 1);
    if ((s32) mode->viHeight == (s32) (mode->xfbHeight * 2)) {
        halfAspect = 1;
    } else {
        halfAspect = 0;
    }
    GXSetFieldMode(mode->fieldRendering, halfAspect);
    /* Display-copy dimensions, filtering, and clear behavior. */
    GXSetDispCopySrc(0, 0, mode->fbWidth, mode->efbHeight);
    GXSetDispCopyDst(mode->fbWidth, mode->efbHeight);
    GXSetDispCopyYScale((f32) mode->xfbHeight / (f32) mode->efbHeight);
    GXSetCopyClamp(3);
    GXSetCopyFilter(mode->aa, mode->samplePattern, 1, mode->vfilter);
    GXSetDispCopyGamma(0);
    GXSetDispCopyFrame2Field(0);
    GXClearBoundingBox();
    /* Direct EFB pixel operations and performance counters. */
    GXPokeColorUpdate(1);
    GXPokeAlphaUpdate(1);
    GXPokeDither(0);
    GXPokeBlendMode(0, 0, 1, 0xF);
    GXPokeAlphaMode(7, 0);
    GXPokeAlphaRead(1);
    GXPokeDstAlpha(0, 0);
    GXPokeZMode(1, 7, 1);
    GXSetGPMetric(0x23, 0x16);
    GXClearGPMetric();
}
