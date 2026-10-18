/* Wait until the locked-cache DMA queue has at most count entries. */
void LCQueueWait(register int count)
{
    register unsigned int status;

    count += 1;
waitForQueue:
    /* ASM: mfspr reads HID2, a hardware register inaccessible to C. */
    asm { mfspr status, 920 }
    status = (status >> 24) & 0xF;
    /* ASM: cmpw and bge use CR2, which C cannot select for its comparison. */
    asm {
        cmpw cr2, status, count
        bge cr2, waitForQueue
    }
}
