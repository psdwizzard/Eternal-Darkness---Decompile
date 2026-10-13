extern unsigned char gTRKState[];
extern unsigned short TRK_saved_exceptionID_80329FE8;

/* MetroTRK: first-level exception entry. The retail routine is a hand-written
 * asm function that runs with no stack, using r2 as its only scratch base and
 * restoring state with mtsrr0/mtsrr1/rfi; only its opening segment (stash the
 * interrupted r2/r4/CR in SRR0/SRR1/SPRG3 and switch MSR) is expressed here. */
void TRKInterruptHandler(void)
{
    /* ASM: mtsrr0/mtsrr1/mfsprg/mfcr/mtsprg + r2 base - supervisor SPR moves
     * with fixed registers on a frameless exception path; C has no access */
    asm {
        mtsrr0 r2
        mtsrr1 r4
        mfsprg r4, 3
        mfcr r2
        mtsprg 3, r2
        lis r2, gTRKState@h
        ori r2, r2, gTRKState@l
        lwz r2, 0x8c(r2)
    }
    /* ASM: ori/xori 0x8002 + sync/mtmsr on r2 - clears MSR[EE,RI] via mtmsr,
     * which C cannot express, using r2 as the only free register */
    asm {
        ori r2, r2, 0x8002
        xori r2, r2, 0x8002
        sync
        mtmsr r2
        sync
    }
    /* ASM: lis/ori/sth via r2 - saves the exception ID (r3) with r2 as the
     * only free base register; C cannot pin the base to r2 */
    asm {
        lis r2, TRK_saved_exceptionID_80329FE8@h
        ori r2, r2, TRK_saved_exceptionID_80329FE8@l
        sth r3, 0x0(r2)
    }
}
