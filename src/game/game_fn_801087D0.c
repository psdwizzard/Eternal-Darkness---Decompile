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

typedef struct DVDFileInfo {
    unsigned char commandBlock[0x30];
    unsigned long startAddr;
    unsigned long length;
    void* callback;
} DVDFileInfo;

typedef struct OSMessageQueue OSMessageQueue;

extern StreamState lbl_8032D648;
extern const volatile char lbl_8023A220[72];
extern int lbl_8064B878;
extern unsigned int lbl_8064CC74;
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

static inline StreamBlock* findBlock(StreamState* stream, int state)
{
    StreamBlock* block = stream->blocks;
    int i;

    for (i = 0; i < 3; i++, block++) {
        if (block->state == state) {
            return block;
        }
    }
    return 0;
}

void* fn_801087D0(const char* path)
{
    StreamState* stream;
    const char* strings;
    int remaining;
    int aligned;
    int offset;
    int chunk;
    int flags;
    StreamBlock* block;
    int length;
    int size;
    unsigned char* buffer;
    int i;
    void* message;
    DVDFileInfo fileInfo;

    strings = (const char*)lbl_8023A220;
    stream = &lbl_8032D648;
    if (fn_80213394(path, &fileInfo) == 0) {
        fn_8020C5D0(strings, 0xCC, strings + 0xC);
    }
    lbl_8064CC78 = &fileInfo;
    lbl_8064CC7C = fileInfo.length;
    lbl_8064CC74 = 0;

restart:
    lbl_8064B878 = 0;
    flags = 0;
    fn_8020D7E0(stream->mutex);
    buffer = lbl_8064CC84;
    block = stream->blocks;
    for (i = 0, size = 0; i < 3; i++, size += BLOCK_SIZE, block++) {
        block->data = buffer + size;
        block->size = BLOCK_SIZE;
        block->state = 0;
    }
    fn_8020D8BC(stream->mutex);

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
            fn_8020D7E0(stream->mutex);
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
            fn_8020D8BC(stream->mutex);
            break;
        case 1:
            fn_8020D7E0(stream->mutex);
            block = findBlock(stream, 1);
            if (block == 0) {
                fn_8020C5D0(strings, 0x108, strings + 0x20);
            }
            offset += chunk;
            aligned -= chunk;
            block->end = block->start + chunk;
            remaining -= chunk;
            block->state = 2;
            fn_8020D8BC(stream->mutex);
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
            lbl_8064B878 = 1;
            fn_8020D7E0(stream->mutex);
            block = findBlock(stream, 1);
            fn_8020D8BC(stream->mutex);
            if (block == 0) {
                goto restart;
            }
            flags |= 2;
            break;
        case 5:
            lbl_8064B878 = 2;
            fn_8020D7E0(stream->mutex);
            block = findBlock(stream, 1);
            fn_8020D8BC(stream->mutex);
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
            fn_8020C5D0(strings, 0x152, strings + 0x30);
            break;
        }
    }

done:
    lbl_8064CC78 = 0;
    fn_8021345C(&fileInfo);
    lbl_8064B878 = 3;
    return 0;
}
