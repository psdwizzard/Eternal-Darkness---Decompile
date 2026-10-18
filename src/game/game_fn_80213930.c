/* DVDPrepareStreamAsync (0x80213930, 236 bytes): DVDPrepareFileAsync (SDK dvdfs.c) */

typedef int s32;
typedef unsigned int u32;
typedef int BOOL;

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

extern void OSPanic(const char *, int, const char *, ...); /* OSPanic */
extern BOOL DVDPrepareStreamAbsAsync(DVDCommandBlock *block, u32 length, u32 offset,
                        DVDCBCallback callback); /* DVDPrepareStreamAbsAsync */
extern void cbForPrepareStreamAsync(s32 result, DVDCommandBlock *block); /* cbForPrepareFileAsync */

extern const char lbl_8064C400[8]; /* "dvdfs.c" */
extern char lbl_802FE150[];

BOOL DVDPrepareStreamAsync(DVDFileInfo *fileInfo, u32 length, u32 offset, DVDCallback callback) {
    char *msgs = lbl_802FE150;
    u32 start;

    start = fileInfo->startAddr + offset;
    if (start & 0x7FFF) {
        OSPanic(lbl_8064C400, 0x4A2, msgs + 0x1C8, fileInfo->startAddr, offset);
    }

    if (length == 0) {
        length = fileInfo->length - offset;
    }

    if (length & 0x7FFF) {
        OSPanic(lbl_8064C400, 0x4AC, msgs + 0x230, length);
    }

    if (!(offset < fileInfo->length && offset + length <= fileInfo->length)) {
        OSPanic(lbl_8064C400, 0x4B4, msgs + 0x288, offset, length);
    }

    fileInfo->callback = callback;
    return DVDPrepareStreamAbsAsync(&fileInfo->cb, length, fileInfo->startAddr + offset, cbForPrepareStreamAsync);
}
