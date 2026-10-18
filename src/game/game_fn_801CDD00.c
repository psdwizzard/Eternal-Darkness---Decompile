typedef unsigned int u32;
typedef unsigned char u8;

typedef struct HeapEntry HeapEntry;
struct HeapEntry {
    HeapEntry* next;
    u32 value;
    u32 size;
    u32 allocation_size;
};

extern HeapEntry aramStreamBuffers[];

u32 aramGetStreamBufferAddress(u8 index, u32* size)
{
    if (size != 0) {
        *size = aramStreamBuffers[index].size;
    }
    return aramStreamBuffers[index].value;
}
