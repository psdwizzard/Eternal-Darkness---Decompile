/* Flush all cache lines touched by the range and synchronize through the
 * operating system's system-call handler. Cache lines are 32 bytes wide. */
void DCFlushRange(register void *address, register unsigned int length)
{
    register unsigned char *line = (unsigned char *)address;

    /* ASM: cmplwi/blelr implement the unsigned empty-range return. C folds
     * the unsigned comparison against zero into an equality-only branch. */
    asm {
        cmplwi length, 0
        blelr
    }

    if ((unsigned int)line & 31) {
        length += 32;
    }
    length = (length + 31) >> 5;

    /* ASM: mtctr sets the hardware loop count. The C do-while loop emits
     * a general-register decrement, while a for loop adds unrolling. */
    asm { mtctr length }
flushLine:
    /* ASM: dcbf flushes a hardware cache line; C has no cache operation. */
    asm { dcbf 0, line }
    line += 32;
    /* ASM: bdnz decrements the hardware loop count and repeats. C cannot
     * express a branch on CTR paired with the explicit mtctr above. */
    asm { bdnz flushLine }

    /* ASM: sc invokes the synchronization handler; C has no instruction
     * for issuing this system call. */
    asm { sc }
}
