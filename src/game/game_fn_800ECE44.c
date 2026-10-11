typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Shape {
    Vec3 first;
    Vec3 second;
    float radius;
    Vec3 axis;
    float length;
    Vec3 center;
    float bound_radius;
} Shape;

typedef struct Hit {
    Vec3 normal;
    Vec3 point;
} Hit;

typedef struct DebugEntry {
    u8 pad0[0x2c];
    s16 x;
    s16 y;
    s16 z;
    u16 pad32;
    u32 height;
    u8 pad38[0x10];
    u32 flags;
} DebugEntry;

typedef struct DebugList {
    u8 pad0[0x34];
    u16 count;
    u16 pad36;
    DebugEntry* entries;
} DebugList;

extern DebugList* fn_8015C390(int);
extern void* fn_8015C2FC(int);
extern int fn_80201B44(void);
extern void* fn_80201814(int);
extern void* fn_80201BC8(void*);
extern void fn_8013F3C0(Shape*, const Vec3*, const Vec3*, float);
extern void* fn_8013FBE4(void*, const Shape*, Hit*, int, int);
extern int fn_800EC318(int, DebugEntry*, char*);
extern void fn_800EBA80(int, Vec3*, u32*, int, float);
extern void fn_800ED4BC(Vec3*, int, const char*, ...);
extern u32 lbl_802FC5BC[];
extern float lbl_8064F8C8;
extern float lbl_8064F8CC;
extern float lbl_8064F8D0;

void fn_800ECE44(int selector)
{
    void* collision;
    DebugEntry* entry;
    DebugList* list;
    int i;
    Vec3 end;
    Vec3 position;
    Shape shape;
    Hit hit;
    char description[0x168];
    u32 color;
    int colorIndex;

    list = fn_8015C390(selector);
    collision = fn_8015C2FC(selector);
    fn_80201BC8(fn_80201814(fn_80201B44()));
    if (list != 0 && list->count != 0) {
        entry = list->entries;
        i = 0;
        while (i < list->count) {
            if (entry->flags & 0x40) {
                position.x = (float)entry->x;
                position.y = (float)entry->y;
                position.z = lbl_8064F8C8 + (float)entry->z;
                end = position;
                end.z -= lbl_8064F8CC;
                fn_8013F3C0(&shape, &position, &end, lbl_8064F8D0);
                if (fn_8013FBE4(collision, &shape, &hit, 0, 0) == 0) {
                    colorIndex = fn_800EC318(i, entry, description);
                    color = lbl_802FC5BC[colorIndex];
                    fn_800EBA80(1, &position, &color, 0x7f, (float)entry->height);
                    position.z += (float)(entry->height + 0x14);
                    fn_800ED4BC(&position, colorIndex, description);
                }
            }
            i++;
            entry++;
        }
    }
}
