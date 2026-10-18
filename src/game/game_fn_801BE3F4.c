typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

extern u8* dataGetCurve(u32);

u32 TranslateVolume(u32 value, u32 resource)
{
    u8* table;
    u32 index;
    u32 result;
    u32 current;
    u16 fraction;
    volatile u64 stack_align;

    if ((u16)resource != 0xFFFF) {
        table = dataGetCurve(resource);
        if (table != 0) {
            index = value >> 16;
            fraction = (u16)value;
            if (index < 0x7F) {
                current = table[index];
                result = table[index + 1];
                result = (result - current) * fraction;
                value = result + (current << 16);
            } else {
                value = table[index] << 16;
            }
        }
    }
    return value;
}
