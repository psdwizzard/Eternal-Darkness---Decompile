typedef unsigned char u8;
typedef unsigned int u32;

extern u32 synthTicksPerSecond[][16];

u32 synthGetTicksPerSecond(u8* source)
{
    u32 owner;

    if ((owner = source[0x122]) == 0xFF)
        owner = 8;
    return synthTicksPerSecond[owner][source[0x123]];
}
