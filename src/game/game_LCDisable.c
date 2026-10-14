/* Invalidate the locked cache before clearing HID2's locked-cache enable. */
void LCDisable(void)
{
    register unsigned char *line = (unsigned char *)0xE0000000;
    register unsigned int control = 512;

    /* ASM: mtctr initializes CTR; MWCC uses a general-register decrement
     * for the equivalent C loop containing cache invalidation. */
    asm { mtctr control }
invalidate_line:
    /* ASM: dcbi invalidates a hardware cache line, which C cannot express. */
    asm { dcbi 0, line }
    line += 32;
    /* ASM: bdnz decrements and tests CTR, which C cannot access. */
    asm { bdnz invalidate_line }

    /* ASM: mfspr reads HID2, a hardware register inaccessible to C. */
    asm { mfspr control, 920 }
    control &= ~0x10000000u;
    /* ASM: mtspr writes HID2, a hardware register inaccessible to C. */
    asm { mtspr 920, control }
}
