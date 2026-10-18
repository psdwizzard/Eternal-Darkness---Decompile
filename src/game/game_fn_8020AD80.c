/* OSAllocFromHeap (0x8020AD80, 252 bytes): OSAllocFromHeap (Dolphin OS alloc.c).
 * First-fit allocation from a heap's free list; splits the chosen cell when
 * enough is left over and moves it to the front of the allocated list. */

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

extern HeapDesc *HeapArray; /* HeapArray */

static Cell *DLAddFront(Cell *list, Cell *cell) {
    cell->next = list;
    cell->prev = 0;
    if (list) {
        list->prev = cell;
    }
    return cell;
}

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

void *OSAllocFromHeap(int heap, unsigned long size) {
    HeapDesc *hd;
    Cell *cell;
    Cell *newCell;
    unsigned long leftoverSize;

    hd = &HeapArray[heap];
    size = (size + 0x20 + 0x1F) & ~0x1F;

    for (cell = hd->free; cell != 0; cell = cell->next) {
        if ((long)size <= (long)cell->size) {
            break;
        }
    }

    if (cell == 0) {
        return 0;
    }

    leftoverSize = cell->size - size;
    if (leftoverSize < 0x40) {
        hd->free = DLExtract(hd->free, cell);
    } else {
        cell->size = size;
        newCell = (Cell *)((char *)cell + size);
        newCell->size = leftoverSize;
        newCell->prev = cell->prev;
        newCell->next = cell->next;
        if (newCell->next != 0) {
            newCell->next->prev = newCell;
        }
        if (newCell->prev != 0) {
            newCell->prev->next = newCell;
        } else {
            hd->free = newCell;
        }
    }

    hd->allocated = DLAddFront(hd->allocated, cell);
    return (char *)cell + 0x20;
}
