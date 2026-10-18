typedef unsigned int u32;

typedef struct Record {
    u32 words[13];
} Record;

extern int lbl_8064D75C;

extern void* fn_801EB080(void);
extern void fn_801F44DC(void);
extern void GXSetTexCopySrc(int, int, int, int);
extern void GXSetTexCopyDst(int, int, int, int);
extern void GXCopyTex(void*, int);
extern void GXPixModeSync(void);
extern void fn_801F4570(int, int);
extern void fn_801F683C(Record*);
extern void fn_801F03F0(Record*, int);

void fn_801F47F8(void)
{
    void* context = fn_801EB080();

    if (lbl_8064D75C == 0) {
        Record copy;
        Record source;

        fn_801F44DC();
        GXSetTexCopySrc(0, 0, 0x280, 0x1E0);
        GXSetTexCopyDst(0x280, 0x1E0, 1, 0);
        GXCopyTex(context, 0);
        GXPixModeSync();
        fn_801F4570(0, 0);
        fn_801F683C(&source);
        copy = source;
        fn_801F03F0(&copy, 0);
        lbl_8064D75C = 1;
    }
}
