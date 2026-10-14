/* Create a heap from a region aligned to 32-byte boundaries. */
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

int fn_8020AF78(void *start, void *end) {
    HeapDesc *hd;
    Cell *cell;
    int i;
    int count;

    hd = lbl_8064D920;
    count = lbl_8064D924;
    start = (void *)(((unsigned long)start + 31) & ~31UL);
    end = (void *)((unsigned long)end & ~31UL);
    for (i = 0; i < count; hd++, i++) {
        if (hd->size < 0) {
            hd->size = (char *)end - (char *)start;
            cell = (Cell *)start;
            cell->prev = 0;
            cell->next = 0;
            cell->size = hd->size;
            hd->free = cell;
            hd->allocated = 0;
            return i;
        }
    }
    return -1;
}
