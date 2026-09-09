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
extern void fn_80228474(void*, void*, int, int, int, int, int, int);
extern void fn_80228730(void*, int, int, int, int, int, float, float, float);
extern void fn_8022A6DC(int);
extern void fn_8022A71C(int);
extern void fn_80229D8C(int, Color*);
extern void fn_801ECEC8(int, int, int);
extern void fn_80228AFC(void*, int);
extern void fn_8022A118(int, int, int, int);
extern void fn_801F3938(int, int, int, int);
extern void fn_80229C0C(int, int, int, int, int, int);
extern void fn_80229B08(int, int, int, int, int);
extern void fn_80229CCC(int, int, int, int, int, int);
extern void fn_80229B88(int, int, int, int, int);
extern void fn_80228020(int);
extern void fn_802262B8(int);
extern void fn_8022A2F4(int);
extern void fn_801ECF50(int);
extern void fn_80226AB4(int, int, int);
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
    fn_80228474(lbl_8063C678 + lbl_8064D738 * 32, lbl_8064D6B8,
                0x280, 0x1E0, 4, 0, 0, 0);
    fn_80228730(lbl_8063C678 + lbl_8064D738 * 32, 0, 0, 0, 0, 0,
                lbl_80651348, lbl_80651348, lbl_80651348);
    fn_8022A6DC(1);
    fn_8022A71C(0);
    color.bytes.a = alpha;
    copy_color = color.bytes;
    fn_80229D8C(1, &copy_color);
    fn_801ECEC8(0, 3, 0);
    fn_80228AFC(lbl_8063C678 + lbl_8064D738 * 32, 0);
    fn_8022A118(0, 0, 0, 0xFF);
    fn_801F3938(0, 1, 4, 0x3C);
    fn_80229C0C(0, 0, 0, 0, 1, 0);
    fn_80229B08(0, 0xF, 8, 0xC, 0xF);
    fn_80229CCC(0, 0, 0, 0, 1, 0);
    fn_80229B88(0, 7, 7, 7, 1);
    fn_80228020(0);
    fn_802262B8(1);
    fn_8022A2F4(1);
    fn_801ECF50(8);
    fn_80226AB4(0x80, 2, 4);

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
