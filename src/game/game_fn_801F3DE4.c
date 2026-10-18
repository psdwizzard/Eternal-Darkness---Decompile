typedef unsigned long u32;

extern char lbl_8063C068[], lbl_8063BF28[];
extern const float lbl_80651348, lbl_8065134C, lbl_80651378, lbl_8065137C;
extern u32 lbl_802FC5BC[];
extern long lbl_8064B810;
extern u32 lbl_8064D724, lbl_8064D728;

extern void GXLoadPosMtxImm(void*, int);
extern void GXLoadNrmMtxImm(void*, int);
extern void GXSetViewport(float, float, float, float, float, float);
extern void GXSetScissor(int, int, int, int);
extern void GXSetProjection(void*, int);
extern void fn_801ED468(int);
extern void fn_801ECEC8(int, int, int);
extern void fn_801FE56C(void);
extern void fn_801ECD74(void*);
extern void fn_801ECF50(int);
extern void GXSetAlphaUpdate(int);
extern void fn_801F2BC8(int);

void fn_801F3DE4(void)
{
    u32 value;

    GXLoadPosMtxImm(lbl_8063C068, 0x1B);
    GXLoadNrmMtxImm(lbl_8063C068, 0x1B);
    GXSetViewport(lbl_80651348, lbl_80651348, lbl_80651378,
                lbl_8065137C, lbl_80651348, lbl_8065134C);
    GXSetScissor(0, 0, 0x280, 0x1E0);
    GXSetProjection(lbl_8063BF28, 0);
    fn_801ED468(0x1B);
    fn_801ECEC8(1, 3, 0);
    fn_801FE56C();
    value = lbl_802FC5BC[3];
    fn_801ECD74(&value);
    if (lbl_8064B810 != 0) {
        fn_801ECF50(2);
        lbl_8064D724 = 0;
        lbl_8064D728 = 0;
        GXSetAlphaUpdate(0);
        fn_801F2BC8(3);
        fn_801F2BC8(2);
        fn_801ECEC8(1, 3, 1);
    }
}
