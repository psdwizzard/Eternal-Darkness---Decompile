void ICInvalidateRange(void* address, register unsigned int length)
{
    register unsigned char* line = (unsigned char*)address;

    /* ASM: cmplwi/blelr retains the SDK's unsigned ordered zero check;
     * MWCC simplifies the C comparison against zero to an equality test. */
    asm {
        cmplwi length, 0
        blelr
    }
    if ((unsigned int)line & 31) {
        length += 32;
    }
    length = (length + 31) >> 5;

    /* ASM: mtctr initializes the hardware loop counter; MWCC emits a
     * general-register decrement for the equivalent C do-while loop. */
    asm { mtctr length }
invalidate_line:
    /* ASM: icbi invalidates an instruction-cache line; MWCC has no
     * intrinsic for this operation and C cannot express it. */
    asm { icbi 0, line }
    line += 32;
    /* ASM: bdnz decrements and tests CTR, which is not accessible in C. */
    asm { bdnz invalidate_line }
    __sync();
    __isync();
}
