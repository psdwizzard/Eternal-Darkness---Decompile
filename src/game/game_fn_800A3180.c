typedef unsigned short u16;

typedef struct Vec3_800A3180 {
    float x;
    float y;
    float z;
} Vec3_800A3180;

extern void* fn_80201B94(void*);
extern int fn_80201C48(void*);
extern void *fn_80201814(int);
extern u16 fn_800A30CC(void*);
extern void fn_802045AC(void*, Vec3_800A3180*);
extern void fn_80211A6C(Vec3_800A3180*, Vec3_800A3180*, Vec3_800A3180*);
extern int fn_800A4F44(Vec3_800A3180*, float);

int fn_800A3180(void* object, Vec3_800A3180* target)
{
    int result;
    int radius;
    void* handle;
    int linked;

    handle = fn_80201B94(object);
    linked = fn_80201C48(handle);
    result = 0;
    if (linked != 0 && fn_80201814(linked) != 0) {
        Vec3_800A3180 position;
        Vec3_800A3180 delta;

        radius = fn_800A30CC(object);
        fn_802045AC(object, &position);
        fn_80211A6C(&position, target, &delta);
        if (fn_800A4F44(&delta, radius) <= 0) {
            result = 1;
        }
    }
    return result;
}
