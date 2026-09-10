asm void fn_800F623C(void)
{
    nofralloc
    subfic r8, r5, 0x20
    addic. r9, r5, -0x20
    srw r4, r4, r5
    slw r10, r3, r8
    or r4, r4, r10
    sraw r10, r3, r9
    ble around
    or r4, r4, r10
around:
    sraw r3, r3, r5
    blr
}
