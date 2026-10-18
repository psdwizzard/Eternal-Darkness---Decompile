typedef signed char s8;
typedef int s32;
typedef unsigned char u8;
typedef unsigned int u32;

extern void* lbl_8064C4E0;
extern u32 lbl_8064D6E8;
extern u8 lbl_8030F540[];

extern void* fn_8015AB00(s32);
extern void fn_801FCF00(void);
extern void fn_801ED56C(s32);
extern void fn_801F194C(void);
extern void fn_801F3D20(void);
extern s32 fn_801EF384(void);
extern void fn_801F4EF4(void);
extern void fn_80156C04(void);
extern s32 fn_8015E4E8(void);
extern void fn_800862F8(void);
extern void fn_801F3DE4(void);
extern void fn_80120BFC(s32);
extern void GXSetDrawSync(s32);
extern s32 fn_800473A4(void);
extern void fn_801FCF04(void);
extern void fn_801882C4(void);
extern void fn_80156CBC(void);
extern void fn_801882D0(void);
extern void fn_801FF9E4(void);
extern void fn_800086CC(void);
extern void fn_800ED054(s32);
extern void fn_8002617C(void);
extern void fn_801F47F8(void);
extern void fn_800AD484(void);
extern s32 fn_80047304(void);
extern void fn_801F4D10(void);
extern int fn_801E79FC(void*, int);
extern void fn_8007D4D4(void);
extern void fn_801EA9F8(void);
extern void fn_80006B38(void);
extern void fn_80026280(void);
extern void fn_80084F38(void);
extern void fn_80046D7C(void);
extern void fn_80046D44(void);
extern void fn_80028BE4(void);

void fn_80008154(void)
{
    void* mode;
    u8* state;

    mode = fn_8015AB00(2);
    fn_801FCF00();
    if (mode != 0) {
        fn_801ED56C(1);
    }
    fn_801F194C();
    fn_801F3D20();
    if (fn_801EF384() != 0) {
        fn_801F4EF4();
    }
    fn_80156C04();
    if (fn_8015E4E8() == 0) {
        fn_800862F8();
    }
    fn_801F3DE4();
    fn_80120BFC(1);
    GXSetDrawSync(0xB00B);
    if (fn_800473A4() == 0) {
        fn_801FCF04();
    }
    fn_801882C4();
    fn_80156CBC();
    fn_801882D0();
    fn_801FF9E4();
    fn_800086CC();
    if (mode != 0) {
        fn_801ED56C(0);
    }
    fn_800ED054(2);
    fn_8002617C();
    if (fn_800473A4() != 0) {
        fn_801F47F8();
    }
    fn_800AD484();
    if (fn_8015E4E8() == 0 ||
        ((state = lbl_8030F540), (s8)state[0x1DC] == 0)) {
        if (fn_80047304() != 0) {
            fn_801F4D10();
        }
    }
    if (fn_801E79FC(lbl_8064C4E0, 0x300) != 0) {
        fn_8007D4D4();
        fn_801EA9F8();
    }
    lbl_8064D6E8 = 1;
    fn_80006B38();
    fn_80026280();
    fn_80084F38();
    lbl_8064D6E8 = 0;
    fn_80046D7C();
    fn_80046D44();
    fn_80028BE4();
}
