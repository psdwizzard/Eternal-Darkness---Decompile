extern void fn_801A8C60(int, int, void*, void*);
extern void fn_801E6070(void*);
extern void fn_80144C4C(void*);
extern void fn_801E717C(void);

extern unsigned char lbl_8064D56C;
extern unsigned char lbl_8064C310;
extern unsigned char lbl_80633440[];
extern void* lbl_8064D598;
extern void* lbl_8064D560;

void fn_801E5FE4(void)
{
    unsigned char* end;
    unsigned char* object;

    fn_801A8C60(0xFF, 0x28, &lbl_8064D56C, &lbl_8064C310);
    object = lbl_80633440;
    end = object + 0x3C00;
    while (object < end) {
        fn_801E6070(object);
        object += 0x600;
    }
    if (lbl_8064D598 != 0) {
        fn_801E6070(lbl_8064D598);
    }
    if (lbl_8064D560 != 0) {
        fn_80144C4C(lbl_8064D560);
        fn_801E717C();
    }
}
