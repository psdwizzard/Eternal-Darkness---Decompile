/* Callback adapter for DVDReadAsyncPrio (Dolphin SDK dvdfs.c). */
typedef int s32;
typedef unsigned int u32;

typedef struct DVDCommandBlock DVDCommandBlock;
typedef struct DVDFileInfo DVDFileInfo;
typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock *block);
typedef void (*DVDCallback)(s32 result, DVDFileInfo *fileInfo);

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

struct DVDFileInfo {
    DVDCommandBlock cb;
    u32 startAddr;
    u32 length;
    DVDCallback callback;
};

void cbForReadAsync(s32 result, DVDCommandBlock *block)
{
    DVDFileInfo *fileInfo = (DVDFileInfo *)block;

    if (fileInfo->callback != 0) {
        fileInfo->callback(result, fileInfo);
    }
}
