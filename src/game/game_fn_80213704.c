/* DVDReadAsyncPrio (Dolphin SDK dvdfs.c). */
typedef int s32;
typedef unsigned int u32;
typedef int BOOL;

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

extern void fn_8020C5D0(const char *file, int line, const char *msg, ...);
extern BOOL fn_802154EC(DVDCommandBlock *block, void *addr, s32 length,
                        s32 offset, DVDCBCallback callback, s32 prio);
extern void fn_802137C4(s32 result, DVDCommandBlock *block);
extern const char lbl_8064C400[8]; /* "dvdfs.c" */
extern char lbl_802FE250[];

BOOL fn_80213704(DVDFileInfo *fileInfo, void *addr, s32 length, s32 offset,
                 DVDCallback callback, s32 prio)
{
    if (!((0 <= offset) && (offset < fileInfo->length))) {
        fn_8020C5D0(lbl_8064C400, 0x2E3, lbl_802FE250);
    }
    if (!((0 <= offset + length) && (offset + length < fileInfo->length + 32))) {
        fn_8020C5D0(lbl_8064C400, 0x2E9, lbl_802FE250);
    }

    fileInfo->callback = callback;
    fn_802154EC(&fileInfo->cb, addr, length, (s32)(fileInfo->startAddr + offset),
                fn_802137C4, prio);
    return 1;
}
