typedef unsigned short u16;
typedef unsigned int u32;

extern void* memcpy(void*, const void*, u32);

u16 fn_801E7508(const void* source, const u32* destination)
{
    u16 size = (*destination >> 2) + 4;
    int remainder;

    memcpy((void*)destination, source, size);
    remainder = size % 32;
    if (remainder != 0) {
        remainder = 32 - remainder;
        size += remainder;
    }
    return size;
}
