typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;
typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

extern void fn_801ED468(int);
extern void GXSetCullMode(int);
extern void fn_801ED118(void);
extern void fn_801EDA7C(void *, int, int, int);
extern void fn_801ECF50(int);
extern void fn_801ECD74(Color *);
extern void GXBegin(int, int, int);
extern void fn_800ED6F8(float, float, float);
extern void fn_800ED6F4(void);
extern char lbl_802FC53C[];
extern Color lbl_802FC5BC[];
extern float lbl_8064F888;

void fn_800EB750(Vec3 *quad, Vec3 *normal, Color *color, int alpha)
{
    Color localColor;
    Color defaultColor;
    Vec3 *vertex;
    int i;
    int j;
    Vec3 *tip;
    float scale;

    fn_801ED468(0x1B);
    GXSetCullMode(0);
    fn_801ED118();
    fn_801EDA7C(lbl_802FC53C, 0, 0x2BF, 0);
    fn_801ECF50(4);
    color->a = alpha;
    localColor = *color;
    fn_801ECD74(&localColor);
    GXBegin(0x80, 3, 4);
    i = 0;
    vertex = quad;
    do {
        fn_800ED6F8(vertex->x, vertex->y, vertex->z);
        i++;
        vertex++;
    } while (i < 4);
    fn_800ED6F4();
    scale = lbl_8064F888;
    tip = quad;
    j = 0;
    do {
        GXBegin(0xA8, 3, 2);
        fn_800ED6F8(tip->x, tip->y, tip->z);
        fn_800ED6F8(scale * normal->x + tip->x,
                      scale * normal->y + tip->y,
                      scale * normal->z + tip->z);
        fn_800ED6F4();
        j++;
        tip++;
    } while (j < 4);
    GXSetCullMode(1);
    defaultColor = lbl_802FC5BC[3];
    fn_801ECD74(&defaultColor);
}
