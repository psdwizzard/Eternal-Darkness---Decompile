/* DCStoreRange: store (write back) all data-cache lines touched by the range
 * and synchronize through the system-call handler. Cache lines are 32 bytes. */
void fn_8020B774(register void *address, register unsigned int length)
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
     * a general-register decrement instead. */
    asm { mtctr length }
storeLine:
    /* ASM: dcbst writes back a data-cache line; C has no cache operation. */
    asm { dcbst 0, line }
    line += 32;
    /* ASM: bdnz decrements CTR and repeats; C cannot branch on CTR. */
    asm { bdnz storeLine }

    /* ASM: sc invokes the synchronization handler; C has no instruction
     * for issuing this system call. */
    asm { sc }
}
