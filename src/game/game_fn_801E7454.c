typedef unsigned char u8;
typedef unsigned int u32;

extern u32 fn_801E73A0(u32, u32, u32);

u32 fn_801E7454(const u8* data, u32 size)
{
    u32 value = 0;

    while (size != 0) {
        value = fn_801E73A0(value, *data, 0xA001);
        data++;
        size--;
    }
    return value;
}
