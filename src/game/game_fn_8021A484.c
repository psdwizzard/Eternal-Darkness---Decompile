/* Get the left audio stream volume. */
typedef unsigned int u32;

volatile u32 __AIRegs[8] : 0xCC006C00;

u32 fn_8021A484(void)
{
    return __AIRegs[1] & 0xFF;
}
