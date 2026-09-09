typedef unsigned int u32;

typedef struct Record {
    u32 words[13];
} Record;

extern int lbl_8064D75C;

extern void* fn_801EB080(void);
extern void fn_801F44DC(void);
extern void fn_80226EA0(int, int, int, int);
extern void fn_80226FA4(int, int, int, int);
extern void fn_802276AC(void*, int);
extern void fn_802266B0(void);
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
        fn_80226EA0(0, 0, 0x280, 0x1E0);
        fn_80226FA4(0x280, 0x1E0, 1, 0);
        fn_802276AC(context, 0);
        fn_802266B0();
        fn_801F4570(0, 0);
        fn_801F683C(&source);
        copy = source;
        fn_801F03F0(&copy, 0);
        lbl_8064D75C = 1;
    }
}
