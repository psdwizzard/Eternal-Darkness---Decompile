typedef unsigned char u8;
typedef unsigned long u32;
typedef signed long s32;

typedef struct ColorF {
    float red, green, blue, alpha;
} ColorF;

typedef struct Color {
    u8 red, green, blue, alpha;
} Color;

extern u32 lbl_8064C384;
extern ColorF lbl_8063C608;
extern s32 lbl_8064D764;
extern float lbl_80651348, lbl_80651378, lbl_8065137C;
extern float lbl_806513E4, lbl_806513E8;
extern char lbl_802FC2C0[];

extern void C_MTXOrtho(float*, float, float, float, float, float, float);
extern void GXSetProjection(float*, int);
extern void PSMTXIdentity(float*);
extern void GXLoadPosMtxImm(float*, int);
extern void fn_801ED468(int);
extern void GXSetCullMode(int);
extern void GXSetNumChans(int);
extern void GXSetNumTexGens(int);
extern void GXSetNumTevStages(int);
extern void fn_801F3938(int, int, int, int);
extern void GXSetTevOrder(int, int, int, int);
extern void GXSetTevColor(int, Color);
extern void GXSetTevKColorSel(int, int);
extern void GXSetTevColorOp(int, int, int, int, int, int);
extern void GXSetTevColorIn(int, int, int, int, int);
extern void GXSetTevAlphaOp(int, int, int, int, int, int);
extern void GXSetTevAlphaIn(int, int, int, int, int);
extern void fn_8015DB84(char*, u8*, int);
extern void GXLoadTexObj(u8*, int);
extern void fn_801ECF50(int);
extern void GXBegin(int, int, int);
extern void fn_801F3924(int, int, int);
extern void fn_801F3914(float, float);
extern void fn_801F0AFC(void);
extern void fn_801ECC4C(void);
extern void fn_801A8D38(int);

void fn_801F35A8(void)
{
    float projection[16];
    float matrix[12];
    Color color;
    u8 texture[0x20];
    u8* target = (u8*)&lbl_8064C384;

    if (lbl_8064D764 != 0) {
        lbl_8063C608.red += ((float)target[0] - lbl_8063C608.red) / (float)lbl_8064D764;
        lbl_8063C608.green += ((float)target[1] - lbl_8063C608.green) / (float)lbl_8064D764;
        lbl_8063C608.blue += ((float)target[2] - lbl_8063C608.blue) / (float)lbl_8064D764;
        lbl_8063C608.alpha += ((float)target[3] - lbl_8063C608.alpha) / (float)lbl_8064D764;
        --lbl_8064D764;
    }

    if (lbl_8063C608.alpha > lbl_80651348) {
        color.red = (u8)lbl_8063C608.red;
        color.green = (u8)lbl_8063C608.green;
        color.blue = (u8)lbl_8063C608.blue;
        color.alpha = (u8)lbl_8063C608.alpha;
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
        GXSetTevColor(1, color);
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
