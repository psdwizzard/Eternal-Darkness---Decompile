/* AIGetDSPSampleRate: the hardware rate bit uses the inverse of the API value. */
typedef unsigned int u32;

volatile u32 __AIRegs[8] : 0xCC006C00;

u32 AIGetDSPSampleRate(void)
{
    return ((__AIRegs[0] >> 6) & 1u) ^ 1u;
}
