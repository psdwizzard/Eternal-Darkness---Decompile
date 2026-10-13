typedef unsigned int u32;
typedef signed int s32;

extern u32 OSGetTick(void);
extern u32 lbl_8064C448;

static inline s32 NextRandom(void)
{
    lbl_8064C448 = lbl_8064C448 * 0x41C64E6D + 0x3039;
    return (lbl_8064C448 >> 16) & 0x7FFF;
}

s32 fn_8021D8F0(void)
{
    u32 shift = 1;
    u32 retries = 0;
    s32 length;
    s32 seed;

    lbl_8064C448 = OSGetTick();
    length = (NextRandom() & 31) + 1;
    while (length < 4 && retries < 10) {
        seed = OSGetTick() << shift;
        ++shift;
        if (shift > 16)
            shift = 1;
        lbl_8064C448 = seed;
        ++retries;
        length = (NextRandom() & 31) + 1;
    }
    if (length < 4)
        length = 4;
    return length;
}
