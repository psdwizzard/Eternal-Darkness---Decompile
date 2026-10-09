typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Coord2 {
    short x, y;
} Coord2;

typedef struct Effect {
    u8 count;
    u8 pad01[5];
    u16 duration;
    u8 pad08[0x10];
    u32 resource;
    u8 pad1C[0x74];
    void (*update)(void);
    void* owner;
    Vec3 position;
    u8 config[6];
    u8 variant;
} Effect;

typedef struct Bounds {
    Vec3 a;
    Vec3 b;
    Vec3 c;
} Bounds;

extern Vec3 lbl_8023A750;
extern u8 lbl_802FC5BC[];
extern void* lbl_8064C4E0;
extern float lbl_8064CF04;
extern const float lbl_806504F8;
extern const float lbl_806504FC;
extern const float lbl_80650500;
extern const float lbl_80650518;

extern void fn_8019BCEC(Effect*);
extern void fn_8019BD44(void);
extern void* memset(void*, int, u32);
extern void* memcpy(void*, const void*, u32);
extern int fn_801E79FC(void*, int);
extern void fn_80147EC4(void*);
extern void fn_8019CE7C(void*, Vec3*, Bounds*, Vec3*);
extern void fn_8019CE34(void*, u8);
extern Coord2* fn_8017FDA8(void*, u8);
extern int fn_800FBFB0(void);

void* fn_8014E6BC(Vec3* position, int count, u32* resource, u16 spread,
                  u16 duration, int flags)
{
    Vec3 offset;
    Bounds bounds;
    Effect effect;
    u8 n;
    Coord2* point;

    offset = lbl_8023A750;
    if (!(flags & 4) && lbl_8064CF04 >= lbl_806504F8) {
        return 0;
    }

    fn_8019BCEC(&effect);
    effect.update = fn_8019BD44;
    effect.position = *position;
    effect.owner = 0;
    effect.variant = 4;
    memset(effect.config, 0, 6);

    if (lbl_8064CF04 >= lbl_806504FC) {
        n = count;
        if ((u8)count >> 2 > 0) {
            n = (u8)count >> 2;
        }
    } else if (lbl_8064CF04 >= lbl_80650500) {
        n = count;
        if ((u8)count >> 1 > 0) {
            n = (u8)count >> 1;
        }
    } else {
        n = count;
    }
    effect.count = n;

    effect.resource = *resource;
    if (duration > 50) {
        effect.duration = duration;
    }
    if (fn_801E79FC(lbl_8064C4E0, 0x2ED)) {
        effect.resource = *(u32*)(lbl_802FC5BC + 0x24);
    }
    fn_80147EC4(&effect);

    if (effect.owner != 0) {
        int i;
        u8 total = effect.count;

        memcpy(&bounds.a, position, sizeof(Vec3));
        memcpy(&bounds.b, position, sizeof(Vec3));
        memcpy(&bounds.c, position, sizeof(Vec3));
        bounds.a.x -= lbl_80650518;
        bounds.a.y -= lbl_80650518;
        bounds.b.x += lbl_80650518;
        bounds.b.y -= lbl_80650518;
        bounds.c.y += lbl_80650518;
        fn_8019CE7C(effect.owner, position, &bounds, &offset);

        for (i = 0; (u8)i < total; i++) {
            u8 index = i;

            fn_8019CE34(effect.owner, index);
            point = fn_8017FDA8(effect.owner, index);
            if (point != 0) {
                point->x = position->x + spread - fn_800FBFB0() % (spread * 2);
                point->y = position->y + spread - fn_800FBFB0() % (spread * 2);
            }
        }
    }
    return effect.owner;
}
