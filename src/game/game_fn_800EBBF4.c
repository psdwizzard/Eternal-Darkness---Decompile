typedef signed short s16;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Color {
    u8 r, g, b, a;
} Color;

extern s16 lbl_802FC53C[];
extern Color lbl_802FC5BC[];

extern void GXSetCullMode(int);
extern void fn_801ED118(void);
extern int fn_801EDA7C(s16*, int, int, void*);
extern void fn_801ECF50(u32);
extern void fn_801ECD74(Color*);
extern void GXBegin(int, int, int);
extern void fn_800ED6F8(float, float, float);
extern void fn_800ED6F4(void);

void fn_800EBBF4(Vec3* min, Vec3* max, Color* color, u8 alpha)
{
    Color fill;
    Color outline;

    GXSetCullMode(2);
    fn_801ED118();
    fn_801EDA7C(lbl_802FC53C, 0, 0x2BF, 0);
    fn_801ECF50(4);
    color->a = alpha;
    fill = *color;
    fn_801ECD74(&fill);

    /* Six faces, each submitted as a quad. */
    GXBegin(0x80, 3, 24);
    fn_800ED6F8(max->x, min->y, max->z);
    fn_800ED6F8(min->x, min->y, max->z);
    fn_800ED6F8(min->x, max->y, max->z);
    fn_800ED6F8(max->x, max->y, max->z);

    fn_800ED6F8(min->x, min->y, min->z);
    fn_800ED6F8(max->x, min->y, min->z);
    fn_800ED6F8(max->x, max->y, min->z);
    fn_800ED6F8(min->x, max->y, min->z);

    fn_800ED6F8(min->x, min->y, min->z);
    fn_800ED6F8(min->x, max->y, min->z);
    fn_800ED6F8(min->x, max->y, max->z);
    fn_800ED6F8(min->x, min->y, max->z);

    fn_800ED6F8(max->x, max->y, min->z);
    fn_800ED6F8(max->x, min->y, min->z);
    fn_800ED6F8(max->x, min->y, max->z);
    fn_800ED6F8(max->x, max->y, max->z);

    fn_800ED6F8(min->x, min->y, max->z);
    fn_800ED6F8(max->x, min->y, max->z);
    fn_800ED6F8(max->x, min->y, min->z);
    fn_800ED6F8(min->x, min->y, min->z);

    fn_800ED6F8(max->x, max->y, max->z);
    fn_800ED6F8(min->x, max->y, max->z);
    fn_800ED6F8(min->x, max->y, min->z);
    fn_800ED6F8(max->x, max->y, min->z);
    fn_800ED6F4();

    /* Closed outlines of the two Z faces. */
    outline = lbl_802FC5BC[3];
    fn_801ECD74(&outline);
    GXBegin(0xB0, 3, 5);
    fn_800ED6F8(max->x, max->y, max->z);
    fn_800ED6F8(min->x, max->y, max->z);
    fn_800ED6F8(min->x, min->y, max->z);
    fn_800ED6F8(max->x, min->y, max->z);
    fn_800ED6F8(max->x, max->y, max->z);
    fn_800ED6F4();

    GXBegin(0xB0, 3, 5);
    fn_800ED6F8(min->x, min->y, min->z);
    fn_800ED6F8(max->x, min->y, min->z);
    fn_800ED6F8(max->x, max->y, min->z);
    fn_800ED6F8(min->x, max->y, min->z);
    fn_800ED6F8(min->x, min->y, min->z);
    fn_800ED6F4();

    /* Four edges joining the Z faces. */
    GXBegin(0xA8, 3, 8);
    fn_800ED6F8(min->x, min->y, min->z);
    fn_800ED6F8(min->x, min->y, max->z);
    fn_800ED6F8(max->x, min->y, min->z);
    fn_800ED6F8(max->x, min->y, max->z);
    fn_800ED6F8(min->x, max->y, min->z);
    fn_800ED6F8(min->x, max->y, max->z);
    fn_800ED6F8(max->x, max->y, min->z);
    fn_800ED6F8(max->x, max->y, max->z);
    fn_800ED6F4();
}
