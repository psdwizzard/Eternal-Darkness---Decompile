typedef unsigned char u8;
typedef unsigned long u32;

typedef struct DrawCommand {
    u32 color;
} DrawCommand;

extern float lbl_80651348, lbl_80651378, lbl_8065137C, lbl_806513E4, lbl_806513E8;
extern char lbl_802FC2C0[];

extern void C_MTXOrtho();
extern void GXSetProjection();
extern void PSMTXIdentity();
extern void GXLoadPosMtxImm();
extern void fn_801ED468();
extern void GXSetCullMode();
extern void GXSetNumChans();
extern void GXSetNumTexGens();
extern void GXSetNumTevStages();
extern void fn_801F3938();
extern void GXSetTevOrder();
extern void GXSetTevColor();
extern void GXSetTevKColorSel();
extern void GXSetTevColorOp();
extern void GXSetTevColorIn();
extern void GXSetTevAlphaOp();
extern void GXSetTevAlphaIn();
extern void fn_8015DB84();
extern void GXLoadTexObj();
extern void fn_801ECF50();
extern void GXBegin();
extern void fn_801F3924();
extern void fn_801F3914();
extern void fn_801F0AFC();
extern void fn_801ECC4C();
extern void fn_801A8D38();

void fn_801F3960(DrawCommand* command)
{
    float projection[16];
    float matrix[12];
    u32 color;
    u8 texture[0x20];

    if (((u8*)command)[3] != 0) {
        C_MTXOrtho(projection, lbl_80651348, lbl_8065137C,
                    lbl_80651348, lbl_80651378, lbl_80651348, lbl_806513E4);
        GXSetProjection(projection, 1);
        PSMTXIdentity(matrix);
        GXLoadPosMtxImm(matrix, 0);
        fn_801ED468(0);
        GXSetCullMode(0);
        GXSetNumChans(1);
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        GXSetCullMode(0);
        fn_801F3938(0, 1, 4, 60);
        GXSetTevOrder(0, 0, 0, 255);
        color = command->color;
        GXSetTevColor(1, &color);
        GXSetTevKColorSel(0, 13);
        GXSetTevColorOp(0, 0, 0, 0, 1, 0);
        GXSetTevColorIn(0, 15, 2, 8, 14);
        GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);
        GXSetTevAlphaIn(0, 7, 7, 7, 1);
        fn_8015DB84(lbl_802FC2C0, texture, 0);
        GXLoadTexObj(texture, 0);
        fn_801ECF50(8);
        GXBegin(128, 2, 4);
        fn_801F3924(0, 0, 0);
        fn_801F3914(lbl_80651348, lbl_80651348);
        fn_801F3924(0x5000, 0, 0);
        fn_801F3914(lbl_806513E8, lbl_80651348);
        fn_801F3924(0x5000, 0x3C00, 0);
        fn_801F3914(lbl_806513E8, lbl_806513E8);
        fn_801F3924(0, 0x3C00, 0);
        fn_801F3914(lbl_80651348, lbl_806513E8);
        fn_801F0AFC();
        GXSetCullMode(1);
        fn_801ECC4C();
        fn_801A8D38(5);
    }
}
