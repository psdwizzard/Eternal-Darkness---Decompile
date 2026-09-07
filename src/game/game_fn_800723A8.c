typedef struct FileHandle {
    char pad_00[0x34];
    unsigned int length;
} FileHandle;

extern char lbl_8064B540;
extern char lbl_8064B544;
extern char lbl_80244680[];
extern char lbl_802446A0[];

extern void fn_802136A4(void *);
extern int fn_80213394(const char *, FileHandle *);
extern int fn_802137F4(FileHandle *, void *, unsigned int, unsigned int, int);
extern void fn_8021345C(FileHandle *);

int fn_800723A8(unsigned int index, void *output)
{
    FileHandle file;
    int result;
    unsigned int count;
    unsigned int offset;

    fn_802136A4(&lbl_8064B540);
    result = fn_80213394(lbl_802446A0, &file);
    fn_802136A4(&lbl_8064B544);
    if (result != 0) {
        count = (file.length - 0x20) / 0xE0;
        offset = index * 0xE0 + 0x20;
        while (fn_802137F4(&file, lbl_80244680, 0x20, 0, 2) < 0) {
        }
        if (index < count) {
            int position = offset;
            while (fn_802137F4(&file, output, 0xE0, position, 2) < 0) {
            }
            result = 1;
            fn_8021345C(&file);
        } else {
            result = 0;
        }
    }
    return result;
}
