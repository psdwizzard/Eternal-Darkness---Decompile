typedef unsigned short u16;
typedef unsigned int u32;

extern void* memcpy(void*, const void*, u32);

u32 fn_801E74B8(const u32* source, void* destination)
{
    u16 size = (*source >> 2) + 4;

    memcpy(destination, source, size);
    return (u16)(size + 31) & 0xFFE0;
}
