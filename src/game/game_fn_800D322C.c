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
    u8 pad0[0x197];
    signed char notify;
    int state;
} Actor;

extern Color lbl_8064F380;
extern Color lbl_8064F384;
extern Color lbl_8064F388;
extern Color lbl_8064F38C;
extern u16 fn_8012DBE8(void *, int, Color *);
extern void fn_800A1AF0(void *, int, int, int, Color, Color, Color, u16);
extern void fn_800A3C84(void *, int, int, int);
extern void fn_800CFFFC(void *, Actor *);
extern void fn_800A4C98(Actor *, void *);
extern void fn_800A4670(Actor *, void *, int);
extern void fn_800A2D78(Actor *);
extern void fn_800A4D04(Actor *);
extern void fn_800A4634(Actor *, void *);

void fn_800D322C(Actor *actor, void *runtime, int source, int context)
{
    u16 flags = 0x80;
    Color detail;
    Color color3;
    Color edge;
    Color color1;
    Color color2;
    Color base;
    Color color0;

    color3 = lbl_8064F380;
    color1 = lbl_8064F384;
    color2 = lbl_8064F388;
    color0 = lbl_8064F38C;

    if (source != 0) {
        flags |= 0x32;
        base = color0;
        edge = color2;
    } else {
        flags |= 0x12;
        base = color3;
        edge = color1;
    }
    if (actor->state != -1) {
        fn_8012DBE8(runtime, 15, &base);
        detail = base;
        fn_800A1AF0(runtime, actor->state, source, context, base, edge, base, flags);
    }
    if (actor->notify != 0) {
        fn_800A3C84(runtime, actor->state, source, context);
    }
    if (source != 0) {
        fn_800CFFFC(runtime, actor);
        fn_800A4C98(actor, runtime);
        fn_800A4670(actor, runtime, 32);
    } else {
        fn_800A2D78(actor);
        fn_800A4D04(actor);
        fn_800A4634(actor, runtime);
    }
}
