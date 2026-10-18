/* DVDReadPrio (0x802137F4, 280 bytes): DVDReadPrio (SDK dvdfs.c) */

typedef int s32;
typedef unsigned int u32;
typedef int BOOL;

typedef struct OSThreadQueue {
    void *head;
    void *tail;
} OSThreadQueue;

typedef struct DVDCommandBlock DVDCommandBlock;
typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock *block);

struct DVDCommandBlock {
    DVDCommandBlock *next;
    DVDCommandBlock *prev;
    u32 command;
    s32 state;
    u32 offset;
    u32 length;
    void *addr;
    u32 currTransferSize;
    u32 transferredSize;
    void *id;
    DVDCBCallback callback;
    void *userData;
};

typedef struct DVDFileInfo {
    DVDCommandBlock cb;
    u32 startAddr;
    u32 length;
    void *callback;
} DVDFileInfo;

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern void OSPanic(const char *, int, const char *, ...); /* OSPanic */
extern void OSSleepThread(OSThreadQueue *queue); /* OSSleepThread */
extern BOOL DVDReadAbsAsyncPrio(DVDCommandBlock *block, void *addr, s32 length, s32 offset,
                        DVDCBCallback callback, s32 prio); /* DVDReadAbsAsyncPrio */
extern void cbForReadSync(s32 result, DVDCommandBlock *block); /* cbForReadSync */

extern OSThreadQueue __DVDThreadQueue;
extern const char lbl_8064C400[8]; /* "dvdfs.c" */
extern char lbl_802FE284[];

s32 DVDReadPrio(DVDFileInfo *fileInfo, void *addr, s32 length, s32 offset, s32 prio) {
    BOOL result;
    DVDCommandBlock *block;
    s32 state;
    BOOL enabled;
    s32 retVal;

    if (!((0 <= offset) && (offset < fileInfo->length))) {
        OSPanic(lbl_8064C400, 0x329, lbl_802FE284);
    }
    if (!((0 <= offset + length) && (offset + length < fileInfo->length + 32))) {
        OSPanic(lbl_8064C400, 0x32F, lbl_802FE284);
    }

    block = &fileInfo->cb;
    result = DVDReadAbsAsyncPrio(block, addr, length, (s32)(fileInfo->startAddr + offset),
                         cbForReadSync, prio);

    if (result == 0) {
        return -1;
    }

    enabled = OSDisableInterrupts();

    while (1) {
        state = ((volatile DVDCommandBlock *)block)->state;

        if (state == 0) {
            retVal = (s32)block->transferredSize;
            break;
        } else if (state == -1) {
            retVal = -1;
            break;
        } else if (state == 10) {
            retVal = -3;
            break;
        }

        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return retVal;
}
