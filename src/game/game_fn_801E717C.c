typedef signed short s16;
typedef unsigned char u8;
typedef unsigned int u32;

typedef union Color {
    u32 value;
    struct {
        u8 r;
        u8 g;
        u8 b;
        u8 a;
    } channel;
} Color;

extern char lbl_80255898[];
extern Color lbl_8064C2A8;
extern Color lbl_8064C2B0;
extern Color lbl_8064C33C;
extern char lbl_8064C344;
extern float lbl_8064C340;
extern int lbl_8064D590;
extern const float lbl_80651284;
extern const float lbl_8065129C;
extern const float lbl_806512A0;

extern void fn_801E3AA4(int);
extern u32 fn_801E3A34(Color*);
extern void fn_801E4314(s16, s16, s16, s16, float, int);
extern void fn_801E5430(s16, s16);
extern void fn_801E56AC(float, const char*, ...);
extern void fn_801E5AD0(u8);

void fn_801E717C(void)
{
    float alpha;
    char* strings = lbl_80255898 + 0x10000;

    fn_801E3AA4(0);
    fn_801E4314(10, 10, 320, 390, lbl_80651284, 0);
    fn_801E5430(20, 20);
    fn_801E5AD0(108);
    {
        Color color = lbl_8064C33C;
        fn_801E3A34(&color);
    }

    alpha = lbl_8064C340;
    while (alpha >= lbl_806512A0) {
        fn_801E56AC(alpha, strings - 0xE40, alpha);
        alpha -= lbl_8065129C;
    }

    if (lbl_8064D590 == 0) {
        Color color = lbl_8064C2A8;
        fn_801E3A34(&color);
    } else {
        Color color = lbl_8064C2B0;
        fn_801E3A34(&color);
    }
    fn_801E5430(50, 400);
    fn_801E56AC(lbl_80651284, &lbl_8064C344, lbl_8064C33C.channel.r);

    if (lbl_8064D590 == 1) {
        Color color = lbl_8064C2A8;
        fn_801E3A34(&color);
    } else {
        Color color = lbl_8064C2B0;
        fn_801E3A34(&color);
    }
    fn_801E5430(200, 400);
    fn_801E56AC(lbl_80651284, strings - 0xE28,
                lbl_8064C33C.channel.g);

    if (lbl_8064D590 == 2) {
        Color color = lbl_8064C2A8;
        fn_801E3A34(&color);
    } else {
        Color color = lbl_8064C2B0;
        fn_801E3A34(&color);
    }
    fn_801E5430(350, 400);
    fn_801E56AC(lbl_80651284, strings - 0xE1C,
                lbl_8064C33C.channel.b);

    if (lbl_8064D590 == 3) {
        Color color = lbl_8064C2A8;
        fn_801E3A34(&color);
    } else {
        Color color = lbl_8064C2B0;
        fn_801E3A34(&color);
    }
    fn_801E5430(500, 400);
    fn_801E56AC(lbl_80651284, strings - 0xE10,
                lbl_8064C340);
}
