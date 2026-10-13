typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TRKExceptionStatus {
    u32 PC;
    u32 instruction;
    u16 exceptionID;
    u8 reserved[3];
    u8 exceptionDetected;
    u8 padding[2];
} TRKExceptionStatus;

extern TRKExceptionStatus gTRKExceptionStatus_8024A864;

/* MetroTRK: exception handler used while the nub itself is probing memory.
 * Records the exception ID and faulting PC, skips the faulting instruction
 * for recoverable exceptions, flags the exception and returns via rfi. The
 * retail routine is hand-written asm with no stack frame and r2 as its only
 * scratch base. */
void TRKExceptionHandler(u16 exceptionID)
{
    register int id;

    /* ASM: lis/ori/sth/mfsrr0/stw/lhz via r2 - stores the exception ID and
     * SRR0 with r2 as the only free base; C cannot read SRR0 or pin r2 */
    asm {
        lis r2, gTRKExceptionStatus_8024A864@h
        ori r2, r2, gTRKExceptionStatus_8024A864@l
        sth r3, 0x8(r2)
        mfsrr0 r3
        stw r3, 0x0(r2)
        lhz id, 0x8(r2)
    }

    if (id == 0x200 || id == 0x300 || id == 0x400 || id == 0x600 ||
        id == 0x700 || id == 0x800 || id == 0x1000 || id == 0x1100 ||
        id == 0x1200 || id == 0x1300) {
        /* ASM: mfsrr0/addi/mtsrr0 - advances SRR0 past the faulting
         * instruction; C has no access to supervisor SPRs */
        asm {
            mfsrr0 r3
            addi r3, r3, 0x4
            mtsrr0 r3
        }
    }

    gTRKExceptionStatus_8024A864.exceptionDetected = 1;

    /* ASM: mfsprg/mtcrf/mfsprg/mfsprg/rfi - restores CR, r2 and r3 saved
     * by the first-level handler and returns from the exception */
    asm {
        mfsprg r3, 3
        mtcrf 255, r3
        mfsprg r2, 1
        mfsprg r3, 2
        rfi
    }
}
