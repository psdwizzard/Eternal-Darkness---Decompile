typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

typedef struct CacheEntry {
    u8 bytes[0x22];
    u8 state;
    u8 tail;
} CacheEntry;

extern CacheEntry lbl_8061A9C4[8][4];
extern CacheEntry lbl_8061A544[8][4];
extern u32 lbl_80630770[8][16];

static inline void inpResetGlobalMIDIDirtyFlags(void)
{
    u32 i;
    u32 j;

    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 16; ++j) {
            lbl_80630770[i][j] = 0xff;
        }
    }
}

void fn_801CBE58(u8* voice)
{
    if (voice != 0) {
        voice[0x218] = 7;
        voice[0x219] = 0;
        *(u32*)(voice + 0x21C) = 0x10000;
        voice[0x220] = 11;
        voice[0x221] = 2;
        *(u32*)(voice + 0x224) = 0x10000;
        voice[0x23A] = 2;
        voice[0x23C] = 10;
        voice[0x23D] = 0;
        *(u32*)(voice + 0x240) = 0x10000;
        voice[0x25E] = 1;
        voice[0x260] = 0x83;
        voice[0x261] = 0;
        *(u32*)(voice + 0x264) = 0x10000;
        voice[0x282] = 1;
        voice[0x284] = 0x80;
        voice[0x285] = 0;
        *(u32*)(voice + 0x288) = 0x10000;
        voice[0x2A6] = 1;
        voice[0x2CC] = 1;
        voice[0x2CD] = 0;
        *(u32*)(voice + 0x2D0) = 0x10000;
        voice[0x2EE] = 1;
        voice[0x2F0] = 0x40;
        voice[0x2F1] = 0;
        *(u32*)(voice + 0x2F4) = 0x10000;
        voice[0x312] = 1;
        voice[0x314] = 0x41;
        voice[0x315] = 0;
        *(u32*)(voice + 0x318) = 0x10000;
        voice[0x336] = 1;
        voice[0x35A] = 0;
        voice[0x35C] = 0x5B;
        voice[0x35D] = 0;
        *(u32*)(voice + 0x360) = 0x10000;
        voice[0x37E] = 1;
        voice[0x3A2] = 0;
        voice[0x3A4] = 0x5D;
        voice[0x3A5] = 0;
        *(u32*)(voice + 0x3A8) = 0x10000;
        voice[0x3C6] = 1;
        voice[0x2A8] = 0x84;
        voice[0x2A9] = 0;
        *(u32*)(voice + 0x2AC) = 0x10000;
        voice[0x2CA] = 1;
        voice[0x3EA] = 0;
        *(u32*)(voice + 0x214) = 0x1FFF;
        voice[0x1D4] = 0;
        voice[0x1D5] = 0;
        voice[0xA8] = 0;
    } else {
        u32 i;
        u32 j;

        for (i = 0; i < 8; i++) {
            for (j = 0; j < 4; j++) {
                lbl_8061A9C4[i][j].state = 0;
                lbl_8061A544[i][j].state = 0;
            }
        }

        inpResetGlobalMIDIDirtyFlags();
    }
}
