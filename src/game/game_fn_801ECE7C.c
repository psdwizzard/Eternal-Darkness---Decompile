typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

extern Color lbl_8064C370;
extern Color lbl_8064D66C;
extern void fn_80229E00(int channel, Color* color);

void fn_801ECE7C(u32 value)
{
    u8 component = (value >> 1) & 0x7F;

    if (lbl_8064D66C.r != component) {
        Color copy;
        lbl_8064D66C.r = component;
        lbl_8064C370.g = component;
        copy = lbl_8064C370;
        fn_80229E00(0, &copy);
    }
}
