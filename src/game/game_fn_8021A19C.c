typedef unsigned int u32;

volatile u32 __AIRegs[8] : 0xCC006C00;

/* AISetStreamTrigger: set the sample count that triggers a stream interrupt. */
void AISetStreamTrigger(u32 sampleCount)
{
    __AIRegs[3] = sampleCount;
}
