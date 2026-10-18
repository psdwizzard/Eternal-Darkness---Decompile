typedef unsigned int u32;
typedef unsigned char u8;

typedef struct HeapEntry HeapEntry;
struct HeapEntry {
    HeapEntry* next;
    u32 value;
    u32 size;
    u32 allocation_size;
};

typedef struct HeapStorage {
    u8 pad[0x508];
    HeapEntry entries[64];
} HeapStorage;

extern HeapStorage aramQueueLo;
extern HeapEntry* aramUsedStreamBuffers;
extern HeapEntry* aramFreeStreamBuffers;
extern HeapEntry* aramIdleStreamBuffers;
extern u32 aramTop;
extern u32 aramStream;

void InitStreamBuffers(void)
{
    u8* base = (u8*)&aramQueueLo;
    u32 i;

    aramUsedStreamBuffers = 0;
    aramFreeStreamBuffers = 0;
    aramIdleStreamBuffers = (HeapEntry*)(base + 0x508);
    for (i = 1; i < 64; i++) {
        ((HeapEntry*)(base + 0x508))[i - 1].next =
            &((HeapEntry*)(base + 0x508))[i];
    }
    ((HeapEntry*)(base + 0x508))[i - 1].next = 0;
    aramStream = aramTop;
}
