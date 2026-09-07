typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;

typedef struct Work Work;
struct Work {
    u8 pad0[4];
    void* object;
    s32 owner;
    s32 valueC;
    s32 handle;
    u8 pad14[0x14];
    void (*callback)(Work*, void*);
    void* callback_arg;
    void* resource;
    u8 pad34[4];
    u8 output[0xC];
    void* effect;
    u8 pad48[0xFA8];
    u8 flags;
    u8 padFF1[3];
    u16 timer;
};

extern s32 lbl_8064D18C;
extern float lbl_80651208;
extern void fn_801FE22C(void*);
extern void* fn_80201B54(void);
extern void fn_8020123C(s32, void*, void*, s32);
extern void fn_801D1318(s32);
extern void fn_801A9E40(s32);
extern void fn_801B05B0(s32, s32);
extern void fn_801D0E78(Work*);
extern void* fn_80201B9C(void);
extern void* fn_80204844(void*, s32);
extern void fn_800CDE80(s32, void*, float, s32);
extern void fn_801FE934(void*, s32);
extern u8 fn_801CEB2C(void*);
extern s32 fn_801D3A34(void*, s32);
extern void fn_8014EAA4(void*, s32, s32, s32, s32, s32, s32, s32);

void fn_801E1BEC(Work* work)
{
    if (work->owner != lbl_8064D18C || (work->flags & 1) != 0) {
        if (work->timer > 60 && work->callback != 0) {
            work->callback(work, work->callback_arg);
        }
        fn_801FE22C(work->effect);
        if (work->resource != 0) {
            void* value = fn_80201B54();
            fn_8020123C(57, value, value, 0);
        }
        if ((work->flags & 0x10) != 0) {
            fn_801D1318(0);
        }
        fn_801A9E40(-1);
        if (work->handle != -1) {
            fn_801B05B0(work->handle, 10);
        }
        fn_801D0E78(work);
        return;
    }

    switch (work->timer) {
    case 0:
        if (fn_80204844(fn_80201B9C(), 34) != 0) {
            void* value = fn_80201B54();
            fn_8020123C(95, value, value, 0);
        }
        fn_800CDE80(work->valueC, work->object, lbl_80651208, 1);
        break;
    case 20:
        fn_801FE934(work->effect, 15);
        break;
    case 40: {
        s32 c;
        s32 b;
        s32 kind;
        s32 a;
        s32 d;
        kind = fn_801CEB2C(work->object);
        a = fn_801D3A34(work->object, 53);
        b = fn_801D3A34(work->object, 78);
        c = fn_801D3A34(work->object, 74);
        d = fn_801D3A34(work->object, 70);
        fn_8014EAA4(work->output, 250, kind, a, d, c, b, 4);
        break;
    }
    case 124:
        if (work->resource != 0) {
            void* value = fn_80201B54();
            fn_8020123C(57, value, value, 0);
        }
        break;
    case 200:
        if (work->callback != 0) {
            work->callback(work, work->callback_arg);
        }
        if ((work->flags & 0x10) != 0) {
            fn_801D1318(0);
        }
        fn_801A9E40(-1);
        fn_801D0E78(work);
        break;
    }
}
