typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Context { u8 pad[8]; u16 counter; } Context;
typedef struct Owner { u8 pad[0x15C]; int* data; } Owner;
typedef struct Work { u8 bytes[0xC4]; Owner* owner; } Work;

extern Context* fn_8006D1DC(int);
extern void fn_8006D198(Work*, Context*, int);
extern unsigned int rand(void);
#define rand() ((int)rand())
extern void fn_8006BEE4(Context*, void (*)(void));
extern void fn_8006DEF8(Work*, int, void*, void*, int);
extern void fn_8006C9E4(Context*, int);
extern void fn_80088E44(void);
extern void fn_800886D8(void);
extern int fn_80088844(int);
extern int lbl_8064C914;

void fn_80088588(Work* work)
{
    Context* context = fn_8006D1DC(2);
    int* data;

    fn_8006D198(work, context, 2);
    data = work->owner->data;
    data[0x1780 / 4] = 15;
    if ((rand() & 0x1F) > 0x10)
        data[0x1780 / 4] = -15;
    fn_8006BEE4(context, fn_80088E44);
    context->counter = 0;
    work->bytes[0xC2] = 0;
    work->bytes[0xC3] = 3;
    work->bytes[0xC0] = 4;
    fn_8006DEF8(work, 2, fn_800886D8, work, 10);
    work->bytes[0xC0] = 0;
    fn_8006DEF8(work, 2, fn_800886D8, work, 10);
    work->bytes[0xC0] = 1;
    fn_8006DEF8(work, 2, fn_800886D8, work, 10);
    work->bytes[0xC0] = 2;
    fn_8006DEF8(work, 2, fn_80088844, work, 60);
    work->bytes[0xC0] = 0;
    fn_8006C9E4(context, 0);
    lbl_8064C914 = 0;
}
