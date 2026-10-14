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

extern HeapDesc *lbl_8064D920;
extern int lbl_8064D924;
extern void *lbl_8064D928;
extern void *lbl_8064D92C;
extern int lbl_8064C3C8;

void *fn_8020AF08(void *arenaStart, void *arenaEnd, int maxHeaps) {
    unsigned long descriptorBytes;
    int i;
    HeapDesc *hd;

    lbl_8064D920 = arenaStart;
    lbl_8064D924 = maxHeaps;
    descriptorBytes = maxHeaps * sizeof(HeapDesc);
    for (i = 0; i < lbl_8064D924; i++) {
        hd = &lbl_8064D920[i];
        hd->size = -1;
        hd->free = hd->allocated = 0;
    }
    lbl_8064C3C8 = -1;
    arenaStart = (char *)lbl_8064D920 + descriptorBytes;
    arenaStart = (void *)(((unsigned long)arenaStart + 31) & ~31UL);
    lbl_8064D928 = arenaStart;
    lbl_8064D92C = (void *)((unsigned long)arenaEnd & ~31UL);
    return arenaStart;
}
