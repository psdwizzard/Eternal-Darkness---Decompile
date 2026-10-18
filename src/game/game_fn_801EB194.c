typedef unsigned char u8;
typedef unsigned int u32;

extern int lbl_8064CB50;
extern u32 lbl_8064D5E0;
extern u32 lbl_80651310;
extern volatile u8 lbl_8064C368;
extern char lbl_8063BEC0[];

extern void fn_801EB118(void);
extern void fn_801ECEC8(int, int, int);
extern void* fn_8015AB00(int);
extern void GXSetColorUpdate(int);
extern int fn_801EF384(void);
extern void GXSetAlphaUpdate(int);
extern void* fn_801EB080(void);
extern void GXCopyDisp(void*, int);
extern void fn_801A8D38(int);
extern void fn_801A8660(int, int, int, int, int, const u32*);
extern void GXSetDrawDone(void);
extern void GXSetDrawSync(int);
extern void fn_801EB11C(void);
extern void OSSendMessage(void*, int, int);
extern void fn_801EFEC4(int);

void fn_801EB194(int value)
{
    volatile u32 color0;
    u32 color1;

    fn_801EB118();
    fn_801ECEC8(1, 3, 1);
    if (fn_8015AB00(2) && lbl_8064CB50 == 0 && lbl_8064D5E0 == 0) {
        GXSetColorUpdate(0);
    } else {
        GXSetColorUpdate(1);
    }
    if (lbl_8064D5E0 != 0) {
        lbl_8064D5E0--;
    }
    if (fn_801EF384()) {
        GXSetAlphaUpdate(0);
    } else {
        GXSetAlphaUpdate(1);
    }
    if (value) {
        GXCopyDisp(fn_801EB080(), 1);
    } else {
        color0 = lbl_80651310;
        fn_801A8D38(5);
        fn_801ECEC8(1, 7, 1);
        color1 = color0;
        fn_801A8660(0, 0, 640, 480, -30360, &color1);
        fn_801ECEC8(1, 3, 1);
    }
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(0);
    GXSetDrawDone();
    GXSetDrawSync(0xBEEF);
    fn_801EB11C();
    OSSendMessage(lbl_8063BEC0, 0, 1);
    if (lbl_8064C368 != 2) {
        (void)lbl_8064C368;
    }
    fn_801EFEC4(value);
}
