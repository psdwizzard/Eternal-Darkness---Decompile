typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern volatile u16 *__peReg;

void fn_802267D0(u8 enabled)
{
    volatile u16 *blendReg = &__peReg[1];
    u32 value = *blendReg;

    /* Update bit 2 of the PE blend register. */
    value = (value & ~4U) | (enabled << 2);
    *blendReg = (u16)value;
}
