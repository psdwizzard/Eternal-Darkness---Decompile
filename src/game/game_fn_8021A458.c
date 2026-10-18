typedef unsigned int u32;

volatile u32 __AIRegs[8] : 0xCC006C00;

/* Read the audio stream sample-rate selection bit. */
u32 AIGetStreamSampleRate(void)
{
    return (__AIRegs[0] >> 1) & 1;
}
