typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;

typedef struct Vec3 { f32 x, y, z; } Vec3;
typedef struct Color { s32 r, g, b; } Color;

/* Per-TU pool of aggregate local initializers. */
typedef struct InitPool {
    u8 pad[0x4C];
    Vec3 offset;     /* 0x4C */
    Color color;     /* 0x58 */
    Vec3 scaleB;     /* 0x64 */
    Vec3 scaleA;     /* 0x70 */
} InitPool;

extern const InitPool lbl_802398B8;
extern s32 lbl_8064CAA0;
extern s32 lbl_8064CAA4;
extern s32 lbl_8064D5A8;
extern f32 lbl_8064F2B0;
extern s32 lbl_80651A9C;
extern s32 lbl_80651AA0;

extern int rand(void);
extern int fn_80128408(void);
extern int fn_800453AC(f32, int, int, int, int, int, int, int, int, Vec3 *, int, int);
extern void *fn_80201814(void);
extern void *fn_80201BC8(void *);
extern void fn_8012CBE8(void *, int, Color *, Vec3 *, Vec3 *, int);
extern void *fn_8012C62C(void *, int, s32 *, s32 *, s32 *, int);
extern void fn_8011F0E8(void *, Vec3 *);
extern void fn_80179AEC(void *, Vec3 *);
extern void fn_80179A18(Vec3 *);
extern void fn_801798DC(Vec3 *, f32);
extern int fn_801261F4(void *);
extern void fn_8011F7BC(void *, Vec3 *);
extern void fn_8012D0D0(void *);

/* Adds a random offset in [-2^(bits-1)+1, 2^(bits-1)] to each axis. */
static inline void AddJitter(Vec3 *v, u8 bits)
{
    if (bits != 0) {
        v->x += (f32)((1 << (bits - 1)) - (((1 << bits) - 1) & rand()));
        v->y += (f32)((1 << (bits - 1)) - (((1 << bits) - 1) & rand()));
        v->z += (f32)((1 << (bits - 1)) - (((1 << bits) - 1) & rand()));
    }
}

void *fn_800CEC24(int base, u8 range, Vec3 *position, void *source, u8 jitterBits,
                  s32 *colorA, f32 angle, f32 divisor, f32 size)
{
    const InitPool *pool = &lbl_802398B8;
    Vec3 offset = pool->offset;
    void *result = 0;
    void *object;
    int count;

    count = fn_80128408() - 0x18;
    if (lbl_8064D5A8 != lbl_8064CAA4) {
        lbl_8064CAA4 = lbl_8064D5A8;
        lbl_8064CAA0 = 0;
    }
    if (count > 0 && lbl_8064CAA0 < 6) {
        fn_800453AC(0.0f, 0x3A, base + rand() % range, -1, -1,
                    -1, -1, -1, 0x23, position, 5, 0);
        result = fn_80201814();
        lbl_8064CAA0++;
        object = fn_80201BC8(result);
        if (object != 0) {
            f32 s;
            Color color;
            Vec3 b;
            Vec3 scaleB;
            Vec3 a;
            Vec3 scaleA;
            s32 c1;
            s32 c2;
            s32 c3;

            if (divisor != lbl_8064F2B0) {
                s = size + (f32)(rand() & 3) / divisor;
            } else {
                s = size;
            }
            scaleA = pool->scaleA;
            scaleA.x = s;
            scaleA.y = s;
            scaleA.z = s;
            a = scaleA;
            scaleB = pool->scaleB;
            scaleB.x = s;
            scaleB.y = s;
            scaleB.z = s;
            b = scaleB;
            color = pool->color;
            fn_8012CBE8(object, 0xF, &color, &b, &a, 0);
            c3 = lbl_80651AA0;
            c2 = lbl_80651A9C;
            c1 = *colorA;
            fn_8012C62C(object, 0xF, &c1, &c2, &c3, 2);
            fn_8011F0E8(object, position);
            if (source != 0) {
                fn_80179AEC(source, &offset);
            }
            fn_80179A18(&offset);
            fn_801798DC(&offset, angle);
            AddJitter(&offset, jitterBits);
            fn_801261F4(object);
            fn_8011F7BC(object, &offset);
            fn_8012D0D0(object);
        }
    }
    return result;
}
