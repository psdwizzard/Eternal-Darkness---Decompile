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
extern void fn_80228474(void*, void*, int, int, int, int, int, int);
extern void fn_80228730(void*, int, int, int, int, int, float, float, float);
extern void fn_8022A6DC(int);
extern void fn_8022A71C(int);
extern void fn_801ECEC8(int, int, int);
extern void fn_80229D8C(int, Color*);
extern void fn_80228AFC(void*, int);
extern void fn_801F3938(int, int, int, int);
extern void fn_80229C0C(int, int, int, int, int, int);
extern void fn_80229B08(int, int, int, int, int);
extern void fn_80229CCC(int, int, int, int, int, int);
extern void fn_80229B88(int, int, int, int, int);
extern void fn_8022A118(int, int, int, int);
extern void fn_80229664(int, int, int);
extern void fn_80229490(int, int, int);
extern void fn_80229330(int, void*, int);
extern void fn_80229810(int, int, int, int, int);
extern void fn_80228020(int);
extern void fn_802262B8(int);
extern void fn_8022A2F4(int);
extern void fn_8022979C(int);
extern void fn_801ECF50(int);
extern void fn_80226AB4(int, int, int);
extern void fn_801F3924(int, int, int);
extern void fn_801F3914(float, float);
extern void fn_801F0AFC(void);
extern void fn_802297C8(int);
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

    fn_80228474(lbl_8063C638 + lbl_8064D738 * 32, context,
                0x280, 0x1E0, 4, 0, 0, 0);
    fn_80228730(lbl_8063C638 + lbl_8064D738 * 32, 0, 0, 0, 0, 0,
                lbl_80651348, lbl_80651348, lbl_80651348);
    fn_8022A6DC(1);
    fn_8022A71C(0);
    fn_801ECEC8(0, 3, 0);
    color_copy = color.bytes;
    fn_80229D8C(2, &color_copy);
    fn_80228AFC(lbl_8063C638 + lbl_8064D738 * 32, 0);
    fn_80228AFC(lbl_8063B31C, 1);
    fn_801F3938(0, 1, 4, 0x3C);
    fn_80229C0C(0, 0, 0, 0, 1, 0);
    fn_80229B08(0, 0xF, 8, 0xC, 0xF);
    fn_80229CCC(0, 0, 0, 0, 1, 0);
    fn_80229B88(0, 7, 7, 7, 2);
    fn_8022A118(0, 0, 0, 0xFF);
    fn_80229664(0, 0, 1);
    fn_80229490(0, 0, 0);
    fn_80229330(1, data, 2);
    fn_80229810(0, 0, 1, 0, 1);
    fn_80228020(0);
    fn_802262B8(1);
    fn_8022A2F4(1);
    fn_8022979C(1);
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
    fn_8022979C(0);
    fn_802297C8(0);
    fn_801ECEC8(1, 3, 1);
}
