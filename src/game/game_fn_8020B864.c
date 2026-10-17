typedef unsigned int u32;

/* Enable the locked cache and initialize its 16 KiB backing store. */
void fn_8020B864(void)
{
    register unsigned char *line;
    register u32 count;
    register u32 state;

    /* ASM: mfmsr reads MSR, which C cannot directly access. */
    asm { mfmsr state }
    state |= 0x1000;
    /* ASM: mtmsr writes the machine-check enable bit to MSR. */
    asm { mtmsr state }

    line = (unsigned char *)0x80000000;
    count = 1024;
    /* ASM: mtctr initializes the cache-line hardware loop counter. */
    asm { mtctr count }
warmLine:
    {
        __dcbt(line, 0);
        __dcbst(line, 0);
        line += 32;
    }
    /* ASM: bdnz iterates using CTR, which C cannot explicitly access. */
    asm { bdnz warmLine }

    /* ASM: mfspr reads HID2, which C cannot access directly. */
    asm { mfspr count, 920 }
    count |= 0x100F0000;
    /* ASM: mtspr writes the locked-cache enable bits to HID2. */
    asm { mtspr 920, count }
    for (count = 6; count != 0; --count) {
        /* ASM: nop, nop provide two settling cycles per iteration.
         * Empty C statements are removed; six iterations give twelve NOPs. */
        asm {
            nop
            nop
        }
    }

    line = (unsigned char *)0xE0000000;
    /* ASM: ori sets BAT read/write protection; C folds this into addi instead. */
    asm { ori line, line, 2 }
    /* ASM: mtdbatl programs the lower half of data BAT 3. */
    asm { mtdbatl 3, line }
    line = (unsigned char *)((u32)line | 0x1FE);
    /* ASM: mtdbatu programs the upper half of data BAT 3. */
    asm { mtdbatu 3, line }
    __isync();

    line = (unsigned char *)0xE0000000;
    count = 512;
    /* ASM: mtctr initializes the locked-cache hardware loop counter. */
    asm { mtctr count }
    count = 0;
clearLine:
    {
        /* ASM: dcbz_l zeros and locks a cache line; __dcbz does not lock it. */
        asm { dcbz_l count, line }
        line += 32;
    }
    /* ASM: bdnz advances the hardware loop without a software decrement. */
    asm { bdnz clearLine }
    for (count = 6; count != 0; --count) {
        /* ASM: nop, nop provide two settling cycles per iteration.
         * Empty C statements are removed; six iterations give twelve NOPs. */
        asm {
            nop
            nop
        }
    }
}
