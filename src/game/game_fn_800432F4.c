typedef struct OSThread OSThread;

typedef struct DataBlock {
    struct { unsigned char data[0x20]; } queue0;
    unsigned char pad20[0xC];
    struct { unsigned char data[0x20]; } queue1;
    unsigned char pad4C[0xC];
    struct { unsigned char data[0x20]; } queue2;
    unsigned char pad78[0x18];
    struct { unsigned char data[0x20]; } queue3;
    unsigned char padB0[0x18];
    unsigned char queue1Storage[0x10];
    unsigned char queue3Storage[0x10];
    unsigned char queue0Storage[0x10];
    struct { unsigned char data[0x20]; } queue4;
    unsigned char thread[0x310];
    unsigned long stack[0x800];
} DataBlock;

extern DataBlock lbl_80304060;

extern int lbl_8064C7C4;
extern int lbl_8064C7C8;
extern int lbl_8064C7CC;
extern int lbl_8064C7D0;
extern void* lbl_8064C7E4[2];
extern void* lbl_8064C7EC[2];
extern int lbl_8064C7F8;

extern void fn_800433FC(void);
extern void OSInitMessageQueue(void*, void*, int);
extern int OSCreateThread(OSThread*, void* (*)(void*), void*, void*,
                         unsigned int, int, unsigned short);
extern int OSResumeThread(OSThread*);

void fn_800432F4(void)
{
    register DataBlock* block = &lbl_80304060;

    lbl_8064C7D0 = 0;
    lbl_8064C7C8 = 0;
    lbl_8064C7CC = -1;
    lbl_8064C7F8 = 0;

    if (lbl_8064C7C4 == 0) {
        OSInitMessageQueue(&block->queue1,
                    block->queue1Storage, 4);
        OSInitMessageQueue(&block->queue3,
                    block->queue3Storage, 4);
        {
            register void* queue;
            /* ASM: addi preserves the retail zero-offset address operation;
             * the C optimizer canonicalizes this expression to mr. */
            asm {
                addi queue, block, 0
            }
            OSInitMessageQueue(queue, block->queue0Storage, 4);
        }
        OSInitMessageQueue(&block->queue2, lbl_8064C7EC, 2);
        OSInitMessageQueue(&block->queue4, lbl_8064C7E4, 2);
        {
            register unsigned char* stackTop;
            register void (*entry)(void);
            register unsigned long entryHigh;
            /* ASM: lis and addi preserve the callback-address split and its
             * ordering around the stack address; C uses a different register
             * and schedules the thread address between these operations. */
            asm {
                lis entryHigh, fn_800433FC@ha
                addi stackTop, block, 0x2428
                addi entry, entryHigh, fn_800433FC@l
            }
            OSCreateThread((OSThread*)block->thread, (void* (*)(void*))entry, 0,
                        stackTop, 0x2000, 0x1D, 1);
        }
        /* ASM: an empty compiler barrier prevents reuse of the thread address
         * across calls; retail recomputes it for the resume operation. */
        asm {
        }
        OSResumeThread((OSThread*)block->thread);
        lbl_8064C7C4 = 1;
    }
}
