asm void TRK_ppc_memcpy(void *destination, const void *source, unsigned int length,
                     unsigned int read_msr, unsigned int write_msr)
{
    nofralloc
    mfmsr r8
    li r10, 0
loop:
    cmpw r10, r5
    beq done
    mtmsr r7
    sync
    lbzx r9, r10, r4
    mtmsr r6
    sync
    stbx r9, r10, r3
    addi r10, r10, 1
    b loop
done:
    mtmsr r8
    sync
    blr
}
