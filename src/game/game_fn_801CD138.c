typedef unsigned char u8;
typedef unsigned int u32;

extern void* aramGetStreamBufferAddress(u8 index, void** info);
extern void DCStoreRange(void* address, u32 length);
extern void aramUploadData(void* destination, void* source, u32 length,
                       u32 mode, u32 arg7, u32 arg8);

void fn_801CD138(void* destination, u32 offset, u32 length, u8 index,
                 u32 arg7, u32 arg8)
{
    void* info;
    void* source;
    void* out = destination;

    source = aramGetStreamBufferAddress(index, &info);
    length += offset & 0x1F;
    offset &= ~0x1F;
    length = (length + 0x1F) & ~0x1F;
    out = (u8*)out + offset;
    DCStoreRange(out, length);
    aramUploadData(out, (u8*)source + offset, length,
                1, arg7, arg8);
}
