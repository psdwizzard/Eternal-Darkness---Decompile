typedef unsigned short u16;
typedef unsigned int u32;

typedef struct State80204A14 {
    u32 field_0;
    u32 field_4;
    u32 field_8;
} State80204A14;

extern char lbl_802FCA10[];
extern void *lbl_8064D878;
extern State80204A14 *lbl_8064D8B0;

extern void *fn_801FEA8C(u32 size, int report, const char *source, int line);
extern void *fn_8017CCD8(void *storage, u32 size, u32 count);
extern State80204A14 *fn_80205210(void);

void fn_80204A14(int initialized, u32 count)
{
    if (initialized == 0) {
        void *storage = fn_801FEA8C(count * 12, 1, lbl_802FCA10, 124);
        lbl_8064D878 = fn_8017CCD8(storage, 12, (u16)count);
    }

    lbl_8064D8B0 = fn_80205210();
    lbl_8064D8B0->field_0 = 0;
    lbl_8064D8B0->field_4 = 0;
    lbl_8064D8B0->field_8 = 0;
}
