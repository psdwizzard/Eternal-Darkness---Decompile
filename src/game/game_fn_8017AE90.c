extern unsigned char lbl_8064A580[];
extern int lbl_8064D208;

typedef unsigned long long u64;

extern void fn_8017B7C8(void);
extern void fn_8017B9F8(void);
extern void fn_8017B7EC(int);
extern void fn_8017B80C(int);
extern void fn_8017B864(int);
extern void fn_8017B8BC(int);
extern void fn_8017B914(int);
extern void fn_8017B96C(int);
extern void fn_8017BA54(u64);
extern void fn_8017B344(int, int);
extern void fn_8017BAF4(void);

void fn_8017AE90(void)
{
    int i;

    fn_8017B7C8();
    fn_8017B9F8();
    fn_8017B7EC(0);
    fn_8017B80C(0);
    fn_8017B864(0);
    fn_8017B8BC(0);
    fn_8017B914(0);
    fn_8017B96C(0);
    fn_8017BA54(0);

    lbl_8064D208 = 0;
    *(int*)(lbl_8064A580 + 0x44) = 0;
    for (i = 0; i < 2; i++) {
        fn_8017B344(i, 0);
        lbl_8064A580[0x40 + i] = 0;
    }
    fn_8017BAF4();
}
