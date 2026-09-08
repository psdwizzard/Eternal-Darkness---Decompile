typedef unsigned long size_t;

typedef struct DisplayState {
    void* field_0;
    void* field_4;
} DisplayState;

extern int lbl_8064B2BC;
extern int lbl_8064D6E4;
extern void* lbl_8064D718;
extern DisplayState lbl_8064D71C;
extern int lbl_8064D734;
extern int lbl_8064D738;

extern void* memcpy(void*, const void*, size_t);
extern void DCFlushRange(void*, unsigned long);
extern void fn_801EFE84(void*);
extern void fn_80217324(void);
extern void fn_80217F88(void);
extern void fn_802180A4(void*);

void fn_801EFEC4(int swap_buffers)
{
    if (swap_buffers == 0) {
        if (lbl_8064D718 == lbl_8064D71C.field_0) {
            memcpy(lbl_8064D71C.field_4, lbl_8064D71C.field_0, 0x96000);
            DCFlushRange(lbl_8064D71C.field_4, 0x96000);
        } else {
            memcpy(lbl_8064D71C.field_0, lbl_8064D71C.field_4, 0x96000);
            DCFlushRange(lbl_8064D71C.field_0, 0x96000);
        }
    }

    fn_802180A4(lbl_8064D718);
    if (lbl_8064B2BC >= 0) {
        lbl_8064B2BC--;
    }
    if (lbl_8064B2BC == 0) {
        fn_801EFE84(0);
    }
    fn_80217F88();
    fn_80217324();
    lbl_8064D734 = lbl_8064D6E4;
    lbl_8064D6E4++;
    lbl_8064D6E4 &= 1;
    lbl_8064D738 ^= 1;

    if (swap_buffers != 0) {
        if (lbl_8064D718 == lbl_8064D71C.field_4) {
            lbl_8064D718 = lbl_8064D71C.field_0;
        } else {
            lbl_8064D718 = lbl_8064D71C.field_4;
        }
    }
}
