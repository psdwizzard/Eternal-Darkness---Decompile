typedef unsigned int u32;
typedef int s32;

typedef u32* Color;

extern void* lbl_8064D74C;
extern char lbl_8063B2AC[];
extern char lbl_80265DA0[];
extern char lbl_8063B374[];
extern char lbl_80265EBC[];
extern char lbl_8063B38C[];
extern u32 lbl_8064DF34;
extern char lbl_802515D0[];
extern u32 lbl_8064C2A8;
extern char lbl_806391F0[];

extern void fn_800243E8(void);
extern void fn_801EF530(void);
extern void fn_801EF580(void*);
extern void fn_80024434(void);
extern void fn_801EC9E4(void);
extern void fn_801EFE84(int);
extern void fn_80027F10(void);
extern void GXLoadTlut(void*, u32);
extern void fn_801EC7F4(void*, void*);
extern void fn_801F3960(u32*);
extern void fn_801A8D38(int);
extern void GXSetArray(u32, void*, u32);
extern void fn_801ED3F4(u32);
extern void fn_801A852C(Color, int, int, u32);
extern void fn_801A8F08(u32, u32, u32, u32, u32, u32, u32);
extern void fn_801E5FE4(void);
extern void fn_80180AD0(void);
extern void fn_80024468(void);
extern void fn_801EA9F8(void);
extern void fn_801EB194(u32);
extern void OSCheckStopwatch(void*);
extern void OSStopStopwatch(void*);
extern void OSResetStopwatch(void*);

void fn_800242B8(u32 value)
{
    u32 first;
    u32 second;

    fn_800243E8();
    fn_801EF530();
    fn_801EF580(lbl_8064D74C);
    fn_80024434();
    fn_801EC9E4();
    fn_801EFE84(0);
    fn_80027F10();
    GXLoadTlut(lbl_8063B2AC, 2);
    fn_801EC7F4(lbl_80265DA0, lbl_8063B374);
    fn_801EC7F4(lbl_80265EBC, lbl_8063B38C);
    first = lbl_8064DF34;
    fn_801F3960(&first);
    fn_801A8D38(5);
    GXSetArray(13, lbl_802515D0, 4);
    fn_801ED3F4(value);
    second = lbl_8064C2A8;
    fn_801A852C(&second, 0, 0, 0x80000000);
    fn_801A8F08(0xC4, 0x3E, 0x1C7, 0x198, -1, 0, 5);
    fn_801E5FE4();
    fn_80180AD0();
    fn_80024468();
    fn_801EA9F8();
    fn_801EB194(1);
    OSCheckStopwatch(lbl_806391F0);
    OSStopStopwatch(lbl_806391F0);
    OSResetStopwatch(lbl_806391F0);
}
