typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Object800A1B90 {
    unsigned char pad00[0xC];
    float radius;
} Object800A1B90;

#define FN_80201E78_RETURN Vec3
#define FN_80201E78_PARAMETERS void*
extern FN_80201E78_RETURN fn_80201E78(FN_80201E78_PARAMETERS);extern void PSVECSubtract();
extern int fn_800A4F44(Vec3*, float);
extern int fn_80201B54();
extern unsigned long long fn_8020123C();

int fn_800A1B90(Object800A1B90* object, int value, void* entity)
{
    int result = 0;
    Vec3 delta;

    if (entity != 0) {
        PSVECSubtract(fn_80201E78(entity), object, &delta);
        result = fn_800A4F44(&delta, object->radius) > 0;
        if (result) {
            fn_8020123C(0xA5, value, ((void*)fn_80201B54(entity)), object);
        }
    }
    return result;
}
