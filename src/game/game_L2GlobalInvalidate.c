typedef unsigned int u32;

extern u32 PPCMfl2cr(void);
extern void PPCMtl2cr(u32 value);
extern void DBPrintf(const char* format, ...);

void L2GlobalInvalidate(void) {
    register u32 busy;
    register const char* message;
    register const char* argument;

    /* ASM: sync orders L2 cache accesses; C has no hardware barrier. */
    asm { sync }
    PPCMtl2cr(PPCMfl2cr() & 0x7FFFFFFFu);
    /* ASM: sync completes the L2 disable before invalidation;
     * C has no hardware barrier. */
    asm { sync }
    PPCMtl2cr(PPCMfl2cr() | 0x00200000u);

    /* ASM: b, b preserve the two branches to the next instruction at
     * polling entry. MWCC removes these in C and in symbolic inline asm,
     * so each b +4 is encoded explicitly. */
    asm {
        opword 0x48000004
        opword 0x48000004
    }
    do {
        busy = PPCMfl2cr();
        /* ASM: clrlwi keeps the status mask separate from the comparison;
         * C combines these into a recording mask instruction. */
        asm { clrlwi busy, busy, 31 }
    } while (busy != 0);

    PPCMtl2cr(PPCMfl2cr() & ~0x00200000u);
    /* ASM: b preserves the branch to the next instruction after clearing
     * L2I. MWCC removes symbolic fall-through branches; this encodes b +4. */
    asm { opword 0x48000004 }
    message = ">>> L2 INVALIDATE : SHOULD NEVER HAPPEN\n";
    /* ASM: b preserves the branch to the next instruction before checking
     * completion. MWCC removes symbolic fall-through branches. */
    asm { opword 0x48000004 }
    goto check_busy;
    do {
        /* ASM: or (mr) copies the diagnostic pointer into the argument;
         * C instead reconstructs the symbolic address with addi. */
        asm { or argument, message, message }
        DBPrintf(argument);
    check_busy:
        busy = PPCMfl2cr();
        /* ASM: clrlwi preserves the separate mask and unsigned comparison;
         * C combines them into a recording mask instruction. */
        asm { clrlwi busy, busy, 31 }
    } while (busy != 0);
}
