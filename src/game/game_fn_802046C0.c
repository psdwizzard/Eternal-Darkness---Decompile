typedef unsigned short u16;
typedef unsigned int u32;

extern char lbl_802FC9A8[];
extern void *lbl_8064D870;
extern void *lbl_8064D874;

extern void *fn_801FEA8C(u32 size, int report, const char *source, int line);
extern void *fn_8017CCD8(void *storage, u32 size, u32 count);

void fn_802046C0(int type, int count)
{
    void *storage;

    switch (type) {
    case 92:
        storage = fn_801FEA8C((u16)count * 0x38, 1, lbl_802FC9A8, 0x2DF);
        lbl_8064D874 = fn_8017CCD8(storage, 0x38, count);
        break;
    case 93:
        storage = fn_801FEA8C((u16)count * 0x40, 1, lbl_802FC9A8, 0x2E7);
        lbl_8064D870 = fn_8017CCD8(storage, 0x40, count);
        break;
    }
}
