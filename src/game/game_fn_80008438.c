typedef int s32;
typedef unsigned char u8;

extern s32 lbl_8064C600;
extern void* lbl_8064D74C;
extern u8 lbl_80331748[];
extern u8 lbl_8064C590;
extern float lbl_8064CF04;
extern float lbl_8064CF08;
extern void* lbl_8064D6EC;
extern void* lbl_8064C4E4;
extern s32 lbl_8064D6E8;
extern s32 lbl_8064D6C4;
extern s32 lbl_8064CB68;
extern u8 lbl_806391F0[];
extern void* __OSCurrHeap;
extern u8 lbl_805E2B1C[];

extern void fn_800243E8(void);
extern void fn_801EF530(void);
extern void fn_8015CA08(void);
extern void fn_800B9474(s32);
extern void fn_80156E50(s32);
extern s32 fn_800BD944(void);
extern void OSSendMessage(void*, s32, s32);
extern void fn_801F7234(s32);
extern s32 fn_801F3B80(void);
extern void fn_801EF580(void*);
extern void fn_801F59A0(void);
extern void fn_801EC9E4(void);
extern void fn_80024434(void);
extern void fn_8014426C(void);
extern void fn_801D0050(s32, void*);
extern void fn_800E6EB0(void);
extern void fn_8007FB40(void);
extern void fn_801FA92C(void);
extern void fn_801A8478(void);
extern void fn_801D17EC(void);
extern void fn_8014B610(void);
extern void* fn_8011E190(s32);
extern void fn_8016AF2C(void);
extern s32 fn_800462C8(s32);
extern void fn_801237F0(s32);
extern void fn_8018807C(float, float);
extern void fn_80156EBC(void);
extern void fn_80200C74(void);
extern void fn_8011E26C(s32);
extern void fn_80086218(void);
extern void fn_80006B08(void);
extern void fn_8011E534(void);
extern void fn_80027F10(void);
extern void fn_801A99B4(void);
extern void fn_800AF230(void);
extern void fn_800E4B1C(void);
extern void fn_80008154(void);
extern void fn_801F3158(void*);
extern void fn_801E5FE4(void);
extern void fn_80008910(s32);
extern void fn_800AF0AC(void);
extern void fn_801F55A0(void);
extern void fn_801E83A8(void);
extern void fn_8015C194(void*);
extern void fn_80029358(void);
extern void fn_8014939C(void);
extern void fn_801E3AA4(s32);
extern void fn_801F35A8(void);
extern void fn_801F33E8(void);
extern void fn_800EB74C(void);
extern void fn_800EB434(void);
extern void fn_801A92D0(void);
extern void fn_80156B1C(s32);
extern void fn_801571C4(void);
extern void fn_8017AF44(void);
extern void fn_80024468(void);
extern void fn_801EB194(s32);
extern void fn_800C9530(void);
extern s32 fn_800473A4(void);
extern s32 fn_80047364(void);
extern void fn_8004736C(void);
extern void fn_8006FD90(void);
extern void fn_8011B74C(void);
extern void fn_800BC000(void);
extern void OSCheckStopwatch(void*);
extern void OSStopStopwatch(void*);
extern void OSResetStopwatch(void*);
extern void OSCheckHeap(void*);

void fn_80008438(void)
{
    void** pending;
    s32 old_count = lbl_8064C600;
    s32 startup_state;
    s32 thread;
    s32 current_thread;

    fn_800243E8();
    fn_801EF530();
    fn_8015CA08();
    fn_800B9474(0x7F);
    fn_80156E50(1);
    if (fn_800BD944() == 0) {
        OSSendMessage(lbl_805E2B1C, -0x1A0A, 0);
    }

    fn_801F7234(3);
    startup_state = fn_801F3B80();
    fn_801EF580(lbl_8064D74C);
    fn_801F59A0();
    fn_801EC9E4();
    fn_80024434();
    fn_8014426C();

    pending = (void**)(lbl_80331748 + 0xAC);
    if (*pending != 0) {
        fn_801D0050(1, pending);
        *pending = 0;
    }

    fn_800E6EB0();
    fn_8007FB40();
    fn_801FA92C();
    fn_801A8478();
    fn_801D17EC();
    fn_8014B610();
    if (fn_8011E190(2) == 0) {
        fn_8016AF2C();
    }

    lbl_8064C590 = 0;
    fn_80156E50(0);
    fn_801237F0(fn_800462C8(0) == 0);
    fn_8018807C(lbl_8064CF04, lbl_8064CF08);
    fn_80156EBC();
    fn_80200C74();
    if (fn_8011E190(-1) != 0) {
        fn_8011E26C(0);
    }

    fn_80086218();
    fn_80006B08();
    fn_8011E534();
    fn_80027F10();
    fn_801A99B4();
    fn_800AF230();
    fn_800E4B1C();

    if (startup_state == 0 && old_count == 0) {
        fn_80008154();
        fn_801F3158(lbl_8064D6EC);
        fn_801E5FE4();
        fn_80008910(2);
        fn_800AF0AC();
        fn_801F55A0();
    }

    fn_801E83A8();
    fn_8015C194(lbl_8064C4E4);
    fn_80029358();
    fn_8014939C();
    lbl_8064D6E8 = 1;
    fn_801E3AA4(0);
    fn_801F35A8();
    if (lbl_8064D6C4 != 0) {
        lbl_8064D6C4 = 0;
        fn_801F33E8();
    }

    fn_800EB74C();
    fn_800EB434();
    if (lbl_8064CB68 != 0) {
        fn_801A92D0();
    }

    lbl_8064D6E8 = 0;
    fn_80156B1C(0);
    fn_801571C4();
    fn_8017AF44();
    fn_800B9474(0x7F);
    fn_80024468();

    if (old_count > 0) {
        lbl_8064C600--;
        fn_801EB194(0);
    } else {
        lbl_8064C600 = 0;
        fn_801EB194(1);
    }

    fn_800C9530();
    thread = fn_800473A4();
    current_thread = fn_80047364();
    if (current_thread != thread) {
        fn_80047364();
        fn_8004736C();
    }

    fn_8006FD90();
    fn_8011B74C();
    fn_800BC000();
    OSCheckStopwatch(lbl_806391F0);
    OSStopStopwatch(lbl_806391F0);
    OSResetStopwatch(lbl_806391F0);
    OSCheckHeap(__OSCurrHeap);
}
