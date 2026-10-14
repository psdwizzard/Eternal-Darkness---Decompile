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

extern int lbl_8064C3C8;
extern int fn_80213394(char *path, DVDFileInfo *file);
extern void *fn_8020AD80(int heap, unsigned long size);
extern s32 fn_802137F4(DVDFileInfo *file, void *addr, s32 length,
                      s32 offset, s32 priority);
extern int fn_8021345C(DVDFileInfo *file);
extern void fn_8022C53C(TPLPalette *palette);

void fn_8022C4C0(TPLPalette **palette, const char *path)
{
    DVDFileInfo file;

    fn_80213394((char *)path, &file);
    *palette = fn_8020AD80(lbl_8064C3C8, (file.length + 31) & ~31);
    fn_802137F4(&file, *palette, (file.length + 31) & ~31, 0, 2);
    fn_8021345C(&file);
    fn_8022C53C(*palette);
}
