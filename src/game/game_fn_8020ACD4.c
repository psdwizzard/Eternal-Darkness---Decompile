/* Insert a free heap cell in address order and coalesce adjacent cells. */
typedef struct Cell {
    struct Cell *prev;
    struct Cell *next;
    unsigned long size;
} Cell;

Cell *DLInsert(Cell *list, Cell *cell) {
    Cell *prev;
    Cell *next;

    for (next = list, prev = 0; next != 0; prev = next, next = next->next) {
        if (cell <= next) {
            break;
        }
    }

    cell->next = next;
    cell->prev = prev;
    if (next != 0) {
        next->prev = cell;
        if ((char *)cell + cell->size == (char *)next) {
            cell->size += next->size;
            next = next->next;
            cell->next = next;
            if (next != 0) {
                next->prev = cell;
            }
        }
    }

    if (prev != 0) {
        prev->next = cell;
        if ((char *)prev + prev->size == (char *)cell) {
            prev->size += cell->size;
            prev->next = next;
            if (next != 0) {
                next->prev = prev;
            }
        }
        return list;
    }
    return cell;
}
