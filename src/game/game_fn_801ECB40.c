typedef unsigned char u8;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

extern Color lbl_8064C370;
extern void fn_80229E00(int channel, Color* color);

void fn_801ECB40(u8 value)
{
    Color color;
    Color first;
    Color second;
    Color third;

    if (lbl_8064C370.r != value) {
        lbl_8064C370.r = value;
        lbl_8064C370.g = value;
        lbl_8064C370.b = value;
        lbl_8064C370.a = 255;
        color = lbl_8064C370;
        first = color;
        second = first;
        fn_80229E00(0, &second);
        third = first;
        fn_80229E00(1, &third);
    }
}
