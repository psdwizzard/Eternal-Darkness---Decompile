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
extern float lbl_80651348;
extern float lbl_8065134C;

extern void* fn_801EB080(void);
extern u32 fn_801F4568(void);
extern void GXInitTexObj(void*, void*, int, int, int, int, int, int);
extern void GXInitTexObjLOD(void*, int, int, int, int, int, float, float, float);
extern void GXSetColorUpdate(int);
extern void GXSetAlphaUpdate(int);
extern void GXSetTevAlphaIn(int, int, int, int, int);
extern void fn_801ECEC8(int, int, int);
extern void GXSetTevColor(int, Color*);
extern void GXLoadTexObj(void*, int);
extern void GXSetTevOrder(int, int, int, int);
extern void fn_801F3938(int, int, int, int);
extern void GXSetTevColorOp(int, int, int, int, int, int);
extern void GXSetTevColorIn(int, int, int, int, int);
extern void GXSetTevAlphaOp(int, int, int, int, int, int);
extern void GXSetNumChans(int);
extern void GXSetNumTexGens(int);
extern void GXSetNumTevStages(int);
extern void fn_801ECF50(int);
extern void GXBegin(int, int, int);
extern void fn_801F3924(int, int, int);
extern void fn_801F3914(float, float);
extern void fn_801F0AFC(void);

void fn_801F4570(int value, int mode)
{
    void* context;
    union {
        u32 word;
        Color bytes;
    } color;
    Color color_copy;

    context = fn_801EB080();
    color.word = fn_801F4568();
    color.bytes.a = 0x20;

    GXInitTexObj(lbl_8063C638 + lbl_8064D738 * 32, context,
                0x280, 0x1E0, 1, 0, 0, 0);
    GXInitTexObjLOD(lbl_8063C638 + lbl_8064D738 * 32, 0, 0, 0, 0, 0,
                lbl_80651348, lbl_80651348, lbl_80651348);

    if (mode == 0) {
        GXSetColorUpdate(1);
        GXSetAlphaUpdate(0);
        GXSetTevAlphaIn(0, 7, 7, 7, 6);
    } else {
        GXSetColorUpdate(0);
        GXSetAlphaUpdate(1);
        GXSetTevAlphaIn(0, 7, 6, 4, 2);
    }

    fn_801ECEC8(0, 3, 0);
    *(u32*)&color_copy = color.word;
    GXSetTevColor(2, &color_copy);
    GXLoadTexObj(lbl_8063C638 + lbl_8064D738 * 32, 0);
    GXSetTevOrder(0, 0, 0, 0xFF);
    fn_801F3938(0, 1, 4, 0x3C);
    GXSetTevColorOp(0, 0, 0, value, 1, 0);
    GXSetTevColorIn(0, 0xF, 8, 4, 0xF);
    GXSetTevAlphaOp(0, 0, 0, value, 1, 0);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
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
    fn_801ECEC8(1, 3, 1);
}
