extern unsigned char gTRKCPUState[];

/* MetroTRK: snapshot the supervisor-level special registers into gTRKCPUState.
 * The retail routine is a hand-written asm function (r2 as base, stmw of
 * r16-r31); only its opening segment-register reads are expressed here. */
void TRKSaveExtended1Block(void)
{
    /* ASM: lis/ori r2 + mfsr r16-r21 - segment registers have no C or intrinsic access */
    asm {
        lis r2, gTRKCPUState@h
        ori r2, r2, gTRKCPUState@l
        mfsr r16, 0
        mfsr r17, 1
        mfsr r18, 2
        mfsr r19, 3
        mfsr r20, 4
        mfsr r21, 5
    }
    /* ASM: mfsr r22-r29 - segment registers have no C or intrinsic access */
    asm {
        mfsr r22, 6
        mfsr r23, 7
        mfsr r24, 8
        mfsr r25, 9
        mfsr r26, 10
        mfsr r27, 11
        mfsr r28, 12
        mfsr r29, 13
    }
}
