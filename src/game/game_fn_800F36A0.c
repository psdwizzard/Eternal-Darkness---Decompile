asm unsigned int __TRK_get_MSR(void)
{
    nofralloc
    mfmsr r3
    blr
}
