typedef unsigned int u32;

extern char lbl_8023E868[];
extern char lbl_8023E884[];
extern char lbl_8023E8A0[];
extern char lbl_8023E8BC[];
extern char lbl_8023E8D8[];
extern char lbl_8023E8F4[];
extern char lbl_8023E910[];
extern char lbl_8023E92C[];
extern char lbl_8023E948[];
extern char lbl_8023E964[];
extern char lbl_8023E980[];
extern char lbl_8023E99C[];
extern char lbl_80251650[];
extern char lbl_80607CD0[];

extern u32 lbl_8064D2A8;
extern u32 lbl_8064D2AC;
extern u32 lbl_8064D2B0;
extern void* lbl_8064D2B4;
extern void* lbl_8064D2B8;
extern void* lbl_8064D2BC;
extern int lbl_8064D2C8;

extern void fn_801AA398(void);
extern void fn_801AA550(int);
extern void fn_801AA618(void);
extern u32 fn_8015D630(char*);
extern void fn_8015E86C(char*, void*, u32);
extern void* fn_801FEA8C(u32, int, char*, int);
extern void fn_801C3E2C(void);
extern void fn_801C3CBC(void*, int, int, void*, void*);
extern void fn_801CD504(void (*)(void));
extern int fn_80213394(char*, char*);
extern void fn_8021345C(char*);
extern void fn_8021B88C(void);
extern void* memset(void*, int, u32);

void fn_801AA6D0(int mode, int arg, int allocate, int value)
{
    u32 size1;
    u32 alternate_size;
    u32 size2;
    u32 size3;
    char* src1;
    char* src2;
    char* src3;
    char* resource;

    if (allocate == 0) {
        fn_801CD504(fn_801AA398);

        size1 = fn_8015D630(lbl_8023E868);
        size2 = fn_8015D630(lbl_8023E8D8);
        size3 = fn_8015D630(lbl_8023E948);
        if ((size1 > size2 ? size1 : size2) > size3) {
            size3 = size1 > size2 ? size1 : size2;
        }
        lbl_8064D2A8 = (size3 + 31) & ~31;
        lbl_8064D2B4 = fn_801FEA8C(lbl_8064D2A8, 1, lbl_80251650, 0x113);

        size2 = fn_8015D630(lbl_8023E8A0);
        alternate_size = fn_8015D630(lbl_8023E910);
        size3 = fn_8015D630(lbl_8023E980);
        size2 = (size2 > alternate_size ? size2 : alternate_size) > size3
                    ? (size2 > alternate_size ? size2 : alternate_size)
                    : size3;
        lbl_8064D2AC = (size2 + 31) & ~31;
        lbl_8064D2B8 = fn_801FEA8C(lbl_8064D2AC, 1, lbl_80251650, 0x11C);

        size2 = fn_8015D630(lbl_8023E8BC);
        alternate_size = fn_8015D630(lbl_8023E92C);
        size3 = fn_8015D630(lbl_8023E99C);
        size2 = (size2 > alternate_size ? size2 : alternate_size) > size3
                    ? (size2 > alternate_size ? size2 : alternate_size)
                    : size3;
        lbl_8064D2B0 = (size2 + 31) & ~31;
        lbl_8064D2BC = fn_801FEA8C(lbl_8064D2B0, 1, lbl_80251650, 0x125);
    } else {
        fn_801C3E2C();
    }

    memset(lbl_8064D2B4, 0xE0, lbl_8064D2A8);
    memset(lbl_8064D2B8, 0xE0, lbl_8064D2AC);
    memset(lbl_8064D2BC, 0xE0, lbl_8064D2B0);

    if (mode == 1) {
        src1 = lbl_8023E868;
        src2 = lbl_8023E8A0;
        src3 = lbl_8023E8BC;
        resource = lbl_8023E884;
    } else if (mode == 2) {
        src1 = lbl_8023E8D8;
        src2 = lbl_8023E910;
        src3 = lbl_8023E92C;
        resource = lbl_8023E8F4;
    } else {
        src1 = lbl_8023E948;
        src2 = lbl_8023E980;
        src3 = lbl_8023E99C;
        resource = lbl_8023E964;
    }

    fn_8015E86C(src1, lbl_8064D2B4, lbl_8064D2A8);
    fn_8015E86C(src2, lbl_8064D2B8, lbl_8064D2AC);
    fn_8015E86C(src3, lbl_8064D2BC, lbl_8064D2B0);

    if (fn_80213394(resource, lbl_80607CD0) != 0) {
        fn_8021B88C();
        lbl_8064D2C8 = arg;
        fn_801AA550(value);
        fn_801C3CBC(lbl_8064D2B8, 0, arg, lbl_8064D2BC, lbl_8064D2B4);
        fn_801AA618();
        fn_8021345C(lbl_80607CD0);
    }
}
