typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec4 { float x, y, z, w; } Vec4;
typedef float Matrix34[3][4];
typedef struct EffectVectors {
    Vec3 v00, v0C, v18, v24, v30, v3C;
    Vec3 v48, v54, v60, v6C, v78;
} EffectVectors;
typedef struct Color {
    u32 word;
    union { u16 bits; s16 value; } alpha;
} Color;
typedef struct Packet {
    u8 type, mode;
    u8 pad02[2];
    u16 id;
    u8 pad06[14];
    u8 flag14;
    u8 pad15[3];
    u32 word18, word1C;
    u8 payload20[0x70];
} Packet;

extern const u32 lbl_80651F08;
extern const u16 lbl_80651F0C;
extern EffectVectors lbl_8023B5C0;
extern int lbl_8064D18C;
extern u32 lbl_80651F10;
extern void* fn_8011FE34(void*);
extern void PSMTXQuat(void*, void*);
extern void PSMTXMultVec(void*, void*, void*);
extern void PSVECSubtract(void*, void*, void*);
extern void PSVECAdd(void*, void*, void*);
extern void fn_80179BC0(void*, void*);
extern void fn_8017A244(void*, void*, float);
extern void fn_801CE980(int, int, int, int, s16*, int, int);
extern int fn_80128258(void);
extern int fn_80128130(void);
extern int fn_800453AC(float, int, int, int, int, int, int, int, int, Vec3*, int, int);
extern void fn_8020104C(int, int, int, int, float);
extern void* fn_80201814(int);
extern void* fn_80201BC8(void*);
extern int fn_801D3974(int);
extern void fn_8012C62C();
extern void fn_8011FA8C();
extern void fn_8012CBE8(void*, int, Vec3, Vec3, Vec3, int);
extern void fn_8012F58C();
extern void fn_8012CDF0(void*, int, Vec4, int);
extern void fn_80181F5C(Packet*);
extern int fn_801D3A24(int, int);
extern void* fn_80148008(Vec3, Color*, Packet*, void*);
extern void* fn_80156938(void*);
extern void fn_8017FE14(void*, void*);
extern void fn_8017FF1C(void*, int);
extern void fn_80182014(void);
extern void fn_8018EDE4(void);

/* Mode-specific effect geometry and drawable setup. Keep independent scoped
 * vectors for transforms and the full 0x90-byte effect packet. The descriptor
 * halfword has both a raw template representation and a signed offset. */
void fn_801DDB84(Vec3* origin, int variant, int mode, void* object)
{
    EffectVectors* vectors;
    Vec3 base, a, b;
    Vec3 preset00, preset0C, preset18, preset24, preset30;
    Matrix34 matrix;
    s16 points[12];
    Packet packet;
    Color color;
    float scale;
    int effect;
    int life;
    int kind;
    volatile int setupResult;
    int setupKindA;
    u32 setupWord;
    int setupKindB;
    int handle;
    void* spawned;

    vectors = &lbl_8023B5C0;
    color.word = lbl_80651F08;
    color.alpha.bits = lbl_80651F0C;
    mode &= 0xff;
    preset00 = vectors->v00;
    preset0C = vectors->v0C;
    preset18 = vectors->v18;
    preset24 = vectors->v24;
    preset30 = vectors->v30;
    base = *origin;

    switch (mode) {
    case 1:
        a = preset00;
        b = preset0C;
        effect = 5;
        scale = 120.0f;
        life = 60;
        break;
    case 2: {
        Vec3 input = vectors->v3C;
        Vec3 second = vectors->v48;
        Vec3 delta;
        void* transform = fn_8011FE34(object);
        PSMTXQuat(matrix, transform);
        PSMTXMultVec(matrix, &input, &input);
        PSMTXMultVec(matrix, &second, &second);
        PSVECSubtract(&second, &input, &delta);
        base.z += 50.0f;
        PSVECAdd(&base, &delta, &base);
        a = preset18;
        b = preset24;
        effect = 0x33;
        scale = 120.0f;
        life = 0x6a;
        break;
    }
    case 3:
        base.z += 450.0f;
        a = preset00;
        b = preset0C;
        effect = 5;
        scale = 150.0f;
        life = 0x5a;
        break;
    }

    switch (variant) {
    case 1: kind = 0x18; break;
    case 2: kind = 0x19; break;
    case 3: kind = 0x1a; break;
    default: kind = 0x1b; break;
    }

    switch (mode) {
    case 1: {
        points[0] = (s16)(origin->x - 100.0f);
        points[1] = (s16)(origin->y - 100.0f);
        points[2] = (s16)(5.0f + origin->z);
        points[3] = (s16)(origin->x - 100.0f);
        points[4] = (s16)(100.0f + origin->y);
        points[5] = (s16)(5.0f + origin->z);
        points[6] = (s16)(100.0f + origin->x);
        points[7] = (s16)(100.0f + origin->y);
        points[8] = (s16)(5.0f + origin->z);
        points[9] = (s16)(100.0f + origin->x);
        points[10] = (s16)(origin->y - 100.0f);
        points[11] = (s16)(5.0f + origin->z);
        break;
    }
    case 2: {
        Vec3 input;
        int i;
        points[0] = 50;
        points[1] = 100;
        points[2] = 0;
        points[3] = -50;
        points[4] = 100;
        points[5] = 0;
        points[6] = -50;
        points[7] = 100;
        points[8] = 100;
        points[9] = 50;
        points[10] = 100;
        points[11] = 100;
        for (i = 0; i < 4; ++i) {
            input.x = points[i * 3];
            input.y = points[i * 3 + 1];
            input.z = points[i * 3 + 2];
            PSMTXMultVec(matrix, &input, &input);
            points[i * 3] = (s16)(origin->x + input.x);
            points[i * 3 + 1] = (s16)(origin->y + input.y);
            points[i * 3 + 2] = (s16)(origin->z + input.z);
        }
        break;
    }
    case 3: {
        float z = base.z;
        points[0] = (s16)(origin->x - 250.0f);
        points[1] = (s16)(origin->y - 250.0f);
        points[2] = (s16)z;
        points[3] = (s16)(origin->x - 250.0f);
        points[4] = (s16)(250.0f + origin->y);
        points[5] = (s16)z;
        points[6] = (s16)(250.0f + origin->x);
        points[7] = (s16)(250.0f + origin->y);
        points[8] = (s16)z;
        points[9] = (s16)(250.0f + origin->x);
        points[10] = (s16)(origin->y - 250.0f);
        points[11] = (s16)z;
        break;
    }
    }
    fn_801CE980(-1, kind, effect, 0xff, points, life, variant);

    if (fn_80128258() != 0 || fn_80128130() != 0) {
        void* drawable;
        Vec3 c;
        handle = fn_800453AC(0.0f, 0x5b, 0x68, lbl_8064D18C, -1, -1, -1, -1,
                             0x3e, &base, 1, 0);
        fn_8020104C(0x39, handle, handle, 0, scale);
        fn_8020104C(0x9c, handle, handle, 6, 1.0f);
        drawable = fn_80201BC8(fn_80201814(handle));
        setupKindA = setupKindB = setupResult = fn_801D3974(variant);
        setupWord = lbl_80651F10;
        c = preset30;
        fn_8012C62C(drawable, 15, &setupKindA, &setupWord, &setupKindB, 2);
        fn_8011FA8C(drawable, 0, 0x1000000);
        fn_8012CBE8(drawable, 15, c, b, a, 1);
        fn_8012F58C(drawable, 15, 1, 0, 0x50, 0x100);
        switch (mode) {
        case 2: {
            Vec3 input = vectors->v54;
            Vec4 rotation;
            fn_8017A244(&input, &rotation, 1.5707963705062866f);
            fn_8012CDF0(drawable, 15, rotation, 1);
            *(Vec4*)fn_8011FE34(drawable) = *(Vec4*)fn_8011FE34(object);
            break;
        }
        case 3: {
            Vec3 input = vectors->v60;
            Vec4 rotation;
            fn_8017A244(&input, &rotation, 3.1415927410125732f);
            fn_8012CDF0(drawable, 15, rotation, 1);
            break;
        }
        }
    }

    fn_80181F5C(&packet);
    packet.mode = 4;
    packet.id = fn_801D3A24(variant, 0x31);
    packet.type = 0x20;
    packet.word18 = 0;
    packet.word1C = 0;
    packet.flag14 = 4;
    switch (mode) {
    case 1:
        color.alpha.value = 8;
        break;
    case 2: {
        Vec3 table6C = vectors->v6C;
        Vec3 table78 = vectors->v78;
        Vec3 delta;
        PSMTXMultVec(matrix, &table78, &table78);
        PSVECSubtract(&table78, &table6C, &delta);
        fn_80179BC0(&delta, &color);
        break;
    }
    case 3:
        color.alpha.value = -8;
        break;
    }
    if ((spawned = fn_80148008(base, &color, &packet, fn_80182014)) != 0) {
        void* p = fn_80156938(spawned);
        fn_8017FE14(p, fn_8018EDE4);
        fn_8017FF1C(p, 4);
    }
}
