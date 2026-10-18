typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

extern u8 lbl_8030241C[];
extern u8 lbl_8063B2AC[];
extern u8 lbl_8063B374[];
extern u8 lbl_8063B38C[];
extern u8 lbl_80265DA0[];
extern u8 lbl_80265EBC[];
extern u8 lbl_806391F0[];
extern void* lbl_8064D74C;
extern u32 lbl_8064CBA0;
extern volatile s32 lbl_8064C600;

extern void fn_800243E8(void);
extern void fn_801EF530(void);
extern void fn_801EF580(void* value);
extern void fn_80024434(void);
extern void fn_80156EBC(void);
extern void fn_80156E50(u32 value);
extern void GXLoadTlut(void* data, u32 value);
extern void fn_801EC7F4(void* source, void* destination);
extern void fn_801F59A0(void);
extern void fn_801EC9E4(void);
extern void fn_801ECB40(u8 value);
extern void fn_80023258(void);
extern void fn_801E5FE4(void);
extern s32 fn_800B84C8(void);
extern void fn_800B84DC(void);
extern s32 fn_800B7D78(void);
extern s32 fn_800B194C(void);
extern void fn_800B7EF4(u8 value, u32 mask);
extern s32 fn_800B8F80(void);
extern void fn_800B8F9C(void);
extern s32 fn_8017BB60(void);
extern int CARDProbeEx(int index, int* first, int* second);
extern void fn_80156B1C(u32 value);
extern void fn_801571C4(void);
extern void fn_801F35A8(void);
extern void fn_801F55A0(void);
extern void fn_80024468(void);
extern void fn_801EB194(u32 value);
extern void fn_80020150(void);
extern void fn_8014426C(void);
extern void fn_801A99B4(void);
extern void fn_8017AF44(void);
extern void fn_800BC000(void);
extern void fn_800B9474(u32 value);
extern void OSCheckStopwatch(void* data);
extern void OSStopStopwatch(void* data);
extern void OSResetStopwatch(void* data);

void fn_80023CF8(void)
{
    int first;
    int second;

    fn_800243E8();
    fn_801EF530();
    fn_801EF580(lbl_8064D74C);
    fn_80024434();
    fn_80156EBC();
    fn_80156E50(1);
    fn_80156E50(0);
    GXLoadTlut(lbl_8063B2AC, 2);
    fn_801EC7F4(lbl_80265DA0, lbl_8063B374);
    fn_801EC7F4(lbl_80265EBC, lbl_8063B38C);
    fn_801F59A0();
    fn_801EC9E4();
    fn_801ECB40(lbl_8064CBA0);
    fn_80023258();
    if (lbl_8030241C[0x3E] != 10) {
        fn_801E5FE4();
    }
    if (fn_800B84C8()) {
        fn_800B84DC();
    }
    if (fn_800B7D78()) {
        s32 state = fn_800B194C();
        fn_800B7EF4(state != 1 && state != 2, 0xFF);
    }
    if (fn_800B8F80()) {
        fn_800B8F9C();
    }
    if (!fn_8017BB60()) {
        CARDProbeEx(0, &first, &second);
        CARDProbeEx(1, &first, &second);
    }
    fn_80156B1C(0);
    fn_801571C4();
    fn_801F35A8();
    fn_801F55A0();
    fn_80024468();
    if (lbl_8064C600 != 0) {
        lbl_8064C600--;
        fn_801EB194(0);
    } else {
        fn_801EB194(1);
    }
    fn_80020150();
    fn_8014426C();
    fn_801A99B4();
    fn_8017AF44();
    fn_800BC000();
    fn_800B9474(0x7F);
    OSCheckStopwatch(lbl_806391F0);
    OSStopStopwatch(lbl_806391F0);
    OSResetStopwatch(lbl_806391F0);
}
