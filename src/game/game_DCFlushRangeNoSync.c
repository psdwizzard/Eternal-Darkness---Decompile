/* Flush the data-cache lines touched by a range without synchronizing. */
void DCFlushRangeNoSync(register void *address, register unsigned int length)
{
    register unsigned char *line = (unsigned char *)address;

    /* ASM: cmplwi/blelr preserve the unsigned ordered empty-range check.
     * MWCC reduces the equivalent C comparison to an equality branch. */
    asm {
        cmplwi length, 0
        blelr
    }
    if ((unsigned int)line & 31) {
        length += 32;
    }
    length = (length + 31) >> 5;

    /* ASM: mtctr initializes the hardware loop count. The C do-while
     * loop uses a general-register decrement instead. */
    asm { mtctr length }
flush_line:
    /* ASM: dcbf flushes a hardware cache line, an operation C cannot express. */
    asm { dcbf 0, line }
    line += 32;
    /* ASM: bdnz decrements and tests CTR, which C cannot access. */
    asm { bdnz flush_line }
}
