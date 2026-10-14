typedef unsigned int u32;

/* System-call exception vector: flush the gather pipe, then restore HID0. */
void fn_8020F120(void)
{
    register u32 savedHid0;
    register u32 flushHid0;

    /* ASM: mfspr reads HID0, which is not accessible through C. */
    asm { mfspr savedHid0, 1008 }
    flushHid0 = savedHid0 | 8;
    /* ASM: mtspr writes HID0, which is not accessible through C. */
    asm { mtspr 1008, flushHid0 }
    __isync();
    __sync();
    /* ASM: mtspr restores HID0; rfi returns from the exception using SRR0
     * and SRR1, a control transfer that C cannot express. */
    asm {
        mtspr 1008, savedHid0
        rfi
    }
}
