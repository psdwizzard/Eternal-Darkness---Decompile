typedef signed short s16;
typedef unsigned int u32;

extern s16 sndSintab[];

int sndSin(u32 angle)
{
    u32 index = angle & 0xFFF;
    s16* table = sndSintab;

    if (index < 0x400) {
        return table[index];
    }
    if (index < 0x800) {
        return table[0x3FF - (index & 0x3FF)];
    }
    if (index < 0xC00) {
        return -table[index & 0x3FF];
    }
    return -table[0x3FF - (index & 0x3FF)];
}
