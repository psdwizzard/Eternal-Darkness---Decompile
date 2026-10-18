typedef signed long s32;
typedef float f32;

extern s32 lbl_8064CBA4;
extern const f32 lbl_80650E00;
extern const f32 lbl_80650E0C;
extern const f32 lbl_80650E10;
extern const f32 lbl_80650E14;
extern const f32 lbl_80650E18;
extern const f32 lbl_80650E1C;
extern const f32 lbl_80650E20;

extern void GXSetCullMode(s32);
extern void fn_801ECF50(s32);
extern void C_MTXOrtho(void*, f32, f32, f32, f32, f32, f32);
extern void GXSetProjection(void*, s32);
extern void PSMTXIdentity(void*);
extern void GXLoadPosMtxImm(void*, s32);
extern void fn_801ED468(s32);

void fn_801A8D38(s32 mode)
{
    unsigned char projection[0x40];
    unsigned char matrix[0x30];

    GXSetCullMode(0);
    fn_801ECF50(mode);
    if (lbl_8064CBA4 == 1) {
        C_MTXOrtho(projection, lbl_80650E0C, lbl_80650E10,
                    lbl_80650E14, lbl_80650E18, lbl_80650E00,
                    lbl_80650E1C);
    } else {
        C_MTXOrtho(projection, lbl_80650E0C, lbl_80650E10,
                    lbl_80650E0C, lbl_80650E20, lbl_80650E00,
                    lbl_80650E1C);
    }
    GXSetProjection(projection, 1);
    PSMTXIdentity(matrix);
    GXLoadPosMtxImm(matrix, 0);
    fn_801ED468(0);
}
