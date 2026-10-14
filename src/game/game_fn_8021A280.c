/* AIGetStreamPlayState: return the stream playback enable bit. */
typedef unsigned int u32;

volatile u32 __AIRegs[8] : 0xCC006C00;

u32 fn_8021A280(void)
{
    return __AIRegs[0] & 1u;
}
