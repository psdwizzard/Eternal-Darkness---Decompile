typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;
typedef union PackedVec3 {
    Vec3 vector;
    s32 first_word;
} PackedVec3;
typedef struct Hit8007D4D8 {
    u8 pad00[8];
    Vec3 position;
    u8 pad14[0x14];
} Hit8007D4D8;

extern const double lbl_8064E9D8;
extern const float lbl_8064E9FC;
extern u8 lbl_802FC5BC[];

extern s32 fn_801A7498(void *);
extern void *fn_8004914C(void *);
extern void *fn_80201B9C();
extern void *fn_80204844(void *, s32);
extern s32 fn_8011F6A4(void *, s32, s32, s32, void *, s32);
extern void *fn_8006D444(void *);
extern int fn_801AC9F4(s32, s32, Vec3 *, s32);
extern unsigned int fn_800FBFB0(void);
extern void fn_8014D478(void *, Vec3 *, Vec3 *, s32, s32, void *, s32);
extern s32 fn_801A9EF4(s32, s32);
extern void *fn_80201814(void *);
extern Vec3 *fn_80201BC8(void *);
extern float fn_8012B750(void *);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern unsigned long long fn_8020123C();

s32 fn_8007D4D8(void *unused, void *handle)
{
    s32 owner_id;
    void *object;
    void *resource;
    u8 *state;
    u8 *slot;
    s32 result;
    Hit8007D4D8 hit;
    Vec3 velocity;
    PackedVec3 direction;
    s32 packed;
    Vec3 *target;

    (void)unused;
    if (handle != 0) {
        owner_id = fn_801A7498(handle);
        object = fn_8004914C(handle);
        if (object != 0) {
            resource = fn_80204844(fn_80201B9C(object), 0x20);
            result = fn_8011F6A4(object, 2, -1, -1, &hit, 1);
            state = fn_8006D444(resource);
            slot = *(u8 **)(state + 0xC4);
            if (result != -1) {
                fn_801AC9F4(0x176, 0x64, &hit.position, 2);
                velocity.x = (float)(8 - (int)(fn_800FBFB0() & 0xF));
                velocity.y = (float)(8 - (int)(fn_800FBFB0() & 0xF));
                velocity.z = lbl_8064E9FC;
                fn_8014D478((void *)0, &hit.position, &velocity, 0x10, 4,
                            lbl_802FC5BC + 0x18, 3);
                fn_801AC9F4((u16)fn_801A9EF4(0x115, 0x117), 0x6E,
                            &hit.position, 2);
            }
            target = fn_80201BC8(fn_80201814(*(void **)(state + 0x38)));
            *(float *)(slot + 0x80) = fn_8012B750(target);
            fn_8011F114(&direction.vector, target);
            packed = direction.first_word;
            *(Vec3 *)(slot + 0x74) = direction.vector;
            fn_8020123C(8, 0, owner_id, 0, packed);
        }
    }
    return 1;
}
