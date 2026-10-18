typedef struct Header {
    int file;
    short id;
    char name[14];
} Header;

typedef struct FileData {
    unsigned char pad[0x14];
    int offset;
} FileData;

extern Header lbl_805AE780;
extern unsigned char lbl_8024EF08[];
extern char lbl_8064B9E8[7];
extern char lbl_8064B9F0[2];
extern void* lbl_8064CFDC;
extern void sprintf(char*, const char*, ...);
extern void fn_80155BB0(const char*, const char*, ...);
extern void DVDChangeDir(void*);
extern int DVDConvertPathToEntrynum(const char*);
extern int DVDFastOpen(int, void*);
extern int DVDReadPrio(void*, void*, int, int, int);
extern void DVDClose(void*);

void fn_801399CC(short id)
{
    unsigned char handle[60];
    unsigned char* strings = lbl_8024EF08;
    char* name;
    int code = id;

    if (code == 119) {
        code = 85;
    } else if (code == 120) {
        code = 121;
    } else if (code == 122) {
        code = 101;
    }

    if (lbl_805AE780.id != id) {
        lbl_805AE780.id = -1;
        name = lbl_805AE780.name;
        sprintf(name, (char*)strings + 0x84, code);
        DVDChangeDir(lbl_8064B9E8);
        lbl_805AE780.file = DVDConvertPathToEntrynum(name);
        DVDChangeDir(lbl_8064B9F0);
        if (lbl_805AE780.file != -1) {
            if (!DVDFastOpen(lbl_805AE780.file, handle)) {
                fn_80155BB0((char*)strings + 0x94, (char*)strings + 0xAC, name,
                            lbl_805AE780.file);
            } else {
                while (DVDReadPrio(handle, lbl_8064CFDC, 1024, 0, 2) == -1) {
                }
                ((FileData*)lbl_8064CFDC)->offset += (int)lbl_8064CFDC;
                lbl_805AE780.id = id;
                DVDClose(handle);
            }
        }
    }
}
