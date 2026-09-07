typedef unsigned int u32;

extern u32 lbl_8064D584;
extern u32 lbl_8064D580;
extern u32 lbl_8064D594;
extern u32 lbl_8064C320;
extern void* lbl_806333C8[];
extern void* lbl_806333F0[];
extern char lbl_802645F8[];

extern void fn_801ED3F4(void*);
extern void fn_801A852C(u32*, u32, void*, u32);
extern void fn_801E7DCC(char*, ...);

void fn_801E39A8(u32 index)
{
    if (index < lbl_8064D584) {
        u32 color;

        lbl_8064D580 = index;
        fn_801ED3F4(lbl_806333C8[index]);
        color = lbl_8064D594;
        fn_801A852C(&color, 0, lbl_806333F0[lbl_8064D580], 0x80000000);
        lbl_8064C320 = -1;
    } else {
        fn_801E7DCC(lbl_802645F8, index);
    }
}
