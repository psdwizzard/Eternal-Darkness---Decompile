typedef int s32;
typedef unsigned int u32;

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

typedef struct DVDFileInfo DVDFileInfo;
typedef void (*DVDCallback)(s32 result, DVDFileInfo *fileInfo);

struct DVDFileInfo {
    DVDCommandBlock cb;
    u32 startAddr;
    u32 length;
    DVDCallback callback;
};

/* Forward completion of a stream preparation to the file callback. */
void cbForPrepareStreamAsync(s32 result, DVDCommandBlock *block)
{
    DVDFileInfo *fileInfo = (DVDFileInfo *)block;

    if (fileInfo->callback != 0) {
        fileInfo->callback(result, fileInfo);
    }
}
