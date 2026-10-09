typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} GXColor;

typedef struct {
    char pad[0x10];
    int unk10;
} RuntimeState;

extern int lbl_8064CDC8;
extern int lbl_8064CD80;
extern RuntimeState lbl_8030241C;
extern int lbl_8064CE44;
extern const GXColor lbl_8064F098;
extern const GXColor lbl_8064F09C;
extern GXColor lbl_8064C2C4;
extern GXColor lbl_8064C2A8;
extern GXColor lbl_802FC5BC[];
extern char lbl_802515D0[];
extern char lbl_8064B6E8[3];
extern float lbl_8064F01C;
extern float lbl_8064F070;
extern float lbl_8064F0A0;
extern float lbl_8064F0A4;
extern float lbl_8064F0A8;

extern void fn_801ED3F4(int);
extern void fn_80225F4C(int, void *, int);
extern void fn_801A852C(GXColor, int, u16, unsigned int);
extern void fn_801A85D4(GXColor, u16, u16, unsigned int);
extern void fn_801A8F08(int, s16, int, s16, int, int, int);
extern void fn_801A8660(int, int, int, int, int, GXColor);
extern void fn_801ED5F4(int, int, int, int, int, float);
extern void fn_801E3AA4(int);
extern void fn_801E5AD0(int);
extern void fn_8022B970(int, int, int, int);
extern void fn_801E3A34(GXColor);
extern void fn_801E5448(int, int, float, const char *, ...);

void fn_800B81AC(const char *text, u8 alpha, float value)
{
    GXColor bar;
    GXColor fill;
    int textY;
    int innerY;
    int frameY;
    int frameW;
    int innerW;
    int innerH;
    float t;
    int width;

    innerY = 0x106;
    frameY = 0xF9;
    textY = 0x143;
    if (lbl_8064CDC8 == 3) {
        fn_801ED3F4(lbl_8064CD80);
        frameW = 0x1E;
        innerW = 0x12;
        fill = lbl_8064F098;
        innerH = 0x5B;
        width = 0x482;
        bar = lbl_8064F09C;
    } else {
        fn_801ED3F4(lbl_8030241C.unk10);
        frameW = 0x13;
        innerW = 0x14;
        innerH = 0x44;
        bar = fill = lbl_8064C2C4;
        width = 0x482;
    }
    fill.a = alpha;
    if (lbl_8064CE44 & 2) {
        textY = 0xAD;
        innerY = 0x70;
        frameY = 0x63;
    }
    t = MIN(1.0f, MAX(value, 0.0f));

    fn_80225F4C(0xD, lbl_802515D0, 4);
    fn_801A852C(fill, 5, frameW, 0x80000000);
    fn_801A8F08(0x87, frameY, 0x1EF, frameY + 0xAC, -1, 0, 5);
    fn_801A85D4(lbl_8064C2A8, innerW, innerH, 0x80000000);
    fn_801A8F08(0x9C, innerY, 0x1E4, innerY + 0x92, -1, 0, 5);
    fn_801ED5F4(1, width, 1, 0, 0, lbl_8064F070);
    t = lbl_8064F0A0 * t;
    fn_801A8660(0xC2, textY, (int)t, 0x1A, -1, bar);
    fn_801ED5F4(0, 2, 1, 0, 0, lbl_8064F01C);
    fn_801E3AA4(0);
    fn_801E5AD0(0x63);
    fn_8022B970((u16)(int)(lbl_8064F0A4 + t), (s16)textY, (u16)(int)(lbl_8064F0A0 - t), 0x1A);
    fn_801E3A34(lbl_802FC5BC[3]);
    fn_801E5448(0x139, textY, lbl_8064F0A8, lbl_8064B6E8, text);
    fn_8022B970(0xC2, (s16)textY, (s16)t, 0x1A);
    fn_801E3A34(lbl_802FC5BC[2]);
    fn_801E5448(0x139, textY, lbl_8064F0A8, lbl_8064B6E8, text);
    fn_8022B970(0, 0, 0x280, 0x1E0);
}
