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
extern HeapEntry* aramUsedStreamBuffers;
extern HeapEntry* aramFreeStreamBuffers;
extern HeapEntry* aramIdleStreamBuffers;
extern u32 aramTop;
extern u32 aramWrite;
extern u32 aramStream;

u8 aramAllocateStreamBuffer(u32 size)
{
    HeapEntry* selected = 0;
    HeapEntry* entry = aramFreeStreamBuffers;
    HeapEntry* previous = 0;
    u32 best_size = -1;
    u32 rounded = (size + 31) & ~31;

    while (entry != 0) {
        if (entry->allocation_size == rounded) {
            selected = entry;
            break;
        }
        if (entry->allocation_size > rounded && best_size > entry->allocation_size) {
            selected = entry;
            best_size = entry->allocation_size;
        }
        previous = entry;
        entry = entry->next;
    }

    if (selected == 0) {
        entry = aramIdleStreamBuffers;
        if (entry != 0 && aramStream - rounded >= aramWrite) {
            aramIdleStreamBuffers = entry->next;
            selected = entry;
            entry->allocation_size = rounded;
            entry->size = rounded;
            aramStream -= rounded;
            entry->value = aramStream;
            entry->next = aramUsedStreamBuffers;
            aramUsedStreamBuffers = entry;
        }
    } else {
        if (previous != 0) {
            previous->next = selected->next;
        } else {
            aramFreeStreamBuffers = selected->next;
        }
        selected->size = rounded;
        selected->next = aramUsedStreamBuffers;
        aramUsedStreamBuffers = selected;
    }

    if (selected == 0) {
        return 255;
    }
    return selected - aramStreamBuffers;
}
