typedef struct StreamBlock {
    unsigned char* data;
    int unknown04;
    int start;
    int end;
    int state;
} StreamBlock;

typedef struct StreamState {
    unsigned char mutex[0x18];
    unsigned char threadStorage[0x1350];
    unsigned char completionQueue[0x20];
    unsigned char commandStorage[0x40];
    unsigned char commandQueue[0x20];
    StreamBlock blocks[3];
} StreamState;

extern StreamState lbl_8032D648;
extern const volatile char lbl_8023A220[72];
extern const char lbl_8064FE58[8];
typedef struct OSMessageQueue OSMessageQueue;
extern int fn_8020D318(OSMessageQueue*, void**, int);
extern int fn_8020D250(OSMessageQueue*, void*, int);
extern void fn_8020D7E0(void*);
extern void fn_8020D8BC(void*);
extern void fn_8020C5D0(const char*, int, const char*, ...);
extern void* memcpy(void*, const void*, unsigned long);

static inline StreamBlock* findPrevious(register unsigned long base)
{
    register StreamBlock* block;
    int i;

    /* ASM: addi materializes the block-array pointer before its state load;
     * C folds the load into the enclosing object's address otherwise. */
    asm { addi block, base, 0x13E8 }
    for (i = 0; i < 3; i++, block++) {
        if (block->state == 3) {
            return block;
        }
    }
    return 0;
}

int fn_80108558(register void* destination, register int size, register int offset)
{
    register unsigned long base = (unsigned long)&lbl_8032D648;
    register void* mutex;
    register int nextState;
    void* message;
    StreamBlock* block;
    register StreamBlock* previous;
    int i;

    for (;;) {
        if (fn_8020D318((OSMessageQueue*)(base + 0x1368), &message, 0) != 0) {
            break;
        }
        /* ASM: addi keeps the mutex's zero-offset address calculation;
         * the optimizer otherwise reduces it to mr. */
        asm { addi mutex, base, 0 }
        fn_8020D7E0(mutex);
        for (i = 0, block = (StreamBlock*)(base + 0x13E8); i < 3; i++, block++) {
            if (block->state == 2 && block->start <= offset && offset < block->end) {
                if (offset + size > block->end) {
                    fn_8020C5D0((const char*)lbl_8023A220, 0x1AC, lbl_8064FE58);
                }
                if (destination != 0) {
                    memcpy(destination, block->data + offset - block->start, size);
                }
                /* Release the previously consumed block for reuse. */
                previous = findPrevious(base);
                if (previous != 0) {
                    previous->state = 0;
                }
                /* ASM: li/addi preserve the state constant's ordering before
                 * the mutex address, which C schedules after this barrier. */
                asm {
                    li nextState, 3
                    addi mutex, base, 0
                }
                block->state = nextState;
                fn_8020D8BC(mutex);
                if (previous != 0) {
                    fn_8020D250((OSMessageQueue*)(base + 0x13C8), (void*)3, 0);
                }
                return size;
            }
        }
        /* ASM: addi keeps the mutex's zero-offset address calculation. */
        asm { addi mutex, base, 0 }
        fn_8020D8BC(mutex);
    }
    return -1;
}
