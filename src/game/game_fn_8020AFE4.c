/* fn_8020AFE4 (0x8020AFE4, 864 bytes): OSCheckHeap (Dolphin OS alloc.c).
 * Walks the allocated and free cell lists of a heap and validates them,
 * returning the number of free bytes, or -1 on corruption. */

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

/* OSCheckHeap failure message strings ("OSCheckHeap: Failed ... in %d") */
extern char lbl_802FCD60[];

extern HeapDesc *lbl_8064D920; /* HeapArray */
extern int lbl_8064D924;       /* NumHeaps */
extern void *lbl_8064D928;     /* ArenaStart */
extern void *lbl_8064D92C;     /* ArenaEnd */

#define ASSERTREPORT(line, off, cond)        \
    if (!(cond)) {                           \
        OSReport(diagnostic.text + (off), line);   \
        return -1;                           \
    }

#define InRange(cell, start, end) \
    ((void *)(start) <= (void *)(cell) && (void *)(cell) < (void *)(end))

long fn_8020AFE4(int heap) {
    HeapDesc *hd;
    Cell *cell;
    long free;
    long total;
    /* Assertion messages share one packed string table. */
    struct { char *text; } diagnostic;

    total = 0;
    free = 0;
    diagnostic.text = lbl_802FCD60;

    ASSERTREPORT(0x37D, 0x0, lbl_8064D920);
    ASSERTREPORT(0x37E, 0x24, 0 <= heap && heap < lbl_8064D924);
    hd = &lbl_8064D920[heap];
    ASSERTREPORT(0x381, 0x5C, 0 <= hd->size);

    ASSERTREPORT(0x383, 0x84, hd->allocated == 0 || hd->allocated->prev == 0);
    for (cell = hd->allocated; cell; cell = cell->next) {
        ASSERTREPORT(0x386, 0xD4, InRange(cell, lbl_8064D928, lbl_8064D92C));
        ASSERTREPORT(0x387, 0x114, ((unsigned long)cell & 0x1F) == 0);
        ASSERTREPORT(0x388, 0x14C, cell->next == 0 || cell->next->prev == cell);
        ASSERTREPORT(0x389, 0x198, 0x40 <= cell->size);
        ASSERTREPORT(0x38A, 0x1CC, (cell->size & 0x1F) == 0);
        total += cell->size;
        ASSERTREPORT(0x38D, 0x20C, 0 < total && total <= hd->size);
    }

    ASSERTREPORT(0x395, 0x248, hd->free == 0 || hd->free->prev == 0);
    for (cell = hd->free; cell; cell = cell->next) {
        ASSERTREPORT(0x398, 0xD4, InRange(cell, lbl_8064D928, lbl_8064D92C));
        ASSERTREPORT(0x399, 0x114, ((unsigned long)cell & 0x1F) == 0);
        ASSERTREPORT(0x39A, 0x14C, cell->next == 0 || cell->next->prev == cell);
        ASSERTREPORT(0x39B, 0x198, 0x40 <= cell->size);
        ASSERTREPORT(0x39C, 0x1CC, (cell->size & 0x1F) == 0);
        ASSERTREPORT(0x39D, 0x290,
                     cell->next == 0 || (char *)cell + cell->size < (char *)cell->next);
        total += cell->size;
        free += cell->size - 0x20;
        ASSERTREPORT(0x3A1, 0x20C, 0 < total && total <= hd->size);
    }

    ASSERTREPORT(0x3A8, 0x2F0, total == hd->size);
    return free;
}
