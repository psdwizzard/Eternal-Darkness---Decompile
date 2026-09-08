typedef unsigned char u8;
typedef int s32;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

typedef struct ResetState {
    s32 first;
    s32 second;
    s32 third;
} ResetState;

extern ResetState lbl_8063B42C;
extern Color lbl_8064C370;
extern Color lbl_8064D648;
extern Color lbl_8064D66C;
extern Color lbl_8064D670;
extern Color lbl_8064D674;
extern s32 lbl_8064D678;
extern u8 lbl_8064D694;
extern u8 lbl_8064D695;
extern s32 lbl_8064D698;
extern s32 lbl_8064D69C;
extern Color lbl_8064D6AC;
extern void fn_80229D8C(int channel, Color* color);
extern void fn_80229E00(int channel, Color* color);
extern void fn_801ED118(void);

void fn_801ECC4C(void)
{
    Color source;
    Color color1;
    Color color2;
    Color color3;
    Color color4;
    Color color5;

    lbl_8064D674.r = 255;
    lbl_8064D674.g = 255;
    lbl_8064D674.b = 255;
    lbl_8064D674.a = 255;
    lbl_8064D670.r = 255;
    lbl_8064D670.g = 255;
    lbl_8064D670.b = 255;
    lbl_8064D670.a = 255;
    lbl_8064D66C.r = 255;
    lbl_8064C370.g = 255;

    source.r = lbl_8064C370.r;
    source.g = lbl_8064C370.r;
    source.b = lbl_8064C370.r;
    source.a = lbl_8064C370.r;
    color1 = source;
    fn_80229E00(1, &color1);

    color2 = lbl_8064C370;
    fn_80229E00(0, &color2);
    color3 = lbl_8064D674;
    fn_80229D8C(1, &color3);
    color4 = lbl_8064D648;
    fn_80229D8C(3, &color4);
    color5 = lbl_8064D6AC;
    fn_80229E00(2, &color5);
    fn_801ED118();

    lbl_8063B42C.first = -1;
    lbl_8064D678 = -1;
    lbl_8064D69C = -1;
    lbl_8064D698 = -1;
    lbl_8064D695 = 255;
    lbl_8064D694 = 255;
    lbl_8063B42C.second = -1;
    lbl_8063B42C.third = -1;
}
