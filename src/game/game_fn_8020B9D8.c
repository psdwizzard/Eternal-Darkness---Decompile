/* Return the number of queued locked-cache DMA transfers. */
unsigned int fn_8020B9D8(void)
{
    register unsigned int count;
    register unsigned int status;

    /* ASM: mfspr reads HID2 through r4 and mr exposes it to C; C cannot
     * access this hardware register. The compiler eliminates the copy. */
    asm {
        mfspr r4, 920
        mr status, r4
    }
    count = (status >> 24) & 0xF;
    return count;
}
