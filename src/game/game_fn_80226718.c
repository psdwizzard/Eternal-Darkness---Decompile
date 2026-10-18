typedef unsigned short u16;
typedef unsigned long u32;
typedef int s32;

extern volatile u16 *__peReg;

void GXPokeBlendMode(s32 mode, u32 srcFactor, u32 dstFactor, u32 operation)
{
    volatile u16 *blendReg = &__peReg[1];
    u32 value = *blendReg;

    value = (value & ~1U) | (mode == 1 || mode == 3);
    value = (value & ~0x800U) | ((mode == 3) << 11);
    value = (value & ~2U) | ((mode == 2) << 1);
    value = (value & ~0xF000U) | (operation << 12);
    value = (value & ~0x700U) | (srcFactor << 8);
    value = (value & ~0xE0U) | (dstFactor << 5);
    value = (value & 0x00FFFFFF) | 0x41000000;
    *blendReg = value;
}
