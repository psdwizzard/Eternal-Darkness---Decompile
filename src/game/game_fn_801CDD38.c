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
extern u32 aramStream;

void aramFreeStreamBuffer(u8 index)
{
    HeapEntry* target = &aramStreamBuffers[index];
    HeapEntry* entry = aramUsedStreamBuffers;
    HeapEntry* previous = 0;

    while (entry != 0) {
        if (entry == target) {
            if (previous != 0) {
                previous->next = target->next;
            } else {
                aramUsedStreamBuffers = target->next;
            }
            break;
        }
        previous = entry;
        entry = entry->next;
    }

    if (target->value == aramStream) {
        u32 lowest = -1;

        target->next = aramIdleStreamBuffers;
        aramIdleStreamBuffers = target;

        entry = aramUsedStreamBuffers;
        while (entry != 0) {
            if (entry->value <= lowest) {
                lowest = entry->value;
            }
            entry = entry->next;
        }

        {
            HeapEntry* next;
            HeapEntry* current = aramFreeStreamBuffers;
            while (current != 0) {
                next = current->next;
                if (current->value < lowest) {
                    aramFreeStreamBuffers = next;
                    current->next = aramIdleStreamBuffers;
                    aramIdleStreamBuffers = current;
                }
                current = next;
            }
        }

        aramStream = lowest != -1 ? lowest : aramTop;
    } else {
        target->next = aramFreeStreamBuffers;
        aramFreeStreamBuffers = target;
    }
}
