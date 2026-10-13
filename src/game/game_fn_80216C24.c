typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct VITiming {
    u8 equ;
    u8 padding;
    u16 acv;
    u16 prbOdd, prbEven, psbOdd, psbEven;
    u8 bs[4];
    u16 be[4];
    u16 nhlines, hlw;
    u8 hsy, hcs, hce, hbe640;
    u16 hbs640;
    u8 hbeCCIR656;
    u16 hbsCCIR656;
} VITiming;

typedef struct VIData {
    VITiming timings[8];
    u16 taps[25];
} VIData;

extern VIData lbl_802FE710;

/* Select the video-interface timing for the encoded TV mode. */
VITiming *fn_80216C24(s32 mode)
{
    /* Values outside the supported mode range have no timing record. */
    if ((u32)mode <= 21) {
        register VITiming *timings;
        register u32 addressHigh;
        /* ASM: lis, addi load the timing table directly into its address register;
         * the equivalent C initialization introduces an extra register move. */
        asm {
            lis addressHigh, lbl_802FE710@ha
            addi timings, addressHigh, lbl_802FE710@l
        }

        switch (mode) {
        case 0: return timings;
        case 1: return timings + 1;
        case 4: return timings + 2;
        case 5: return timings + 3;
        case 20: return timings;
        case 21: return timings + 1;
        case 8: return timings + 4;
        case 9: return timings + 5;
        case 2: return timings + 6;
        case 3: return timings + 7;
        case 16: return timings + 2;
        case 17: return timings + 3;
        }
    }
    return 0;
}
