typedef struct FileHandle {
    char pad_00[0x34];
    unsigned int length;
} FileHandle;

extern char lbl_8064B540;
extern char lbl_8064B544;
extern char lbl_80244680[];
extern char lbl_802446A0[];

extern void DVDChangeDir(void *);
extern int DVDOpen(const char *, FileHandle *);
extern int DVDReadPrio(FileHandle *, void *, unsigned int, unsigned int, int);
extern void DVDClose(FileHandle *);

int fn_800723A8(unsigned int index, void *output)
{
    FileHandle file;
    int result;
    unsigned int count;
    unsigned int offset;

    DVDChangeDir(&lbl_8064B540);
    result = DVDOpen(lbl_802446A0, &file);
    DVDChangeDir(&lbl_8064B544);
    if (result != 0) {
        count = (file.length - 0x20) / 0xE0;
        offset = index * 0xE0 + 0x20;
        while (DVDReadPrio(&file, lbl_80244680, 0x20, 0, 2) < 0) {
        }
        if (index < count) {
            int position = offset;
            while (DVDReadPrio(&file, output, 0xE0, position, 2) < 0) {
            }
            result = 1;
            DVDClose(&file);
        } else {
            result = 0;
        }
    }
    return result;
}
