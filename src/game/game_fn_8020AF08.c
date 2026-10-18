/* Initialize heap descriptors and align the usable arena to 32 bytes. */
typedef struct Cell {
    struct Cell *prev;
    struct Cell *next;
    unsigned long size;
} Cell;

typedef struct HeapDesc {
    long size;
    Cell *free;
    Cell *allocated;
} HeapDesc;

extern HeapDesc *HeapArray;
extern int NumHeaps;
extern void *ArenaStart;
extern void *ArenaEnd;
extern int __OSCurrHeap;

void *OSInitAlloc(void *arenaStart, void *arenaEnd, int maxHeaps) {
    unsigned long descriptorBytes;
    int i;
    HeapDesc *hd;

    HeapArray = arenaStart;
    NumHeaps = maxHeaps;
    descriptorBytes = maxHeaps * sizeof(HeapDesc);
    for (i = 0; i < NumHeaps; i++) {
        hd = &HeapArray[i];
        hd->size = -1;
        hd->free = hd->allocated = 0;
    }
    __OSCurrHeap = -1;
    arenaStart = (char *)HeapArray + descriptorBytes;
    arenaStart = (void *)(((unsigned long)arenaStart + 31) & ~31UL);
    ArenaStart = arenaStart;
    ArenaEnd = (void *)((unsigned long)arenaEnd & ~31UL);
    return arenaStart;
}
