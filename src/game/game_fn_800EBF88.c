typedef unsigned char u8;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Color {
    u8 r, g, b, a;
} Color;

extern short lbl_802FC53C[];
extern Color lbl_802FC5BC[];

extern void fn_80226C18(int, int);
extern void fn_80226D28(int);
extern void fn_801ED118(void);
extern int fn_801EDA7C(short*, int, int, void*);
extern void fn_801ECF50(unsigned int);
extern void fn_801ECD74(Color*);
extern void fn_80226AB4(int, int, int);
extern void fn_800ED6F8(float, float, float);
extern void fn_800ED6F4(void);

/* Draws a box between min and max as one 30-vertex strip, walking its edges. */
void fn_800EBF88(Vec3* min, Vec3* max, Color* color, u8 alpha)
{
    Color line;
    Color reset;

    fn_80226C18(0x18, 0);
    fn_801ED118();
    fn_801ECF50(4);
    fn_801EDA7C(lbl_802FC53C, 0, 0x2BF, 0);
    fn_80226D28(0);
    fn_801ECF50(4);
    color->a = alpha;
    line = *color;
    fn_801ECD74(&line);

    fn_80226AB4(0xB0, 3, 30);
    fn_800ED6F8(max->x, max->y, max->z);
    fn_800ED6F8(min->x, max->y, max->z);
    fn_800ED6F8(min->x, min->y, max->z);
    fn_800ED6F8(max->x, min->y, max->z);
    fn_800ED6F8(max->x, max->y, max->z);
    fn_800ED6F8(min->x, min->y, min->z);
    fn_800ED6F8(max->x, min->y, min->z);
    fn_800ED6F8(max->x, max->y, min->z);
    fn_800ED6F8(min->x, max->y, min->z);
    fn_800ED6F8(min->x, min->y, min->z);
    fn_800ED6F8(min->x, min->y, min->z);
    fn_800ED6F8(min->x, max->y, min->z);
    fn_800ED6F8(min->x, max->y, max->z);
    fn_800ED6F8(min->x, min->y, max->z);
    fn_800ED6F8(min->x, min->y, min->z);
    fn_800ED6F8(max->x, max->y, max->z);
    fn_800ED6F8(max->x, min->y, max->z);
    fn_800ED6F8(max->x, min->y, min->z);
    fn_800ED6F8(max->x, max->y, min->z);
    fn_800ED6F8(max->x, max->y, max->z);
    fn_800ED6F8(min->x, min->y, min->z);
    fn_800ED6F8(max->x, min->y, min->z);
    fn_800ED6F8(max->x, min->y, max->z);
    fn_800ED6F8(min->x, min->y, max->z);
    fn_800ED6F8(min->x, min->y, min->z);
    fn_800ED6F8(max->x, max->y, max->z);
    fn_800ED6F8(min->x, max->y, max->z);
    fn_800ED6F8(min->x, max->y, min->z);
    fn_800ED6F8(max->x, max->y, min->z);
    fn_800ED6F8(max->x, max->y, max->z);
    fn_800ED6F4();

    reset = lbl_802FC5BC[3];
    fn_801ECD74(&reset);
}
