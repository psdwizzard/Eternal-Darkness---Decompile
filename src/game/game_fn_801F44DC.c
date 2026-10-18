typedef float Matrix34[3][4];

extern const float lbl_80651348;
extern const float lbl_8065137C;
extern const float lbl_80651378;
extern const float lbl_806513E4;
extern const float lbl_806513FC;
extern const float lbl_80651400;

extern void C_MTXOrtho();
extern void GXSetProjection();
extern void PSMTXIdentity();
extern void PSMTXTrans();
extern void GXLoadPosMtxImm();
extern void fn_801ED468();
extern void GXSetCullMode();

void fn_801F44DC(void)
{
    float projection[18];
    Matrix34 matrix;
    float one = lbl_80651348;

    C_MTXOrtho(projection, one, lbl_8065137C,
                one, lbl_80651378, one,
                lbl_806513E4);
    GXSetProjection(projection, 1);
    PSMTXIdentity(matrix);
    PSMTXTrans(matrix, lbl_806513FC, lbl_80651400, lbl_80651348);
    GXLoadPosMtxImm(matrix, 0);
    fn_801ED468(0);
    GXSetCullMode(0);
}
