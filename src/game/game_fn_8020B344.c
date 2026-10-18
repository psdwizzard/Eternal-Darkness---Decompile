/* OSDumpHeap: report the allocated and free cells in a heap. */
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

extern void OSReport(const char *fmt, ...);
extern char lbl_802FCD60[];
extern HeapDesc *HeapArray;

void OSDumpHeap(int heap) {
    HeapDesc *hd;
    Cell *cell;
    struct { char *text; } diagnostic;

    diagnostic.text = lbl_802FCD60;
    OSReport(diagnostic.text + 0x31C, heap);
    hd = &HeapArray[heap];
    if (hd->size < 0) {
        OSReport(diagnostic.text + 0x330);
        return;
    }
    OSReport(diagnostic.text + 0x344);
    OSReport(diagnostic.text + 0x360);
    for (cell = hd->allocated; cell; cell = cell->next) {
        OSReport(diagnostic.text + 0x374, cell, cell->size,
                 (char *)cell + cell->size, cell->prev, cell->next);
    }
    OSReport(diagnostic.text + 0x384);
    for (cell = hd->free; cell; cell = cell->next) {
        OSReport(diagnostic.text + 0x374, cell, cell->size,
                 (char *)cell + cell->size, cell->prev, cell->next);
    }
}
