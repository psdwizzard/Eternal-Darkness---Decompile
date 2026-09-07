typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Packet {
    u8 type, mode;
    u16 id;
    u8 pad04[16];
    u32 word14, word18;
} Packet;

extern u32 lbl_80651F08;
extern u16 lbl_80651F0C;
extern u32 lbl_8023B5C0[];
extern float lbl_806511B0, lbl_806511B4, lbl_806511B8, lbl_806511BC;
extern int lbl_8064D18C;
extern void* fn_8011FE34(void*);
extern void fn_802114E0(void*, void*);
extern void fn_80211710(void*, void*, void*);
extern void fn_80211A6C(void*, void*, void*);
extern void fn_80211A48(void*, void*, void*);
extern void fn_80179BC0(void*, void*);
extern void fn_8017A244(void*, void*, float);
extern void fn_801CE980(int, int, int, int, int, s16*);
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
extern void* fn_80148008(Vec3*, u32*, Packet*, void*);
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
    Vec3 a, b, c, d;
    s16 points[12];
    Packet packet;
    u32 color = lbl_80651F08;
    u16 alpha = lbl_80651F0C;
    float scale = lbl_806511B0;
    int effect = 5;
    int life = 60;
    int kind;
    int handle;
    void* drawable;

    if (mode == 2) {
        fn_802114E0(&d, fn_8011FE34(object));
        fn_80211710(&d, (u8*)lbl_8023B5C0 + 0x3c, (u8*)lbl_8023B5C0 + 0x3c);
        fn_80211A6C((u8*)lbl_8023B5C0 + 0x48, (u8*)lbl_8023B5C0 + 0x3c, &a);
        base.z += lbl_806511B4;
        fn_80211A48(&base, &a, &base);
        effect = 0x33;
        life = 0x6a;
    } else if (mode == 3) {
        base.z += lbl_806511B8;
        scale = lbl_806511BC;
        life = 0x5a;
    }

    switch (variant) {
    case 1: kind = 0x18; break;
    case 2: kind = 0x19; break;
    case 3: kind = 0x1a; break;
    default: kind = 0x1b; break;
    }

    if (mode == 2) {
        static const s16 shape[12] = {50,100,0,-50,100,0,-50,100,100,50,100,100};
        int i;
        for (i = 0; i < 12; ++i) points[i] = shape[i];
    } else {
        int i;
        for (i = 0; i < 4; ++i) {
            points[i * 3] = (s16)origin->x;
            points[i * 3 + 1] = (s16)origin->y;
            points[i * 3 + 2] = (s16)origin->z;
        }
    }
    fn_801CE980(-1, kind, effect, 0xff, life, points);

    if (fn_80128258() != 0 || fn_80128130() != 0) {
        handle = fn_800453AC(0x5b, 0x68, lbl_8064D18C, -1, -1, -1, -1,
                             0x3e, &base, 1, 0, lbl_806511B0);
        fn_8020104C(0x39, handle, handle, 0, scale);
        fn_8020104C(0x9c, handle, handle, 6, lbl_806511B0);
        drawable = (void*)fn_80201BC8(fn_80201814(handle));
        fn_8012F58C(drawable, 15, 1, 0, 0x50, 0x100);
    }

    fn_80181F5C(&packet);
    packet.mode = 4;
    packet.type = 0x20;
    packet.id = fn_801D3A24(variant, 0x31);
    packet.word14 = 0;
    packet.word18 = 0;
    if (mode == 1) alpha = 8;
    else if (mode == 3) alpha = (u16)-8;
    else if (mode == 2) {
        fn_80211710(&d, (u8*)lbl_8023B5C0 + 0x78, (u8*)lbl_8023B5C0 + 0x78);
        fn_80211A6C((u8*)lbl_8023B5C0 + 0x78, (u8*)lbl_8023B5C0 + 0x6c, &a);
        fn_80179BC0(&a, &color);
    }
    if (fn_80148008(&base, &color, &packet, fn_80182014) != 0) {
        void* p = fn_80156938();
        fn_8017FE14(p, fn_8018EDE4);
        fn_8017FF1C(p, 4);
    }
    (void)alpha;
}
