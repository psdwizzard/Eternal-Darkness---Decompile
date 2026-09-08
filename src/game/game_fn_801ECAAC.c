typedef unsigned char u8;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

extern Color lbl_8064D648;
extern void fn_80229D8C(int channel, Color* color);

void fn_801ECAAC(Color* color)
{
    Color value;

    if (lbl_8064D648.r != color->r ||
        lbl_8064D648.g != color->g ||
        lbl_8064D648.b != color->b ||
        lbl_8064D648.a != color->a) {
        lbl_8064D648.r = color->r;
        lbl_8064D648.g = color->g;
        lbl_8064D648.b = color->b;
        lbl_8064D648.a = color->a;
        value = lbl_8064D648;
        fn_80229D8C(3, &value);
    }
}
