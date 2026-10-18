typedef unsigned char u8;
typedef unsigned int u32;

typedef struct FileInfo {
    u8 pad0[0x34];
    u32 size;
} FileInfo;

extern int DVDOpen(char*, FileInfo*);
extern int DVDReadPrio(FileInfo*, void*, u32, int, int);
extern void DVDClose(FileInfo*);

u32 fn_8015E86C(char* path, void* destination)
{
    u32 size = 0;
    FileInfo info;

    if (DVDOpen(path, &info)) {
        size = (info.size + 0x1F) & ~0x1F;
        while (DVDReadPrio(&info, destination, size, 0, 2) == -1) {}
        DVDClose(&info);
    }
    return size;
}
