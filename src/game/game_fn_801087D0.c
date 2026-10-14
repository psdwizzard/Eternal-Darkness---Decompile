typedef struct StreamBlock {
    unsigned char* data;
    int size;
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

typedef struct StreamStrings {
    char file[0xC];
    char openFailed[0x14];
    char noBlock[0x10];
    char badMessage[0x18];
} StreamStrings;

typedef struct DVDFileInfo {
    unsigned char commandBlock[0x30];
    unsigned long startAddr;
    unsigned long length;
    void* callback;
} DVDFileInfo;

typedef struct OSMessageQueue OSMessageQueue;

extern StreamState lbl_8032D648;
extern StreamStrings lbl_8023A220;
extern int lbl_8064B878;
extern unsigned long lbl_8064CC74;
extern DVDFileInfo* lbl_8064CC78;
extern int lbl_8064CC7C;
extern unsigned char* lbl_8064CC84;

extern int fn_80213394(const char*, DVDFileInfo*);
extern int fn_8021345C(DVDFileInfo*);
extern int fn_80213704(DVDFileInfo*, void*, int, int, void (*)(int, DVDFileInfo*), int);
extern int fn_80215C34(DVDFileInfo*);
extern int fn_8020D318(OSMessageQueue*, void**, int);
extern int fn_8020D250(OSMessageQueue*, void*, int);
extern void fn_8020D7E0(void*);
extern void fn_8020D8BC(void*);
extern void fn_8020C5D0(const char*, int, const char*, ...);
extern void fn_80108BD4(int, DVDFileInfo*);

#define BLOCK_SIZE 0x80000

static inline StreamBlock* findBlock(register StreamState* stream, int state)
{
    register StreamBlock* block;
    int i;

    /* ASM: addi block, stream, 0x13E8. The blocks are a separate pooled .bss
       object in retail; C folds the offset into each lwz instead. */
    asm { addi block, stream, 0x13E8 }
    for (i = 3; i != 0; i--, block++) {
        if (block->state == state) {
            return block;
        }
    }
    return 0;
}

static inline void lockStream(register StreamState* stream)
{
    register void* mutex;

    /* ASM: addi mutex, stream, 0. Retail addresses the pooled mutex object
       with addi +0; C only emits mr. */
    asm { addi mutex, stream, 0 }
    fn_8020D7E0(mutex);
}

static inline void unlockStream(register StreamState* stream)
{
    register void* mutex;

    /* ASM: addi mutex, stream, 0. Same pooled-base addi +0 as lockStream. */
    asm { addi mutex, stream, 0 }
    fn_8020D8BC(mutex);
}

/* ASM (both below): li value, N; addi mutex, stream, 0. Pooled-base addi +0
   for the mutex; retail loads the state constant before it, which C
   schedules after the asm barrier. */
static inline void lockStreamRestart(register StreamState* stream)
{
    register void* mutex;
    register int value;

    /* ASM: li value, 1; addi mutex, stream, 0 (see above). */
    asm {
        li value, 1
        addi mutex, stream, 0
    }
    lbl_8064B878 = value;
    fn_8020D7E0(mutex);
}

static inline void lockStreamCancel(register StreamState* stream)
{
    register void* mutex;
    register int value;

    /* ASM: li value, 2; addi mutex, stream, 0 (see above). */
    asm {
        li value, 2
        addi mutex, stream, 0
    }
    lbl_8064B878 = value;
    fn_8020D7E0(mutex);
}

static inline void streamPanic(register StreamStrings* strings, int line, const char* msg)
{
    register const char* file;

    /* ASM: addi file, strings, 0. The file name string is pooled with the
       other messages and addressed with addi +0; C only emits mr. */
    asm { addi file, strings, 0 }
    fn_8020C5D0(file, line, msg);
}

static inline void initBlocks(register StreamState* stream, unsigned char* buffer)
{
    register StreamBlock* block;
    register void* mutex;
    int offset;
    int i;

    /* ASM: addi block, stream, 0x13E8. Retail keeps a pointer to the pooled
       block array; C folds the offset into each store instead. */
    asm { addi block, stream, 0x13E8 }
    offset = 0;
    /* ASM: addi mutex, stream, 0. Pooled-base addi +0, after the offset reset. */
    asm { addi mutex, stream, 0 }
    for (i = 0; i < 3; i++, block++) {
        block->data = buffer + offset;
        block->size = BLOCK_SIZE;
        block->state = 0;
        offset += BLOCK_SIZE;
    }
    fn_8020D8BC(mutex);
}

void* fn_801087D0(const char* path)
{
    register StreamState* stream;
    StreamStrings* strings;
    int remaining;
    int aligned;
    int offset;
    int chunk;
    int flags;
    StreamBlock* block;
    int length;
    void* message;
    DVDFileInfo fileInfo;

    strings = &lbl_8023A220;
    stream = &lbl_8032D648;
    if (fn_80213394(path, &fileInfo) == 0) {
        streamPanic(strings, 0xCC, strings->openFailed);
    }
    lbl_8064CC78 = &fileInfo;
    lbl_8064CC7C = fileInfo.length;
    lbl_8064CC74 = 0;

restart:
    {
        register void* mutex;
        register int value;

        /* ASM: li value, 0; addi mutex, stream, 0. Pooled-base addi +0 with
           the state constant loaded first (C sinks it past the barrier); the
           flags reset sits between the state store and the lock call. */
        asm {
            li value, 0
            addi mutex, stream, 0
        }
        lbl_8064B878 = value;
        flags = 0;
        fn_8020D7E0(mutex);
    }
    initBlocks(stream, lbl_8064CC84);

rewind:
    remaining = lbl_8064CC7C;
    aligned = (remaining + 0x1F) & ~0x1F;
    fn_8020D250((OSMessageQueue*)stream->commandQueue, (void*)0, 0);
    offset = 0;

    for (;;) {
        fn_8020D318((OSMessageQueue*)stream->commandQueue, &message, 1);
        switch ((unsigned long)message) {
        case 3:
            break;
        case 0:
            lockStream(stream);
            block = findBlock(stream, 0);
            if (block != 0) {
                chunk = length = (aligned < BLOCK_SIZE) ? aligned : BLOCK_SIZE;
                while (fn_80213704(&fileInfo, block->data, length, offset, fn_80108BD4, 2) == 0) {
                }
                block->start = offset;
                block->state = 1;
            } else {
                fn_8020D250((OSMessageQueue*)stream->commandQueue, (void*)2, 0);
            }
            unlockStream(stream);
            break;
        case 1:
            lockStream(stream);
            block = findBlock(stream, 1);
            if (block == 0) {
                streamPanic(strings, 0x108, strings->noBlock);
            }
            offset += chunk;
            aligned -= chunk;
            block->end = block->start + chunk;
            remaining -= chunk;
            block->state = 2;
            unlockStream(stream);
            if (flags & 1) {
                goto done;
            }
            if (flags & 2) {
                goto restart;
            }
            if (remaining <= 0) {
                goto rewind;
            }
            fn_8020D250((OSMessageQueue*)stream->commandQueue, (void*)0, 0);
            break;
        case 2:
            fn_8020D318((OSMessageQueue*)stream->commandQueue, &message, 1);
            if ((int)message == 3) {
                message = 0;
            }
            fn_8020D250((OSMessageQueue*)stream->commandQueue, message, 0);
            break;
        case 4:
            lockStreamRestart(stream);
            block = findBlock(stream, 1);
            unlockStream(stream);
            if (block == 0) {
                goto restart;
            }
            flags |= 2;
            break;
        case 5:
            lockStreamCancel(stream);
            block = findBlock(stream, 1);
            unlockStream(stream);
            if (block == 0) {
                goto done;
            }
            if (lbl_8064CC74 != 0) {
                goto done;
            }
            if (fn_80215C34(lbl_8064CC78) == -1) {
                goto done;
            }
            flags |= 1;
            break;
        case 6:
            lbl_8064CC74 = 1;
            break;
        default:
            streamPanic(strings, 0x152, strings->badMessage);
            break;
        }
    }

done:
    lbl_8064CC78 = 0;
    fn_8021345C(&fileInfo);
    lbl_8064B878 = 3;
    return 0;
}
