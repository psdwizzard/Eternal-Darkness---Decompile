typedef unsigned char u8;
typedef int s32;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

extern s32 lbl_8064D640;
extern float lbl_8064D644;
extern Color lbl_8064D674;
extern const float lbl_8065131C;
extern void fn_80229D8C(int channel, Color* color);

void fn_801ECD74(Color* color)
{
    Color copy;

    if (lbl_8065131C != lbl_8064D644 && lbl_8064D640 != 0) {
        s32 value = color->a * lbl_8064D644;
        value = (value > 0 ? value : 0) > 255 ? 255 : (value > 0 ? value : 0);
        color->a = value;
    }

    if (color->r != lbl_8064D674.r || color->g != lbl_8064D674.g ||
        color->b != lbl_8064D674.b || color->a != lbl_8064D674.a) {
        lbl_8064D674.r = color->r;
        lbl_8064D674.g = color->g;
        lbl_8064D674.b = color->b;
        lbl_8064D674.a = color->a;
        copy = lbl_8064D674;
        fn_80229D8C(1, &copy);
    }
}
