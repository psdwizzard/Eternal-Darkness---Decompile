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
    {
        float value;
        float maximum;
        float result;

        value = lbl_80651294 * amount + lbl_8064C340;
        lbl_8064C340 = value;
        maximum = lbl_80651284;
        if (value > maximum) {
            maximum = value;
        }
        if (lbl_80651298 < maximum) {
            result = lbl_80651298;
        } else {
            /* Re-read the lower bound for the second selection. */
            result = *(const volatile float *)&lbl_80651284;
            if (value > result) {
                result = value;
            }
        }
        lbl_8064C340 = result;
        break;
    }
    }
    fn_80144C40();
}
