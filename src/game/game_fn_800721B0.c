typedef struct Entry {
    int field_00;
    int id;
    char pad_08[0xD8];
} Entry;

typedef struct FileHandle {
    char pad_00[0x34];
    unsigned int length;
} FileHandle;

extern Entry lbl_80313120;
extern char lbl_80244680[0x20];
extern char lbl_802446A0[];
extern char lbl_8064B540;
extern char lbl_8064B544;

extern void *memset(void *, int, unsigned long);
extern int fn_801391AC(void);
extern int fn_80042808(void);
extern void fn_8015E9EC(unsigned int, void *, unsigned int);
extern void DVDChangeDir(void *);
extern int DVDOpen(const char *, FileHandle *);
extern int DVDReadPrio(FileHandle *, void *, unsigned int, unsigned int, int);
extern void DVDClose(FileHandle *);

void fn_800721B0(void)
{
    FileHandle file;
    int i;
    int result;
    int length;

    memset(&lbl_80313120, 0, 0x9920);
    for (i = 0; i != 175; i++) {
        (&lbl_80313120)[(unsigned int)i].id = -1;
    }
    memset(lbl_80244680, -1, sizeof(lbl_80244680));
    if (fn_801391AC() != 0 && fn_80042808() != -1) {
        fn_8015E9EC(0xFB63D0, lbl_80244680, sizeof(lbl_80244680));
        fn_8015E9EC(0xFB63F0, &lbl_80313120, 0x9920);
    } else {
        DVDChangeDir(&lbl_8064B540);
        result = DVDOpen(lbl_802446A0, &file);
        DVDChangeDir(&lbl_8064B544);
        if (result != 0) {
            length = file.length;
            while (DVDReadPrio(&file, lbl_80244680, 0x20, 0, 2) < 0) {
            }
            length -= 0x20;
            while (DVDReadPrio(&file, &lbl_80313120, length, 0x20, 2) < 0) {
            }
            DVDClose(&file);
        }
    }
}
