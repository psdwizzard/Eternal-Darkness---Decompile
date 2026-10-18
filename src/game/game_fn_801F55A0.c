typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Color {
    u8 r, g, b, a;
} Color;

typedef struct StateBlock {
    u32 words[13];
} StateBlock;

extern void* lbl_8064D6B8;
extern int lbl_8064D738;
extern int lbl_8064D76C;
extern int lbl_8064D780;
extern u8 lbl_8063C678[];
extern u32 lbl_80651410;
extern float lbl_80651348;
extern float lbl_8065134C;
extern float lbl_806513B8;

extern void fn_801F44DC(void);
extern void fn_801F550C(void);
extern void GXInitTexObj(void*, void*, int, int, int, int, int, int);
extern void GXInitTexObjLOD(void*, int, int, int, int, int, float, float, float);
extern void GXSetColorUpdate(int);
extern void GXSetAlphaUpdate(int);
extern void GXSetTevColor(int, Color*);
extern void fn_801ECEC8(int, int, int);
extern void GXLoadTexObj(void*, int);
extern void GXSetTevOrder(int, int, int, int);
extern void fn_801F3938(int, int, int, int);
extern void GXSetTevColorOp(int, int, int, int, int, int);
extern void GXSetTevColorIn(int, int, int, int, int);
extern void GXSetTevAlphaOp(int, int, int, int, int, int);
extern void GXSetTevAlphaIn(int, int, int, int, int);
extern void GXSetNumChans(int);
extern void GXSetNumTexGens(int);
extern void GXSetNumTevStages(int);
extern void fn_801ECF50(int);
extern void GXBegin(int, int, int);
extern void fn_801F3924(int, int, int);
extern void fn_801F3914(float, float);
extern void fn_801F0AFC(void);
extern void fn_801F683C(StateBlock*);
extern void fn_801F03F0(StateBlock*, int);

int fn_801F55A0(void)
{
    union { u32 word; Color bytes; } color;
    Color copy_color;
    StateBlock copy;
    StateBlock source;
    if (lbl_8064D6B8 != 0) {
    u8 alpha;
    color.word = lbl_80651410;
    alpha = (u8)(lbl_806513B8 * ((float)lbl_8064D780 / (float)lbl_8064D76C));
    fn_801F44DC();
    GXInitTexObj(lbl_8063C678 + lbl_8064D738 * 32, lbl_8064D6B8,
                0x280, 0x1E0, 4, 0, 0, 0);
    GXInitTexObjLOD(lbl_8063C678 + lbl_8064D738 * 32, 0, 0, 0, 0, 0,
                lbl_80651348, lbl_80651348, lbl_80651348);
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(0);
    color.bytes.a = alpha;
    copy_color = color.bytes;
    GXSetTevColor(1, &copy_color);
    fn_801ECEC8(0, 3, 0);
    GXLoadTexObj(lbl_8063C678 + lbl_8064D738 * 32, 0);
    GXSetTevOrder(0, 0, 0, 0xFF);
    fn_801F3938(0, 1, 4, 0x3C);
    GXSetTevColorOp(0, 0, 0, 0, 1, 0);
    GXSetTevColorIn(0, 0xF, 8, 0xC, 0xF);
    GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);
    GXSetTevAlphaIn(0, 7, 7, 7, 1);
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
    fn_801F683C(&source);
    copy = source;
    fn_801F03F0(&copy, 0);

    if (lbl_8064D780 > 0) {
        lbl_8064D780--;
        return 1;
    } else {
        fn_801F550C();
        lbl_8064D780 = 0;
        return 0;
    }
    }
    return 0;
}
