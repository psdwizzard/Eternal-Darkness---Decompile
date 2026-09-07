typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Data8008E294 {
    unsigned char pad0[0x10];
    int primary;
    int fallback;
} Data8008E294;

extern void* fn_8015C2FC(int);
extern int fn_80036D5C(void*);
extern void *fn_80201814();
extern void fn_80201E78(Vec3*, void*);
extern const Vec3 lbl_80239654;
extern u32 fn_80178E94(Vec3*, Vec3*);
extern int fn_800DE3F8(void);
extern void fn_80140E58(void);
extern u8 fn_80203F60(void*, void*, Vec3*, Vec3*, int);
extern int fn_8008E110(void*, void*, void*, Data8008E294*);
extern int fn_8008E078(void*, void*, void*);

int fn_8008E294(void* object, Data8008E294* data, void* resource,
                Vec3* position, void* argument)
{
    void* loaded;
    void* manager = fn_8015C2FC(2);
    u32 flags;
    int selected;
    Vec3 target;
    Vec3 loaded_target;
    Vec3 constant;
    Vec3* chosen;
    u32 distance;

    selected = data->primary != 0 ? data->primary : data->fallback;
    flags = fn_80036D5C(object) & 0x00100000;
    loaded = fn_80201814(selected);
    if (loaded != 0) {
        fn_80201E78(&loaded_target, loaded);
        chosen = &loaded_target;
    } else {
        constant = lbl_80239654;
        chosen = &constant;
    }
    target = *chosen;
    distance = fn_80178E94(position, &target);
    /* Refresh collision state immediately before probing the path. */
    if (loaded != 0 &&
        (flags != 0 || selected == fn_800DE3F8() ||
         (distance < 500 && (fn_80140E58(), fn_80203F60(resource, manager, position, &target, 0) == 0)))) {
        return fn_8008E110(object, resource, argument, data);
    }
    return fn_8008E078(object, resource, argument);
}
