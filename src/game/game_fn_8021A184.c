typedef unsigned int u32;

volatile u32 __AIRegs[8] : 0xCC006C00;

/* AIResetStreamSampleCount: pulse the stream sample counter reset bit. */
void fn_8021A184(void)
{
    __AIRegs[0] = (__AIRegs[0] & ~0x20) | 0x20;
}
