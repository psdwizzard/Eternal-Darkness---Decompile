typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

typedef struct Actor {
    u8 pad0[0x86];
    u16 mode;
    u8 pad88[0x10F];
    signed char notify;
    int state;
} Actor;

extern Color lbl_8064F444;
extern Color lbl_8064F448;
extern Color lbl_8064F44C;
extern Color lbl_8064F450;
extern u16 fn_8012DBE8(void *, int, Color *);
extern void fn_800A1AF0(void *, int, int, int, Color, Color, Color, u16);
extern void fn_800A3C84(void *, int, int, int);
extern void fn_800D91AC(void *, Actor *);
extern void fn_800A4C98(Actor *, void *);
extern void fn_800A4670(Actor *, void *, int);
extern void fn_800A2D78(Actor *);
extern void fn_800A4D04(Actor *);
extern void fn_800A4634(Actor *, void *);
extern u16 fn_8012FCB0(void *, int, u16, u16);
extern void fn_800D8EC4(Actor *, void *, int);

void fn_800D9428(Actor *actor, void *runtime, int source, int context)
{
    u16 flags = 0x100;
    Color detail;
    Color color0;
    Color edge;
    Color color1;
    Color color2;
    Color base;
    Color color3;

    color0 = lbl_8064F444;
    color1 = lbl_8064F448;
    color2 = lbl_8064F44C;
    color3 = lbl_8064F450;

    if (source != 0) {
        flags |= 0x32;
        base = color3;
        detail = color0;
        edge = color2;
    } else {
        flags |= 0x12;
        base = color0;
        detail = color3;
        edge = color1;
    }
    if (actor->state != -1) {
        fn_8012DBE8(runtime, 15, &base);
        detail = base;
        fn_800A1AF0(runtime, actor->state, source, context, base, edge, base, flags);
    }
    if (actor->state != 1) {
        fn_800A1AF0(runtime, 1, source, context, base, edge, detail, flags);
    }
    if (actor->notify != 0) {
        fn_800A3C84(runtime, actor->state, source, context);
    }
    if (source != 0) {
        fn_800D91AC(runtime, actor);
        fn_800A4C98(actor, runtime);
        fn_800A4670(actor, runtime, 16);
    } else {
        fn_800A2D78(actor);
        fn_800A4D04(actor);
        fn_800A4634(actor, runtime);
    }
    if (actor->mode == 2) {
        if (source != 0) {
            fn_8012FCB0(runtime, 14, 0, 0x400);
        } else {
            fn_8012FCB0(runtime, 14, 0x400, 0);
        }
        fn_800D8EC4(actor, runtime, 1);
    }
}
