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
extern void fn_80228474(void*, void*, int, int, int, int, int, int);
extern void fn_80228730(void*, int, int, int, int, int, float, float, float);
extern void fn_8022A6DC(int);
extern void fn_8022A71C(int);
extern void fn_80229B88(int, int, int, int, int);
extern void fn_801ECEC8(int, int, int);
extern void fn_80229D8C(int, Color*);
extern void fn_80228AFC(void*, int);
extern void fn_8022A118(int, int, int, int);
extern void fn_801F3938(int, int, int, int);
extern void fn_80229C0C(int, int, int, int, int, int);
extern void fn_80229B08(int, int, int, int, int);
extern void fn_80229CCC(int, int, int, int, int, int);
extern void fn_80228020(int);
extern void fn_802262B8(int);
extern void fn_8022A2F4(int);
extern void fn_801ECF50(int);
extern void fn_80226AB4(int, int, int);
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

    fn_80228474(lbl_8063C638 + lbl_8064D738 * 32, context,
                0x280, 0x1E0, 1, 0, 0, 0);
    fn_80228730(lbl_8063C638 + lbl_8064D738 * 32, 0, 0, 0, 0, 0,
                lbl_80651348, lbl_80651348, lbl_80651348);

    if (mode == 0) {
        fn_8022A6DC(1);
        fn_8022A71C(0);
        fn_80229B88(0, 7, 7, 7, 6);
    } else {
        fn_8022A6DC(0);
        fn_8022A71C(1);
        fn_80229B88(0, 7, 6, 4, 2);
    }

    fn_801ECEC8(0, 3, 0);
    *(u32*)&color_copy = color.word;
    fn_80229D8C(2, &color_copy);
    fn_80228AFC(lbl_8063C638 + lbl_8064D738 * 32, 0);
    fn_8022A118(0, 0, 0, 0xFF);
    fn_801F3938(0, 1, 4, 0x3C);
    fn_80229C0C(0, 0, 0, value, 1, 0);
    fn_80229B08(0, 0xF, 8, 4, 0xF);
    fn_80229CCC(0, 0, 0, value, 1, 0);
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
}
