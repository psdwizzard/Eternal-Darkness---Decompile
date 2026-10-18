/* Return an allocated cell to its heap and coalesce adjacent free cells. */
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
extern Cell *DLInsert(Cell *list, Cell *cell);

static Cell *DLExtract(Cell *list, Cell *cell) {
    if (cell->next) {
        cell->next->prev = cell->prev;
    }
    if (cell->prev == 0) {
        return cell->next;
    } else {
        cell->prev->next = cell->next;
        return list;
    }
}

void OSFreeToHeap(int heap, void *ptr) {
    HeapDesc *hd;
    Cell *cell;

    cell = (Cell *)((char *)ptr - 0x20);
    hd = &HeapArray[heap];
    hd->allocated = DLExtract(hd->allocated, cell);
    hd->free = DLInsert(hd->free, cell);
}
