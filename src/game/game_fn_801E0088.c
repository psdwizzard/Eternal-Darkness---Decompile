typedef unsigned char u8;
typedef unsigned short u16;

extern int lbl_8064D18C;
extern int lbl_8064C544;
extern u8 lbl_8023B5C0[];
extern void* fn_80201814(int);
extern int fn_80036D5C(void);
extern void fn_80036DA4(void*, unsigned int);
extern int fn_80201B5C(void*);
extern void fn_80201D44(void*, int);
extern void fn_80201D24(void*, int);
extern void fn_802015A4(void*);
extern void fn_801D7E70(int, int);
extern void fn_801FE22C(int);
extern void fn_8020123C(int, int, int, int);
extern void fn_801B05B0(int, int);
extern void fn_801E1920(void*);
extern void fn_801FE934(int, int);
extern int fn_801D3A34(int, int);
extern u8 fn_801CEB2C(int);
extern void fn_8014EAA4();

/* NonMatching: honest-C reconstruction of the complete common teardown path
 * and the first event arms. The remaining large event dispatcher is not yet
 * reconstructed; retail also requires a 0x110 frame and r26-r31/f31 lives. */
void fn_801E0088(void* object)
{
    u8* info = object;
    u8* constants = lbl_8023B5C0;
    void* handle;
    int result;
    int a, b, c, d;
    (void)constants;

    if (*(int*)(info + 8) != lbl_8064D18C || (info[0xff0] & 1)) {
        handle = fn_80201814(*(int*)(info + 0xe0));
        if (handle) {
            fn_80036DA4(handle, fn_80036D5C() | 0x08000000);
            result = fn_80201B5C(handle);
            if (result == 0 || result == 40) {
                fn_80201D44(handle, *(int*)(info + 0x13c));
                fn_80201D24(handle, 1);
                fn_802015A4(handle);
            }
            if (!(info[0xff0] & 0x10) && !(info[0xff0] & 1) &&
                *(void (**)(void*, int))(info + 0x28))
                (*(void (**)(void*, int))(info + 0x28))(info, *(int*)(info + 0x2c));
        }
        if (*(u16*)(info + 0xff4) && (info[0xff0] & 0x10))
            fn_801D7E70(*(int*)(info + 0xc), 1);
        fn_801FE22C(*(int*)(info + 0x44));
        if (info[0xff0] & 0x10) {
            if (fn_80201814(lbl_8064C544))
                fn_8020123C(8, lbl_8064C544, lbl_8064C544, 0);
            lbl_8064C544 = *(int*)(info + 0xe0);
            fn_8020123C(195, *(int*)(info + 0xc), *(int*)(info + 0xc), 0);
        }
        if (*(int*)(info + 0x10) != -1)
            fn_801B05B0(*(int*)(info + 0x10), 10);
        fn_801E1920(info);
        return;
    }

    switch (*(u16*)(info + 0xff4)) {
    case 20:
        fn_801FE934(*(int*)(info + 0x44), 5);
        break;
    case 40:
        d = fn_801D3A34(*(int*)(info + 4), 0x4e);
        c = fn_801D3A34(*(int*)(info + 4), 0x4a);
        b = fn_801D3A34(*(int*)(info + 4), 0x46);
        a = fn_801D3A34(*(int*)(info + 4), 0x35);
        fn_8014EAA4(info + 0x38, 250, fn_801CEB2C(*(int*)(info + 4)), a, b, c, d, 4);
        break;
    }
}
