typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern volatile u16 *__peReg;

void fn_802267EC(u8 enable, u32 func, u8 update)
{
    u32 value = enable;

    /* Build the PE Z mode register: enable, compare function, update. */
    value = (value & ~0xEU) | (func << 1);
    value = (value & ~0x10U) | (update << 4);
    *__peReg = (u16)value;
}
