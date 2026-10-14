/* Invalidate each 32-byte data-cache line touched by the range. */
void DCInvalidateRange(void *address, register unsigned int length)
{
    register unsigned char *line = (unsigned char *)address;

    /* ASM: cmplwi/blelr preserve the unsigned ordered empty-range check.
     * MWCC simplifies the equivalent C comparison to an equality branch. */
    asm {
        cmplwi length, 0
        blelr
    }
    if ((unsigned int)line & 31) {
        length += 32;
    }
    length = (length + 31) >> 5;

    /* ASM: mtctr initializes the hardware loop counter. MWCC uses a
     * general-register decrement for the equivalent C do-while loop. */
    asm { mtctr length }
invalidate_line:
    /* ASM: dcbi invalidates a hardware data-cache line, an operation
     * that cannot be expressed in C. */
    asm { dcbi 0, line }
    line += 32;
    /* ASM: bdnz decrements and tests CTR, which is not accessible in C. */
    asm { bdnz invalidate_line }
}
