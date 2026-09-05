extern unsigned short lbl_8064CCAC;
extern unsigned char lbl_80332140[];

extern void *fn_80201B9C();
extern void* fn_80204844(void*, int);
extern int fn_8006D444(void);
extern void fn_8010BFF0(void);
extern void fn_8010AD7C(void);
extern int fn_80201B54();
extern unsigned long long fn_8020123C();
extern void fn_8014C23C(int, int, int);
extern void fn_80046398(int, int, int, int);

void fn_8010F2A4(void)
{
    void* controller;
    unsigned int active;
    int id;

    lbl_8064CCAC++;
    if (lbl_8064CCAC >= 300) {
        controller = fn_80204844(fn_80201B9C(), 32);
        active = fn_8006D444();
        lbl_8064CCAC = 0;
        *(unsigned int*)(lbl_80332140 + 16) &= ~2u;
        fn_8010BFF0();
        fn_8010AD7C();
        if (active != 0) {
            id = fn_80201B54(controller);
            fn_8020123C(81, 0, id, 0);
            fn_8014C23C(20, 0, 0);
            fn_80046398(60, 0xFFFF, 100, 100);
        }
    }

    if (lbl_8064CCAC == 1) {
        controller = fn_80204844(fn_80201B9C(), 32);
        if (controller != 0 &&
            (unsigned int)(fn_8020123C(84, 0, fn_80201B54(controller), 0) & 0xFFFFFFFF) == 0) {
            fn_8010BFF0();
            fn_8010AD7C();
            lbl_8064CCAC = 0;
            *(unsigned int*)(lbl_80332140 + 16) &= ~2u;
        }
    }
}
