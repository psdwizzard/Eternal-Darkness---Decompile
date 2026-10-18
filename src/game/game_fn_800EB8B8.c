typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;

typedef struct Color {
    u8 r, g, b, a;
} Color;

typedef struct PathPoint {
    u8 pad0[4];
    s16 x;
    s16 y;
    s16 z;
    u8 padA[2];
} PathPoint;

typedef struct Path {
    u8 pad0[0x68];
    u16 count;
    u16 pad6A;
    PathPoint* points;
} Path;

extern void fn_801ED468(int);
extern void GXSetCullMode(int);
extern void fn_801ED118(void);
extern void fn_801EDA7C(void*, int, int, int);
extern void fn_801ECF50(int);
extern void fn_801ECD74(Color);
extern void GXBegin(int, int, u16);
extern void fn_800ED6F8(float, float, float);
extern void fn_800ED6F4(void);

extern char lbl_802FC53C[];

void fn_800EB8B8(Path* path, Color* color)
{
    int i;

    if (path->count == 0) {
        return;
    }

    fn_801ED468(0x1B);
    GXSetCullMode(0);
    fn_801ED118();
    fn_801EDA7C(lbl_802FC53C, 0, 0x2BF, 0);
    fn_801ECF50(4);
    fn_801ECD74(*color);
    GXBegin(0xA8, 3, (path->count - 1) * 2);

    for (i = 0; i < path->count - 1; i++) {
        PathPoint* p = &path->points[i];
        float x = p[1].x;
        float y = p[1].y;
        float z = p[1].z;
        fn_800ED6F8(p[0].x, p[0].y, p[0].z);
        fn_800ED6F8(x, y, z);
    }
    fn_800ED6F4();
}
