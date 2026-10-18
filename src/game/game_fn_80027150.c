typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef u32* Color;
typedef float f32;

extern u32 lbl_8064C2A8;
extern const f32 lbl_8064DF58;
extern const f32 lbl_8064DF5C;
extern const f32 lbl_8064DF60;
extern const f32 lbl_8064DF64;
extern const f32 lbl_8064DF68;

extern void GXSetCullMode(s32);
extern void fn_801ECF50(s32);
extern void C_MTXOrtho(void*, f32, f32, f32, f32, f32, f32);
extern void GXSetProjection(void*, s32);
extern void PSMTXIdentity(void*);
extern void GXLoadPosMtxImm(void*, s32);
extern void fn_801ED468(s32);
extern void fn_801A852C(Color, int, int, u32);
extern void fn_801F1034(void);
extern void fn_801ECEC8(s32, s32, s32);
extern void GXSetArray(s32, void*, s32);
extern void GXBegin(s32, s32, s32);
extern void fn_800272A8(u16);
extern void fn_8002729C(u16);
extern void fn_80027290(u16);
extern void fn_80026740(void);

void fn_80027150(void* first, void* second, void* third)
{
    unsigned char projection[0x40];
    unsigned char matrix[0x30];
    u32 color;
    u16 index;
    s32 i;

    GXSetCullMode(0);
    fn_801ECF50(3);
    C_MTXOrtho(projection, lbl_8064DF58, lbl_8064DF5C, lbl_8064DF58,
                lbl_8064DF60, lbl_8064DF64, lbl_8064DF68);
    GXSetProjection(projection, 1);
    PSMTXIdentity(matrix);
    GXLoadPosMtxImm(matrix, 0);
    fn_801ED468(0);

    color = lbl_8064C2A8;
    fn_801A852C(&color, -1, 0, 0);
    fn_801F1034();
    fn_801ECEC8(0, 3, 0);

    GXSetArray(9, first, 6);
    GXSetArray(13, third, 4);
    GXSetArray(11, second, 4);
    GXBegin(0x80, 6, 4);

    for (i = 0; (u16)i < 4; i++) {
        index = i;
        fn_800272A8(index);
        fn_8002729C(index);
        fn_80027290(index);
    }
    fn_80026740();
}
