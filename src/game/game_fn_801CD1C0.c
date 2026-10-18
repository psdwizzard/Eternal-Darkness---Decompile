typedef unsigned char u8;
typedef unsigned int u32;

extern u8 aramAllocateStreamBuffer(u32 size, u32 arg1, u32 arg2, u32 arg3);

u8 hwInitStream(u32 size, u32 arg1, u32 arg2, u32 arg3)
{
    return aramAllocateStreamBuffer(size, arg1, arg2, arg3);
}
