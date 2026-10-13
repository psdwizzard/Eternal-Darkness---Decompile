typedef unsigned int u32;
extern unsigned char gTRKCPUState[];

/* Save SR0-SR15 at the segment-register offset in the extended CPU state.
 * The remaining supervisor-register groups are not yet implemented. */
void TRKSaveExtended1Block(void)
{
    register u32 sr0, sr1, sr2, sr3, sr4, sr5, sr6, sr7, sr8, sr9, sr10, sr11, sr12, sr13, sr14, sr15;
    u32 *segments = (u32 *)(gTRKCPUState + 0x1A8);

    /* ASM: mfsr reads SR0-SR7; MWCC has no segment-register read intrinsic. */
    asm {
        mfsr sr0, 0
        mfsr sr1, 1
        mfsr sr2, 2
        mfsr sr3, 3
        mfsr sr4, 4
        mfsr sr5, 5
        mfsr sr6, 6
        mfsr sr7, 7
    }
    /* ASM: mfsr reads SR8-SR15; MWCC has no segment-register read intrinsic. */
    asm {
        mfsr sr8, 8
        mfsr sr9, 9
        mfsr sr10, 10
        mfsr sr11, 11
        mfsr sr12, 12
        mfsr sr13, 13
        mfsr sr14, 14
        mfsr sr15, 15
    }
    segments[0] = sr0;
    segments[1] = sr1;
    segments[2] = sr2;
    segments[3] = sr3;
    segments[4] = sr4;
    segments[5] = sr5;
    segments[6] = sr6;
    segments[7] = sr7;
    segments[8] = sr8;
    segments[9] = sr9;
    segments[10] = sr10;
    segments[11] = sr11;
    segments[12] = sr12;
    segments[13] = sr13;
    segments[14] = sr14;
    segments[15] = sr15;
}
