typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Resource {
    u8 pad0[8];
    u16 value8;
    u8 padA[14];
    void *value18;
} Resource;

typedef struct State {
    u8 pad0[6];
    u8 value6;
    u8 pad7;
    u8 value8;
    u8 value9;
    u16 valueA;
    u8 padC[0x150];
    void *value15C;
} State;

typedef struct GlobalState {
    u8 pad0[0x654];
    State state;
} GlobalState;

extern u8 lbl_803108B8[];
extern void *lbl_8064C8C0;
extern s32 lbl_8064C8C4;
extern s32 lbl_8064C8C8;
extern s32 lbl_8064C8CC;
extern void *lbl_8064C8D0;
extern u8 (*lbl_8064C8D4)[0x654];
extern s32 lbl_8064C914;

extern void *memset(void *dest, s32 value, unsigned long size);
extern Resource *fn_8006D1DC(s32 kind);
extern void fn_8006B364(void *state);
extern void fn_8006B40C(void);
extern void fn_800AE2D4(s32 mode);
extern void fn_80088F08(s32 first, s32 second);
extern void fn_800891F4(s32 value);
extern unsigned int fn_800FBFB0(void);
#define fn_800FBFB0() ((int)fn_800FBFB0())

void fn_8006B21C(s32 mode)
{
    GlobalState *root = (GlobalState *)lbl_803108B8;
    u8 *base = (u8 *)root;
    State *state;
    Resource *resource;

    lbl_8064C8D4 = &root->pad0;
    lbl_8064C8D0 = base + 0x630;
    switch (mode) {
    case 1:
        state = (State *)(base + 0x654);
        state->value6 = 0;
        state->value8 = 5;
        state->valueA = 0;
        state->value9 = 1;
        resource = fn_8006D1DC(0x25);
        if (resource != 0) {
            resource->value8 = 0;
            resource->value18 = 0;
        }
        fn_8006D1DC(0xC);
        break;
    default:
        memset(base + 0x654, 0, 0x164);
        state = (State *)(base + 0x654);
        state->value15C = (u8 *)state + 0x164;
        fn_8006B364(state);
        break;
    }
    fn_8006B40C();
    memset(base + 0x7B8, 0, 0x1788);
    memset(base + 0x1F40, 0, 0x80);
    memset(base + 0x1FC0, 0, 0x10);
    fn_800AE2D4(mode);
    lbl_8064C8C8 = 0;
    lbl_8064C8C4 = 0;
    lbl_8064C8CC = 0x10000;
    fn_80088F08(0, -1);
    fn_800891F4(-15);
    lbl_8064C914 = 0;
    if ((fn_800FBFB0() & 0x7F) > 0x40) {
        fn_800891F4(15);
    }
    lbl_8064C8C0 = 0;
}
