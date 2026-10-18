/* Get the right audio stream volume. */
typedef unsigned char u8;
typedef unsigned int u32;

volatile u32 __AIRegs[8] : 0xCC006C00;

u8 AIGetStreamVolRight(void)
{
    return (__AIRegs[1] >> 8) & 0xFF;
}
