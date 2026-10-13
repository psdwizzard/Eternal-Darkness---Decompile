/* fn_8022F780 (0x8022F780, 212 bytes): bump allocator on the debug heap.
 * Blocks carry a header {magic, size}; the free tail is tagged 0xBAADF00D and
 * allocated blocks 0x0A1BEEF0. The heap walk is a validity check whose
 * diagnostics were compiled out. */

typedef struct HeapBlock {
    unsigned int magic;
    int size;
} HeapBlock;

extern int lbl_8064DC0C;
extern int lbl_8064DC20;
extern char *lbl_8064DC24;
extern char *lbl_8064DC2C;

#define HEAP_FREE 0xBAADF00D
#define HEAP_USED 0x0A1BEEF0

static inline void HeapWalk(void) {
    HeapBlock *block = (HeapBlock *)(lbl_8064DC2C + 0x18);
    while (block->magic == HEAP_FREE || block->magic == HEAP_USED) {
        if (block->magic == HEAP_FREE) {
            return;
        }
        block = (HeapBlock *)((char *)block + block->size);
    }
}

void *fn_8022F780(int size) {
    char *top;
    int remaining;
    HeapBlock *tail;

    HeapWalk();
    size = (size + 0xB) & ~3;
    top = lbl_8064DC24;
    remaining = lbl_8064DC20 - size;
    lbl_8064DC20 = remaining;
    lbl_8064DC24 += size;
    if (remaining < lbl_8064DC0C) {
        lbl_8064DC0C = remaining;
    }
    ((HeapBlock *)top)[-1].size = size;
    ((HeapBlock *)top)[-1].magic = HEAP_USED;
    tail = (HeapBlock *)lbl_8064DC24;
    tail[-1].magic = HEAP_FREE;
    tail[-1].size = 0;
    HeapWalk();
    return top;
}
