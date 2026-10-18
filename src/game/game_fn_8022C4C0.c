/* Load a TPL palette from DVD and resolve its internal pointers. */
typedef unsigned int u32;
typedef int s32;
typedef struct TPLPalette TPLPalette;
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

extern int __OSCurrHeap;
extern int DVDOpen(char *path, DVDFileInfo *file);
extern void *OSAllocFromHeap(int heap, unsigned long size);
extern s32 DVDReadPrio(DVDFileInfo *file, void *addr, s32 length,
                      s32 offset, s32 priority);
extern int DVDClose(DVDFileInfo *file);
extern void UnpackTexPalette(TPLPalette *palette);

void LoadTexPalette(TPLPalette **palette, const char *path)
{
    DVDFileInfo file;

    DVDOpen((char *)path, &file);
    *palette = OSAllocFromHeap(__OSCurrHeap, (file.length + 31) & ~31);
    DVDReadPrio(&file, *palette, (file.length + 31) & ~31, 0, 2);
    DVDClose(&file);
    UnpackTexPalette(*palette);
}
