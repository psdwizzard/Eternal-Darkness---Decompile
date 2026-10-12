typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 lbl_8064DB1C;
extern u32 lbl_8064DB20;
extern u32 lbl_8064DB24;
extern void DCFlushRange(void*, u32);
extern void DCInvalidateRange(void*, u32);
extern void* memset(void*, int, unsigned long);
extern void fn_80209AD4(void);

volatile u16 DSP[] : 0xCC005000;

static inline void WriteDMA(u32 memory, u32 aram, u32 length)
{
    DSP[0x10] = (DSP[0x10] & ~0x3FF) | (u16) (memory >> 16);
    DSP[0x11] = (DSP[0x11] & ~0xFFE0) | (u16) (memory & 0xFFFF);
    DSP[0x12] = (DSP[0x12] & ~0x3FF) | (u16) (aram >> 16);
    DSP[0x13] = (DSP[0x13] & ~0xFFE0) | (u16) (aram & 0xFFFF);
    DSP[0x14] &= ~0x8000;
    DSP[0x14] = (DSP[0x14] & ~0x3FF) | (u16) (length >> 16);
    DSP[0x15] = (DSP[0x15] & ~0xFFE0) | (u16) (length & 0xFFFF);
}

static inline void ReadDMA(u32 memory, u32 aram, u32 length)
{
    DSP[0x10] = (DSP[0x10] & ~0x3FF) | (u16) (memory >> 16);
    DSP[0x11] = (DSP[0x11] & ~0xFFE0) | (u16) (memory & 0xFFFF);
    DSP[0x12] = (DSP[0x12] & ~0x3FF) | (u16) (aram >> 16);
    DSP[0x13] = (DSP[0x13] & ~0xFFE0) | (u16) (aram & 0xFFFF);
    DSP[0x14] |= 0x8000;
    DSP[0x14] = (DSP[0x14] & ~0x3FF) | (u16) (length >> 16);
    DSP[0x15] = (DSP[0x15] & ~0xFFE0) | (u16) (length & 0xFFFF);
}

static inline void WaitDMA(void)
{
    while (DSP[5] & 0x200) {
    }
    DSP[5] = (DSP[5] & ~0x88) | 0x20;
}

/* Probe the expansion ARAM address lines by checking which test writes alias. */
void fn_8021ABE4(void)
{
    u8 testStorage[63];
    u8 clearStorage[63];
    u8 readStorage[63];
    u32* test;
    u32* clear;
    u32* read;
    u32 size;
    u16 mode;
    u32 i;

    while (!(DSP[0xB] & 1)) {
    }
    size = lbl_8064DB20 = 0x01000000;
    DSP[9] = (DSP[9] & ~0x3F) | 0x23;
    mode = 3;
    test = (u32*)(((u32)testStorage + 31) & ~31);
    clear = (u32*)(((u32)clearStorage + 31) & ~31);
    read = (u32*)(((u32)readStorage + 31) & ~31);
    for (i = 0; i < 8; i++) {
        test[i] = 0xDEADBEEF;
        clear[i] = 0xBAD0BAD0;
    }
    DCFlushRange(test, 32);
    DCFlushRange(clear, 32);
    lbl_8064DB24 = 0;

    WriteDMA((u32)clear, size, 32);
    WaitDMA();
    WriteDMA((u32)clear, size + 0x200000, 32);
    WaitDMA();
    WriteDMA((u32)clear, size + 0x1000000, 32);
    WaitDMA();
    WriteDMA((u32)clear, size + 0x200, 32);
    WaitDMA();
    WriteDMA((u32)clear, size + 0x400000, 32);
    WaitDMA();

    memset(read, 0, 32);
    DCFlushRange(read, 32);
    WriteDMA((u32)test, size, 32);
    WaitDMA();
    DCInvalidateRange(read, 32);
    ReadDMA((u32)read, size, 32);
    WaitDMA();
    fn_80209AD4();
    if (read[0] == test[0]) {
        memset(read, 0, 32);
        DCFlushRange(read, 32);
        ReadDMA((u32)read, size + 0x200000, 32);
        WaitDMA();
        fn_80209AD4();
        if (read[0] == test[0]) {
            lbl_8064DB24 = 0x200000;
            size += 0x200000;
        } else {
            memset(read, 0, 32);
            DCFlushRange(read, 32);
            ReadDMA((u32)read, size + 0x1000000, 32);
            WaitDMA();
            fn_80209AD4();
            if (read[0] == test[0]) {
                lbl_8064DB24 = 0x400000;
                mode |= 8;
                size += 0x400000;
            } else {
                memset(read, 0, 32);
                DCFlushRange(read, 32);
                ReadDMA((u32)read, size + 0x200, 32);
                WaitDMA();
                fn_80209AD4();
                if (read[0] == test[0]) {
                    lbl_8064DB24 = 0x800000;
                    mode |= 0x10;
                    size += 0x800000;
                } else {
                    memset(read, 0, 32);
                    DCFlushRange(read, 32);
                    ReadDMA((u32)read, size + 0x400000, 32);
                    WaitDMA();
                    fn_80209AD4();
                    if (read[0] == test[0]) {
                        lbl_8064DB24 = 0x1000000;
                        mode |= 0x18;
                        size += 0x1000000;
                    } else {
                        lbl_8064DB24 = 0x2000000;
                        mode |= 0x20;
                        size += 0x2000000;
                    }
                }
            }
        }
        DSP[9] = (DSP[9] & ~0x3F) | mode;
    }
    *(volatile u32*)0xC00000D0 = size;
    lbl_8064DB1C = size;
}
