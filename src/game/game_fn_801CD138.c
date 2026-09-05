typedef unsigned char u8;
typedef unsigned int u32;

extern void* fn_801CDD00(u8 index, void** info);
extern void fn_8020B774(void* address, u32 length);
extern void fn_801CD5D0(void* destination, void* source, u32 length,
                       u32 mode, u32 arg7, u32 arg8);

void fn_801CD138(void* destination, u32 offset, u32 length, u8 index,
                 u32 arg7, u32 arg8)
{
    register void* source;
    void* info;
    register void* out = destination;
    register u32 saved_arg8 = arg8;
    register u32 saved_arg7 = arg7;
    register u32 saved_length = length;
    register u32 saved_offset = offset;

    source = fn_801CDD00(index, &info);
    saved_length += saved_offset & 0x1F;
    saved_offset &= ~0x1F;
    saved_length = (saved_length + 0x1F) & ~0x1F;
    out = (u8*)out + saved_offset;
    fn_8020B774(out, saved_length);
    fn_801CD5D0(out, (u8*)source + saved_offset, saved_length,
                1, saved_arg7, saved_arg8);
}
