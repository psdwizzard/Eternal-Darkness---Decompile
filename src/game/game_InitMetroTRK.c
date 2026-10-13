/* InitMetroTRK: MetroTRK debugger entry. Snapshots the full CPU state into
 * gTRKCPUState, disables external interrupts, clears the hardware
 * breakpoints, switches to the debugger stack and enters the TRK main loop.
 * The original is a hand-written asm routine; only the register-level
 * pieces C cannot express are kept as inline asm. */

typedef unsigned int u32;

extern u32 gTRKCPUState[];
extern unsigned char _db_stack_addr[];

void TRKSaveExtended1Block(void);
int InitMetroTRKCommTable(int hwId);
void TRK_main(void);

void InitMetroTRK(int hwId) {
    register u32 *state;
    register u32 msr;
    register u32 lr;
    register u32 cr;

    state = gTRKCPUState;
    /* ASM: stmw - store all 32 GPRs (including r1/r2/r13) into the TRK
     * CPU state block; C has no way to name every GPR. */
    asm {
        stmw r0, 0(state)
        stw r1, 4(state)
    }
    state[3] = hwId;
    /* ASM: mflr/mfcr - capture the caller's LR and CR as the resume PC and
     * condition register; C cannot read these registers, and the stores
     * must stay interleaved with the SPR reads. */
    asm {
        mflr lr
        stw lr, 0x84(state)
        stw lr, 0x80(state)
        mfcr cr
        stw cr, 0x88(state)
    }
    /* ASM: mfmsr/ori/xori/mtmsr/mtsrr1 - clear MSR[EE] and stash the old
     * MSR in SRR1; supervisor register moves have no C equivalent. */
    asm {
        mfmsr msr
        ori r3, msr, 0x8000
        xori r3, r3, 0x8000
        mtmsr r3
        mtsrr1 msr
    }
    TRKSaveExtended1Block();
    /* ASM: li/mtspr - clear the IABR/DABR hardware breakpoints; these
     * supervisor SPRs are unreachable from C. */
    asm {
        li r0, 0
        mtspr IABR, r0
        mtspr DABR, r0
    }
    if (InitMetroTRKCommTable(hwId) != 1) {
        TRK_main();
    }
}
