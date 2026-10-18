asm void __TRK_set_MSR(unsigned int value)
{
    nofralloc
    mtmsr r3
    blr
}
