typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

extern volatile u16 *__peReg;

void fn_802266FC(u8 enable)
{
    volatile u16 *blendReg = &__peReg[1];
    u32 value = *blendReg;

    value = (value & ~0x10U) | (enable << 4);
    *blendReg = value;
}
