typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

extern void* memcpy(void*, const void*, unsigned long);

u32 fn_801A81FC(u8* source, u16 count, u8* output)
{
    u8* record = output;
    int limit = count;
    u32 size = 0;
    int index = 0;

    while (index < limit) {
        memcpy(record + 0x68, source + (u16)size, 4);
        size += 4;
        record += 0x74;
        index++;
    }

    return (size + 0x1F) & 0xFFE0;
}
