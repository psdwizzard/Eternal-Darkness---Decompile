typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec4 { float x, y, z, w; } Vec4;
typedef float Matrix34[3][4];
typedef struct Color {
    u32 word;
    u16 alpha;
} Color;
typedef struct Packet {
    u8 type, mode;
    u8 pad02[2];
    u16 id;
    u8 pad06[14];
    u8 flag14;
    u8 pad15[3];
    u32 word18, word1C;
} Packet;

extern u32 lbl_80651F08;
extern u16 lbl_80651F0C;
extern u32 lbl_8023B5C0[];
extern float lbl_806511B0, lbl_806511B4, lbl_806511B8, lbl_806511BC;
extern float lbl_806511C0, lbl_806511C4, lbl_806511C8;
extern float lbl_806511CC, lbl_806511D0, lbl_806511D4, lbl_806511D8;
extern int lbl_8064D18C;
extern u32 lbl_80651F10;
extern void* fn_8011FE34(void*);
extern void fn_802114E0(void*, void*);
extern void fn_80211710(void*, void*, void*);
extern void fn_80211A6C(void*, void*, void*);
extern void fn_80211A48(void*, void*, void*);
extern void fn_80179BC0(void*, void*);
extern void fn_8017A244(void*, void*, float);
extern void fn_801CE980(int, int, int, int, s16*, int, int);
extern int fn_80128258(void);
extern int fn_80128130(void);
extern int fn_800453AC();
extern void fn_8020104C(int, int, int, int, float);
extern void* fn_80201814(int);
extern int fn_80201BC8(void*);
extern int fn_801D3974(int);
extern void fn_8012C62C();
extern void fn_8011FA8C();
extern void fn_8012CBE8();
extern void fn_8012F58C();
extern void fn_8012CDF0();
extern void fn_80181F5C(Packet*);
extern int fn_801D3A24(int, int);
extern void* fn_80148008(Vec3*, Color*, Packet*, void*);
extern void* fn_80156938(void);
extern void fn_8017FE14(void*, void*);
extern void fn_8017FF1C(void*, int);
extern void fn_80182014(void);
extern void fn_8018EDE4(void);

/* NonMatching: honest mode-driven reconstruction of the complete effect setup.
 * Retail's 0x300-byte frame depends on exact aggregate-copy lowering, fctiwz
 * spill-slot reuse, and GC/1.3 register scheduling; those codegen details are
 * intentionally preserved as the documented divergence instead of using asm. */
void fn_801DDB84(Vec3* origin, int variant, u8 mode, void* object)
{
    Vec3 base = *origin;
    Vec3 a, b, c, input, table78, table6C;
    Matrix34 matrix;
    Vec4 rotation;
    s16 points[12];
    Packet packet;
    Color color;
    float scale = lbl_806511B0;
    int effect = 5;
    int life = 60;
    int kind;
    int handle;
    void* drawable;

    color.word = lbl_80651F08;
    color.alpha = lbl_80651F0C;

    if (mode == 1) {
        a = *(Vec3*)((u8*)lbl_8023B5C0 + 0x00);
        b = *(Vec3*)((u8*)lbl_8023B5C0 + 0x0c);
    } else if (mode == 2) {
        fn_802114E0(matrix, fn_8011FE34(object));
        input = *(Vec3*)((u8*)lbl_8023B5C0 + 0x3c);
        fn_80211710(matrix, &input, &input);
        b = *(Vec3*)((u8*)lbl_8023B5C0 + 0x48);
        fn_80211710(matrix, &b, &b);
        fn_80211A6C(&b, &input, &a);
        base.z += lbl_806511B4;
        fn_80211A48(&base, &a, &base);
        a = *(Vec3*)((u8*)lbl_8023B5C0 + 0x18);
        b = *(Vec3*)((u8*)lbl_8023B5C0 + 0x24);
        effect = 0x33;
        life = 0x6a;
    } else if (mode == 3) {
        base.z += lbl_806511B8;
        a = *(Vec3*)((u8*)lbl_8023B5C0 + 0x00);
        b = *(Vec3*)((u8*)lbl_8023B5C0 + 0x0c);
        scale = lbl_806511BC;
        life = 0x5a;
    }

    switch (variant) {
    case 1: kind = 0x18; break;
    case 2: kind = 0x19; break;
    case 3: kind = 0x1a; break;
    default: kind = 0x1b; break;
    }

    if (mode == 1 || mode == 3) {
        float radius = mode == 1 ? lbl_806511C0 : lbl_806511C8;
        float z = mode == 1 ? origin->z + lbl_806511C4 : base.z;
        points[0] = (s16)(origin->x - radius);
        points[1] = (s16)(origin->y - radius);
        points[2] = (s16)z;
        points[3] = (s16)(origin->x - radius);
        points[4] = (s16)(origin->y + radius);
        points[5] = (s16)z;
        points[6] = (s16)(origin->x + radius);
        points[7] = (s16)(origin->y + radius);
        points[8] = (s16)z;
        points[9] = (s16)(origin->x + radius);
        points[10] = (s16)(origin->y - radius);
        points[11] = (s16)z;
    } else if (mode == 2) {
        static const s16 shape[12] = {50,100,0,-50,100,0,-50,100,100,50,100,100};
        int i;
        for (i = 0; i < 4; ++i) {
            input.x = shape[i * 3];
            input.y = shape[i * 3 + 1];
            input.z = shape[i * 3 + 2];
            fn_80211710(matrix, &input, &input);
            points[i * 3] = (s16)(origin->x + input.x);
            points[i * 3 + 1] = (s16)(origin->y + input.y);
            points[i * 3 + 2] = (s16)(origin->z + input.z);
        }
    } else {
        int i;
        for (i = 0; i < 4; ++i) {
            points[i * 3] = (s16)origin->x;
            points[i * 3 + 1] = (s16)origin->y;
            points[i * 3 + 2] = (s16)origin->z;
        }
    }
    fn_801CE980(-1, kind, effect, 0xff, points, life, variant);

    if (fn_80128258() != 0 || fn_80128130() != 0) {
        handle = fn_800453AC(0x5b, 0x68, lbl_8064D18C, -1, -1, -1, -1,
                             0x3e, &base, 1, 0, lbl_806511CC);
        fn_8020104C(0x39, handle, handle, 0, scale);
        fn_8020104C(0x9c, handle, handle, 6, lbl_806511D0);
        drawable = (void*)fn_80201BC8(fn_80201814(handle));
        kind = fn_801D3974(variant);
        c = *(Vec3*)((u8*)lbl_8023B5C0 + 0x30);
        fn_8012C62C(drawable, 15, &kind, &lbl_80651F10, &kind, 2);
        fn_8011FA8C(drawable, 0, 0x1000000);
        fn_8012CBE8(drawable, 15, &c, &b, &a, 1);
        fn_8012F58C(drawable, 15, 1, 0, 0x50, 0x100);
        if (mode == 2) {
            input = *(Vec3*)((u8*)lbl_8023B5C0 + 0x54);
            fn_8017A244(&input, &rotation, lbl_806511D4);
            fn_8012CDF0(drawable, 15, &rotation, 1);
            *(Vec4*)fn_8011FE34(drawable) = *(Vec4*)fn_8011FE34(object);
        } else if (mode == 3) {
            input = *(Vec3*)((u8*)lbl_8023B5C0 + 0x60);
            fn_8017A244(&input, &rotation, lbl_806511D8);
            fn_8012CDF0(drawable, 15, &rotation, 1);
        }
    }

    fn_80181F5C(&packet);
    packet.mode = 4;
    packet.type = 0x20;
    packet.id = fn_801D3A24(variant, 0x31);
    packet.word18 = 0;
    packet.word1C = 0;
    packet.flag14 = 4;
    if (mode == 1) color.alpha = 8;
    else if (mode == 3) color.alpha = (u16)-8;
    else if (mode == 2) {
        table78 = *(Vec3*)((u8*)lbl_8023B5C0 + 0x78);
        table6C = *(Vec3*)((u8*)lbl_8023B5C0 + 0x6c);
        fn_80211710(matrix, &table78, &table78);
        fn_80211A6C(&table78, &table6C, &a);
        fn_80179BC0(&a, &color);
    }
    if (fn_80148008(&base, &color, &packet, fn_80182014) != 0) {
        void* p = fn_80156938();
        fn_8017FE14(p, fn_8018EDE4);
        fn_8017FF1C(p, 4);
    }
}
