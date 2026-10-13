typedef signed char s8;
typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef float Matrix[3][4];

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Color {
    u8 r, g, b, a;
} Color;

typedef struct ScreenPosition {
    int x;
    int y;
    int visible;
} ScreenPosition;

typedef struct Marker {
    u8 pad0[0x2C];
    s16 x;
    s16 y;
    s16 z;
    u8 pad32[0x2];
    u32 size;
    u8 pad38[0x10];
    u32 flags;
} Marker;

typedef struct MarkerTable {
    u8 pad0[0x34];
    u16 count;
    Marker* markers;
} MarkerTable;


extern s16 lbl_802FC53C[];
extern Color lbl_802FC5BC[];
extern Vec3 lbl_8024A53C[];
extern u8 lbl_8024A584[];
extern char lbl_8024A59C[];
extern Vec3 lbl_80327F60[];
extern Vec3 lbl_8032808C[];
extern float lbl_8063C068[3][4];
extern u8 lbl_8063BF28[];
extern int lbl_8064CBD0;
extern int lbl_8064D5FC;
extern const float lbl_8064F8B0;
extern const float lbl_8064F8B4;
extern const float lbl_8064F8B8;
extern const float lbl_8064F8BC;

extern MarkerTable* fn_8015C390(int);
extern void fn_801ED118(void);
extern int fn_801EDA7C(s16*, int, int, void*);
extern void fn_801ECF50(u32);
extern void fn_80226D28(int);
extern void fn_801ED468(int);
extern void fn_800EC5EC(void*, u8, Vec3*, u8*);
extern void fn_800EC640(void);
extern void fn_800EC6C4(void);
extern u32 fn_801F6D90(int, int, int);
extern int fn_800EC318(int, Marker*, void*);
extern void fn_80179DB0(Vec3*, s16*);
extern void fn_80211484(Matrix, float, float, float);
extern void fn_802114B8(Matrix, float, float, float);
extern void fn_80210FDC(Matrix, Matrix, Matrix);
extern void fn_801ECD74(Color);
extern void fn_80211764(Matrix, Vec3*, Vec3*, int);
extern void fn_80226AB4(int, int, u16);
extern void fn_800ED6F8(float, float, float);
extern void fn_800ED70C(float, float, float);
extern void fn_800ED6F4(void);
extern Color fn_801E3A34(Color);
extern void fn_801E3AA4(int);
extern s8 fn_801E5AD0(s8);
extern void fn_801E5014(void);
extern float fn_800ED784(s16*, float*);
extern void fn_801F6B6C(Vec3*, ScreenPosition*, int, int);
extern void fn_801E5430(s16, s16);
extern void fn_801E57F4(float, const char*, ...);
extern int fn_801ED3F4(int);
extern void fn_801ECC4C(void);
extern void fn_8022B4B8(void*, int);

static inline void EmitVertex(u32 index)
{
    fn_800ED6F8(lbl_80327F60[index].x, lbl_80327F60[index].y, lbl_80327F60[index].z);
    fn_800ED70C(lbl_8032808C[index].x, lbl_8032808C[index].y, lbl_8032808C[index].z);
}

void fn_800EC6FC(int kind)
{
    MarkerTable* table;
    Marker* marker;
    int i;
    int n;
    Marker* entry;
    int j;
    int k;
    int tri;
    u32 dist;
    float size;
    float scale;
    float fit;
    float low;
    Color oldColor;
    Color color;
    Color label;
    s8 oldFont;
    int oldState;
    Vec3 pos;
    Vec3 world;
    ScreenPosition screen;
    Matrix mtx;
    Matrix transMtx;
    Matrix scaleMtx;
    char text[0x164];

    table = fn_8015C390(kind);
    fn_801ED118();
    fn_801EDA7C(lbl_802FC53C, 0, 0x2BF, 0);
    fn_801ECF50(4);
    fn_80226D28(0);
    fn_801ED468(0x3C);
    lbl_8064CBD0 = 0;
    for (tri = 7; tri >= 0; tri--) {
        fn_800EC5EC(0, tri, lbl_8024A53C, lbl_8024A584);
    }

    if (table != 0) {
        if (table->count != 0) {
            marker = table->markers;
            fn_800EC640();
            for (i = 0; i < table->count; i++, marker++) {
                dist = fn_801F6D90(marker->x, marker->y, marker->z);
                if (dist == 0 || dist >= 1000) {
                    continue;
                }
                size = (u32)marker->size;
                color = lbl_802FC5BC[fn_800EC318(i, marker, text)];
                fn_80179DB0(&pos, &marker->x);
                fn_80211484(transMtx, pos.x, pos.y, pos.z);
                fn_80210FDC(lbl_8063C068, transMtx, mtx);
                fn_802114B8(scaleMtx, size, size, size);
                fn_80210FDC(mtx, scaleMtx, mtx);
                color.a = 0x7F;
                fn_801ECD74(color);
                fn_80211764(mtx, lbl_8032808C, lbl_80327F60, lbl_8064CBD0);
                k = 0;
                fn_80226AB4(0x90, 3, lbl_8064CBD0);
                for (j = 0; j < lbl_8064CBD0 / 3; j++, k += 3) {
                    fn_800ED6F8(lbl_80327F60[k].x, lbl_80327F60[k].y, lbl_80327F60[k].z);
                    fn_800ED70C(lbl_8032808C[k].x, lbl_8032808C[k].y, lbl_8032808C[k].z);
                    EmitVertex(k + 1);
                    EmitVertex(k + 2);
                }
                fn_800ED6F4();
            }
            fn_800EC6C4();

            oldColor = fn_801E3A34(lbl_802FC5BC[0]);
            entry = table->markers;
            oldState = lbl_8064D5FC;
            fn_801E3AA4(0);
            oldFont = fn_801E5AD0(0x63);
            fn_801E5014();
            for (n = 0; n < table->count; n++, entry++) {
                dist = fn_801F6D90(entry->x, entry->y, entry->z + (int)(entry->size + 20));
                if (dist == 0 || dist >= 600) {
                    continue;
                }
                fn_800ED784(&entry->x, &world.x);
                fn_800ED784(&entry->y, &world.y);
                world.z = entry->z + (int)(entry->size + 20);
                fn_801F6B6C(&world, &screen, 0, 0);
                if (screen.visible == 0 || screen.x <= 0 || screen.x >= 640 ||
                    screen.y <= 0 || screen.y >= 480) {
                    continue;
                }
                fit = lbl_8064F8B4 / (lbl_8064F8B8 * dist);
                low = MAX(fit, 0.2f);
                scale = lbl_8064F8BC;
                if (scale < low) {
                    scale = lbl_8064F8BC;
                } else {
                    scale = 0.2f;
                    if (fit > scale) {
                        scale = fit;
                    }
                }
                label = lbl_802FC5BC[fn_800EC318(n, entry, text)];
                label.a = 0x7F;
                fn_801ECD74(label);
                fn_801E5430(screen.x, screen.y);
                fn_801E57F4(scale, "%s", text);
            }
        }
        fn_801E3A34(oldColor);
        fn_801E5AD0(oldFont);
        fn_801ED3F4(oldState);
        fn_801ECC4C();
        fn_8022B4B8(lbl_8063BF28, 0);
    }

    fn_80226D28(1);
    fn_801ECD74(lbl_802FC5BC[3]);
}
