typedef unsigned char u8;
typedef struct Color { u8 r, g, b, a; } Color;

extern Color lbl_8064F908;
extern float lbl_8064F90C;
extern void fn_801F3960(Color*);

void fn_800ED98C(float alpha) {
    Color color;
    Color out;
    float scale = lbl_8064F90C;
    u8 a = (u8)(scale * alpha);
    color = lbl_8064F908;
    color.a = a;
    out = color;
    fn_801F3960(&out);
}
