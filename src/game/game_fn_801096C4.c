typedef unsigned char u8;
typedef unsigned int u32;

extern int fn_80108510(void);
extern void fn_801084E0(void);
extern void fn_801084B0(void);
extern int fn_80108470(void);
extern void VIWaitForRetrace(void);

#define U8(p, o) (*(u8*)((u8*)(p) + (o)))
#define U32(p, o) (*(u32*)((u8*)(p) + (o)))

int fn_801096C4(void* state)
{
    u32 buffer;

    if (state == 0) {
        return 1;
    }

    U8(state, 0x1AC) = 4;
    if (fn_80108510() == -1) {
        fn_801084E0();
    } else {
        fn_801084B0();
        while (fn_80108470() != 0 && fn_80108470() != 3) {}
    }

    while (U8(state, 0x1AE) != 0) {
        U32(state, 0x174) = U32(state, 0x1C);
        VIWaitForRetrace();
    }

    U8(state, 0xF8) = 0;
    U8(state, 0x104) = 0;
    U8(state, 0x110) = 0;
    U8(state, 0x11C) = 0;
    U8(state, 0x128) = 0;
    U8(state, 0x134) = 0;
    U32(state, 0x16C) = 0;
    U32(state, 0x170) = 0;
    U32(state, 0x188) = 0;
    U32(state, 0x18C) = 0;
    U32(state, 0x194) = 0;
    U32(state, 0x190) = 0;
    buffer = U32(state, 0x154);
    U32(state, 0x160) = buffer;
    U32(state, 0x158) = buffer;
    return 0;
}
