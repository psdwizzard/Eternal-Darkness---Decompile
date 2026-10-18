typedef unsigned char u8;
typedef signed short s16;

typedef struct Context { u8 pad[8]; s16 counter; } Context;
typedef struct Work { u8 pad[0x3C]; float value; } Work;

extern void *fn_8006ED3C();
extern int fn_800891FC(void);
extern void fn_800891F4(int);
extern unsigned int rand(void);
#define rand() ((int)rand())
extern int fn_80088818(void);
extern void fn_801FA66C(int, int, float);
extern float lbl_8064EB7C;
extern float lbl_8064EB80;
extern float lbl_8064C910;
extern int lbl_8064C914;
extern unsigned int lbl_8064C920;

int fn_800886D8(Work* work)
{
    int index;
    Context* context = fn_8006ED3C(work, 2, &index);
    float amount;
    float factor;

    context->counter++;
    if (context->counter > 10000)
        context->counter = 1;
    if (work->value <= lbl_8064EB7C) {
        factor = (float)fn_800891FC();
        amount = factor * (lbl_8064EB7C - work->value);
        lbl_8064C914 = 1;
    } else {
        lbl_8064C910 = lbl_8064EB80;
        if (lbl_8064C914 != 0) {
            if ((rand() & 0x7F) > 0x40)
                fn_800891F4(15);
            else
                fn_800891F4(-15);
            lbl_8064C914 = 0;
        }
        context->counter = 0;
        return 1;
    }
    if (lbl_8064C920 == 0 && fn_80088818() != 0)
        fn_801FA66C(2, 0, amount);
    lbl_8064C910 = amount;
    return 1;
}
