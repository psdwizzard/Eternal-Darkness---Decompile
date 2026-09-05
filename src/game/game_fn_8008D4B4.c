typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern void fn_8011F114();
extern int fn_80201B54();
extern void* fn_80201B94();
extern void *fn_80201B8C();
extern int fn_80201B44();
extern void *fn_80201814();
#define FN_80201E78_RETURN void
#define FN_80201E78_PARAMETERS Vec3*, void*
extern FN_80201E78_RETURN fn_80201E78(FN_80201E78_PARAMETERS);extern int fn_80204180(void*, void*);
extern unsigned char fn_80204434(void*, Vec3*, int, float);
extern int fn_8008D31C(void*, void*, int, void*, void*, int, Vec3*);
extern Vec3 lbl_80239630;
extern float lbl_8064EC20;

#pragma optimization_level 1
int fn_8008D4B4(void* object, void* resource)
{
    Vec3 source;
    Vec3 position;
    Vec3 mode_position;
    Vec3 fallback;
    void* runtime;
    void* data;
    int result = 0;
    void* target;
    int value;
    void* mode;
    Vec3* selected;
    int distance;

    fn_8011F114(&position);
    target = ((void*)fn_80201B54(object));
    runtime = fn_80201B94(object);
    data = fn_80201B8C(object);
    value = fn_80201B44();
    mode = fn_80201814();
    if (mode != 0) {
        fn_80201E78(&mode_position, mode);
        selected = &mode_position;
    } else {
        fallback = lbl_80239630;
        selected = &fallback;
    }
    source = *selected;
    distance = fn_80204180(object, mode);
    if (mode != 0 && distance < 155 &&
        fn_80204434(resource, &source, 0, lbl_8064EC20)) {
        result = fn_8008D31C(object, target, value, data, resource, 5, &position);
    }
    (void)runtime;
    return result;
}
#pragma optimization_level reset
