typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;

typedef f32 Matrix[3][4];

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;

typedef struct Matrix34 {
    f32 m[3][4];
} Matrix34;

typedef struct TransformOutput {
    s32 index;
    s32 marker;
    Vec3 first;
    Vec3 second;
    f32 trailing;
    u8 enabled;
} TransformOutput;

typedef struct Resource {
    u8 pad[0xE];
    u16 id;
} Resource;

typedef struct Entry {
    u8 pad[4];
    Resource* resource;
} Entry;

typedef struct Object {
    u8 pad[0x240];
    Entry** entries;
} Object;

typedef struct RuntimeEntry {
    u8 pad[0x48];
    void* value;
} RuntimeEntry;

typedef struct ObjectRuntimeLayout {
    u8 pad[0x160];
    RuntimeEntry* runtime;
} ObjectRuntimeLayout;

extern f32 lbl_806501D8;
extern f32 lbl_806501DC;
extern const double lbl_80650208;

extern void fn_80125ECC(void*);
extern int fn_8012FDA0(Object*, int);
extern void fn_8011F3B4(void*, Matrix, int, int);
extern void fn_8011F304(TransformOutput*, Matrix, int);
extern void fn_80211AAC(const Vec3*, Vec3*);
extern void fn_80211B64(const Vec3*, const Vec3*, Vec3*);
extern f32 fn_80211B08(const Vec3*);
extern u32 fn_802110A8(void*, void*);
extern void fn_8017AD00(const Matrix34*, const Vec3*, Vec3*);
extern void fn_8017A244(const Vec3*, Vec4*, f32);
extern void fn_8012CEA4(u8*, int, Vec4*);
extern f32 fn_8017A5A8(const Vec4*, const Vec4*, f32);
extern void fn_8012CF08(u8*, int, Vec4, Vec4, int, int, f32);
extern void fn_8012F58C(void*, unsigned int, unsigned int, u16, u16, u16);

int fn_8012EDB0(void* context, s32 index, Vec3* position, f32 angle,
                f32 limit)
{
    ObjectRuntimeLayout* runtime_layout = (ObjectRuntimeLayout*)context;
    TransformOutput transform;
    Matrix34 matrix;
    Matrix34 inverse;
    Vec4 current;
    Vec3 cross;
    Vec3 axis;
    Vec4 desired;
    Entry* entry;
    Resource* resource;
    s32 transform_id;
    f32 scale;

    fn_80125ECC(context);
    entry = ((Object*)context)->entries[index];
    if (entry != 0) {
        resource = entry->resource;
        runtime_layout->runtime[resource->id].value = 0;

        transform_id = fn_8012FDA0((Object*)context, index);
        transform.index = index;
        transform.marker = -1;
        transform.first.x = lbl_806501D8;
        transform.first.y = lbl_806501D8;
        transform.first.z = lbl_806501D8;
        transform.second.x = lbl_806501DC;
        transform.second.y = lbl_806501D8;
        transform.second.z = lbl_806501D8;
        transform.trailing = transform.second.x;

        fn_8011F3B4(context, matrix.m, transform_id, 9);
        fn_8011F304(&transform, matrix.m, 9);

        fn_80211AAC(position, position);
        fn_80211B64(&transform.second, position, &cross);
        if (fn_80211B08(&cross) > lbl_80650208) {
            fn_802110A8(&matrix, &inverse);
            fn_8017AD00(&inverse, &cross, &axis);
            fn_8017A244(&axis, &desired, angle);
            fn_8012CEA4((u8*)context, index, &current);
            scale = fn_8017A5A8(&current, &desired, limit);
            fn_8012CF08((u8*)context, index, current, desired, 0, 0, scale);
            fn_8012F58C(context, index, 3, 0, 0, 0x84);
        }
    }
    return 0;
}
