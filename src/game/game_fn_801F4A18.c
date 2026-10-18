typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

extern int lbl_8064D738;
extern u8 lbl_8063C638[];
extern u8 lbl_8063B31C[];
extern u32 lbl_80651404;
extern float lbl_80651408;
extern float lbl_80651348;
extern float lbl_8065134C;
extern float lbl_806513B8;

extern void* fn_801EB080(void);
extern void GXInitTexObj(void*, void*, int, int, int, int, int, int);
extern void GXInitTexObjLOD(void*, int, int, int, int, int, float, float, float);
extern void GXSetColorUpdate(int);
extern void GXSetAlphaUpdate(int);
extern void fn_801ECEC8(int, int, int);
extern void GXSetTevColor(int, Color*);
extern void GXLoadTexObj(void*, int);
extern void fn_801F3938(int, int, int, int);
extern void GXSetTevColorOp(int, int, int, int, int, int);
extern void GXSetTevColorIn(int, int, int, int, int);
extern void GXSetTevAlphaOp(int, int, int, int, int, int);
extern void GXSetTevAlphaIn(int, int, int, int, int);
extern void GXSetTevOrder(int, int, int, int);
extern void GXSetIndTexOrder(int, int, int);
extern void GXSetIndTexCoordScale(int, int, int);
extern void GXSetIndTexMtx(int, void*, int);
extern void GXSetTevIndWarp(int, int, int, int, int);
extern void GXSetNumChans(int);
extern void GXSetNumTexGens(int);
extern void GXSetNumTevStages(int);
extern void GXSetNumIndStages(int);
extern void fn_801ECF50(int);
extern void GXBegin(int, int, int);
extern void fn_801F3924(int, int, int);
extern void fn_801F3914(float, float);
extern void fn_801F0AFC(void);
extern void GXSetTevDirect(int);
extern void* memset(void*, int, unsigned long);

void fn_801F4A18(float value)
{
    void* context;
    union {
        u32 word;
        Color bytes;
    } color;
    Color color_copy;
    u8 data[24];

    context = fn_801EB080();
    color.word = lbl_80651404;
    memset(data, 0, sizeof(data));
    *(float*)&data[0] = value;
    *(float*)&data[16] = value;
    if (value < lbl_80651408) {
        color.bytes.a = (u8)(lbl_806513B8 * (value / lbl_80651408));
    }

    GXInitTexObj(lbl_8063C638 + lbl_8064D738 * 32, context,
                0x280, 0x1E0, 4, 0, 0, 0);
    GXInitTexObjLOD(lbl_8063C638 + lbl_8064D738 * 32, 0, 0, 0, 0, 0,
                lbl_80651348, lbl_80651348, lbl_80651348);
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(0);
    fn_801ECEC8(0, 3, 0);
    color_copy = color.bytes;
    GXSetTevColor(2, &color_copy);
    GXLoadTexObj(lbl_8063C638 + lbl_8064D738 * 32, 0);
    GXLoadTexObj(lbl_8063B31C, 1);
    fn_801F3938(0, 1, 4, 0x3C);
    GXSetTevColorOp(0, 0, 0, 0, 1, 0);
    GXSetTevColorIn(0, 0xF, 8, 0xC, 0xF);
    GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);
    GXSetTevAlphaIn(0, 7, 7, 7, 2);
    GXSetTevOrder(0, 0, 0, 0xFF);
    GXSetIndTexOrder(0, 0, 1);
    GXSetIndTexCoordScale(0, 0, 0);
    GXSetIndTexMtx(1, data, 2);
    GXSetTevIndWarp(0, 0, 1, 0, 1);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetNumIndStages(1);
    fn_801ECF50(8);
    GXBegin(0x80, 2, 4);

    fn_801F3924(-0x2800, -0x1E00, 0);
    fn_801F3914(lbl_80651348, lbl_80651348);
    fn_801F3924(0x2800, -0x1E00, 0);
    fn_801F3914(lbl_8065134C, lbl_80651348);
    fn_801F3924(0x2800, 0x1E00, 0);
    fn_801F3914(lbl_8065134C, lbl_8065134C);
    fn_801F3924(-0x2800, 0x1E00, 0);
    fn_801F3914(lbl_80651348, lbl_8065134C);
    fn_801F0AFC();
    GXSetNumIndStages(0);
    GXSetTevDirect(0);
    fn_801ECEC8(1, 3, 1);
}
