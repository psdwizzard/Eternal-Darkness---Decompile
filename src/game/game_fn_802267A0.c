typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern volatile u16 *__peReg;

void fn_802267A0(u8 enable)
{
    volatile u16 *blendReg = &__peReg[1];
    u32 value = *blendReg;

    value = (value & ~8U) | (enable << 3);
    *blendReg = value;
}
