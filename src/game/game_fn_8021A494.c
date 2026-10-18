/* Set the right audio stream volume. */
typedef unsigned char u8;
typedef unsigned int u32;

volatile u32 __AIRegs[8] : 0xCC006C00;

void AISetStreamVolRight(u8 volume)
{
    __AIRegs[1] = (__AIRegs[1] & ~0xFF00) | (volume << 8);
}
