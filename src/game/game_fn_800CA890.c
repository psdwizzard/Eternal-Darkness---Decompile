typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Color {
    u8 r, g, b, a;
} Color;

typedef struct HitInfo {
    u8 pad[0x10];
    float z;
    u8 pad2[0x18];
} HitInfo;

extern void *fn_80201B8C(void *);
extern void *fn_80201B54(void *);
extern void *fn_80201BC8(void *);
extern Vec3 *fn_8011F130(void);
extern int fn_80035628(void *);
extern void fn_8012B344(void *);
extern void *fn_8012C62C(void *, int, Color *, Color *, Color *, int);
extern void *fn_801294DC(void *, int, int, int);
extern void fn_801DAC18(void *, int);
extern void fn_801D38BC(int, Color *, s16 *);
extern int fn_8011F598(void *, int, int, int, HitInfo *, int);
extern void fn_801502C0(Vec3 *, Vec3 *, int, s16, int, int, int, int, int,
                        int, void *, Color *, int, int);
extern u32 fn_8011FA8C(void *, int, int);
extern void fn_8014F65C(Vec3 *, float, int, s16, int, Color *);
extern void fn_8014F5B8(Vec3 *, float, int, s16, int, Color *);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);

extern float lbl_8064F2B0;
extern Color lbl_8064F2B8;
extern Color lbl_8064F2BC;
extern float lbl_8064F2C0;
extern float lbl_8064F2C4;
extern Color lbl_80651A84;

void fn_800CA890(void *object, int unused, Vec3 *pos, int mode, int light)
{
    HitInfo hit;
    Vec3 target;
    Vec3 origin;
    Color color;
    Color fadeColor;
    Color ambient;
    Color diffuse;
    Color specular;
    Color glow;
    Color copy1;
    Color copy2;
    s16 size;
    u8 *data;
    void *model;
    Vec3 *cam;
    void *owner;
    int id;
    int dist;
    float d;

    data = *(u8 **)((u8 *)fn_80201B8C(object) + 0x8C);
    owner = fn_80201B54(object);
    model = fn_80201BC8(object);
    cam = fn_8011F130();
    *(Vec3 *)(data + 0xA0) = *pos;
    id = fn_80035628(object);
    fn_8012B344(model);
    specular = lbl_80651A84;
    diffuse = lbl_8064F2BC;
    ambient = lbl_8064F2B8;
    fn_8012C62C(model, 0xF, &ambient, &diffuse, &specular, 4);
    if (light != -1) {
        fn_801294DC(model, light, 0x20, 8);
    }
    fn_801DAC18(owner, 0);
    if (mode != 0) {
        dist = 200;
        fn_801D38BC(id, &color, &size);
        target = *(Vec3 *)(data + 0xA0);
        origin = *cam;
        switch (mode) {
        case 2:
        case 3:
            if (fn_8011F598(model, 0, 1, -1, &hit, 1) == -1) {
                target.z += lbl_8064F2C0;
                origin.z += lbl_8064F2C0;
            } else {
                d = hit.z - cam->z;
                if (d < lbl_8064F2B0) {
                    d = -d;
                }
                dist = d;
                target.z += (u16)dist;
                origin.z += (u16)dist;
            }
            break;
        default:
            target.z += lbl_8064F2C0;
            origin.z += lbl_8064F2C0;
            break;
        }
        glow = color;
        fn_801502C0(&origin, &target, id, size, 0x57, 0x57, 0x1E, 0x64, 0,
                    0x64, owner, &glow, mode, dist);
        fn_8011FA8C(model, 0xC0, 0);
    } else {
        fn_801D38BC(id, &fadeColor, &size);
        copy1 = fadeColor;
        fn_8014F65C(cam, lbl_8064F2C4, 0x64, size, 0, &copy1);
        copy2 = fadeColor;
        fn_8014F5B8((Vec3 *)(data + 0xA0), lbl_8064F2C4, 0x64, size, 0, &copy2);
    }
    fn_80201D2C(object, 0x30);
    fn_80201D14(object, 1);
}
