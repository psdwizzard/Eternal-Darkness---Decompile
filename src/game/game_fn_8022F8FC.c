/* Walk the debug heap until its free tail or an invalid block is found. */

typedef struct HeapBlock {
    unsigned int magic;
    int size;
} HeapBlock;

extern char *lbl_8064DC2C;

#define HEAP_FREE 0xBAADF00D
#define HEAP_USED 0x0A1BEEF0

void fn_8022F8FC(void) {
    HeapBlock *block = (HeapBlock *)(lbl_8064DC2C + 0x18);

    while (block->magic == HEAP_FREE || block->magic == HEAP_USED) {
        if (block->magic == HEAP_FREE) {
            return;
        }
        block = (HeapBlock *)((char *)block + block->size);
    }
}
