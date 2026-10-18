typedef struct DVDFileInfo {
    unsigned char data[0x34];
    int length;
} DVDFileInfo;

extern unsigned char lbl_805FA1F0[];
extern unsigned char lbl_8064D130;
extern void fn_8015CDF0(void);
extern void fn_8015D6A0(void);
extern void OSInitMessageQueue(void*, void*, int);
extern int OSReceiveMessage(void*, void*, int);
extern int DVDOpen(void*, DVDFileInfo*);
extern void DVDClose(DVDFileInfo*);
extern int DVDReadAsyncPrio(DVDFileInfo*, void*, int, int, void*, int);

int fn_8015D6D0(register void* path, register unsigned char* buffer,
                register int size)
{
    DVDFileInfo info;
    int message;
    register int offset;
    register int chunk;
    register int result;
    int length;

    result = 0;
    offset = 0;
    OSInitMessageQueue(lbl_805FA1F0, &lbl_8064D130, 2);
    if (DVDOpen(path, &info)) {
        length = (info.length + 31) & ~31;
        if (length > size) {
            length = size;
        }
        while (length != 0) {
            chunk = 0x1000;
            if (length <= 0x1000) {
                chunk = length;
            }
            while (!DVDReadAsyncPrio(&info, buffer, chunk, offset,
                                fn_8015D6A0, 2)) {
            }
            OSReceiveMessage(lbl_805FA1F0, &message, 1);
            fn_8015CDF0();
            offset += chunk;
            length -= chunk;
            buffer += chunk;
        }
        result = (info.length + 31) & ~31;
        DVDClose(&info);
    }
    return result;
}
