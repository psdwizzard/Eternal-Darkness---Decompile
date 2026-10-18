typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
typedef float Matrix34[3][4];

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Color {
    u8 r, g, b, a;
} Color;

extern s16 lbl_802FC53C[];
extern Color lbl_802FC5BC[];
extern Matrix34 lbl_8063C068;

extern void GXSetCullMode(int);
extern void fn_801ED118(void);
extern int fn_801EDA7C(s16*, int, int, void*);
extern void fn_801ECF50(u32);
extern void fn_801ED468(int);
extern void PSMTXTrans(Matrix34, float, float, float);
extern void PSMTXScale(Matrix34, float, float, float);
extern void PSMTXConcat(Matrix34, Matrix34, Matrix34);
extern void GXLoadPosMtxImm(Matrix34, u32);
extern void fn_801ECD74(Color*);
extern void GXDrawSphere(int, int);
extern void GXDrawOctahedron(void);
extern void fn_801EC9A8(void);

void fn_800EBA80(int shape, Vec3* position, Color* color, u8 alpha, float scale)
{
    Matrix34 transform;
    Matrix34 translation;
    Matrix34 scaling;
    Color fill;
    Color outline;

    GXSetCullMode(0);
    fn_801ED118();
    fn_801EDA7C(lbl_802FC53C, 0, 0x2BF, 0);
    fn_801ECF50(4);
    fn_801ED468(0);
    PSMTXTrans(translation, position->x, position->y, position->z);
    PSMTXConcat(lbl_8063C068, translation, transform);
    PSMTXScale(scaling, scale, scale, scale);
    PSMTXConcat(transform, scaling, transform);
    GXLoadPosMtxImm(transform, 0);
    color->a = alpha;
    fill = *color;
    fn_801ECD74(&fill);

    switch (shape) {
    case 1:
        GXDrawSphere(4, 8);
        break;
    case 0:
        GXDrawSphere(8, 16);
        break;
    case 2:
        GXDrawOctahedron();
        break;
    }

    fn_801ED468(0x1B);
    GXSetCullMode(1);
    outline = lbl_802FC5BC[3];
    fn_801ECD74(&outline);
    fn_801EC9A8();
}
