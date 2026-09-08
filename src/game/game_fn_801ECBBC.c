typedef unsigned char u8;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

extern Color lbl_8064D6AC;
extern void fn_80229E00(int channel, Color* color);

void fn_801ECBBC(Color* color)
{
    Color value;

    if (lbl_8064D6AC.r != color->r ||
        lbl_8064D6AC.g != color->g ||
        lbl_8064D6AC.b != color->b ||
        lbl_8064D6AC.a != color->a) {
        value = *color;
        fn_80229E00(2, &value);
        lbl_8064D6AC = *color;
    }
}
