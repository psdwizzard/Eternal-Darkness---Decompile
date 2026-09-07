typedef signed short s16;
typedef unsigned char u8;

typedef union Color {
    struct {
        u8 r;
        u8 g;
        u8 b;
        u8 a;
    } channel;
    unsigned int value;
} Color;

extern int lbl_8064D590;
extern Color lbl_8064C33C;
extern float lbl_8064C340;
extern const float lbl_80651284;
extern const double lbl_80651288;
extern const float lbl_80651294;
extern const float lbl_80651298;
extern void fn_80144C40(void);

#define MIN(a, b) ((b) < (a) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(value, low, high) MIN(MAX((value), (low)), (high))

void fn_801E7014(s16 amount)
{
    switch (lbl_8064D590) {
    case 0:
        lbl_8064C33C.channel.r += amount;
        break;
    case 1:
        lbl_8064C33C.channel.g += amount;
        break;
    case 2:
        lbl_8064C33C.channel.b += amount;
        break;
    case 3:
        lbl_8064C340 += lbl_80651294 * amount;
        lbl_8064C340 = CLAMP(lbl_8064C340, lbl_80651284, lbl_80651298);
        break;
    }
    fn_80144C40();
}
