typedef unsigned short u16;
typedef unsigned int u32;

extern char lbl_8024A278[];
extern void *lbl_8064CB10;
extern void *fn_801FEA8C(u32 size, int report, const char *source, int line);
extern void *fn_8017CCD8(void *storage, u32 size, u32 count);

void fn_800EA038(u32 count) {
    void *storage = fn_801FEA8C((u16)count * 0x28, 1, lbl_8024A278, 0x475);
    lbl_8064CB10 = fn_8017CCD8(storage, 0x28, count);
}
