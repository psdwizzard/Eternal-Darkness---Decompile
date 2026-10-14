typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern volatile u16 *__peReg;

void fn_802267BC(u8 enable, u8 alpha)
{
    u32 value = alpha;

    value = (value & ~0x100U) | (enable << 8);
    __peReg[2] = (u16)value;
}
