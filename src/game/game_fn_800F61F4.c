asm void fn_800F61F4(void)
{
    nofralloc
    subfic r8, r5, 32
    subic r9, r5, 32
    slw r3, r3, r5
    srw r10, r4, r8
    or r3, r3, r10
    slw r10, r4, r9
    or r3, r3, r10
    slw r4, r4, r5
    blr
}
