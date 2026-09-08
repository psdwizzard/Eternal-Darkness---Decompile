typedef unsigned char u8;
typedef unsigned int u32;

extern void fn_801E9124(u32*);

u32 fn_801EA774(const u8* source, const u8** output)
{
    u32 offset = 0;

    *output = source;
    offset += 0x11C;
    fn_801E9124(&offset);
    return offset;
}
