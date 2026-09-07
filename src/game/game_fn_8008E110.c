typedef unsigned long long u64;

typedef struct Data8008E110 {
    unsigned char pad0[0xc];
    int result;
    int primary;
    int fallback;
} Data8008E110;

extern int fn_80201B54();
extern void *fn_80201814();
extern void *fn_801294DC(void *, int, int, int);
extern unsigned long long fn_8020123C();
extern int fn_800DE3F8(void);
extern void* fn_800CCF60(void*, int, int, void*, int, int, int, int, int, int,
                         int);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern int fn_8008E078(void*, void*, void*);

int fn_8008E110(void* object, void* resource, void* argument,
                Data8008E110* data)
{
    int selected;
    void* loaded;
    void* created = 0;
    int object_id;
    void* spawned;

    selected = data->primary != 0 ? data->primary : data->fallback;
    object_id = fn_80201B54(object);
    loaded = fn_80201814(selected);
    if (loaded != 0) {
        created = fn_801294DC(resource, 134, 33, 6);
    }
    if (loaded != 0 && created != 0) {
        u64 state = fn_8020123C(125, object_id, selected, 1);
        if ((unsigned int)(state & 0xFFFFFFFF) == 1) {
            int current = fn_800DE3F8();
            if (current == selected) {
                spawned = fn_800CCF60(loaded, 0, 0, object, 0, 0, 0, 0, 10,
                                      20, 0);
            } else {
                spawned = fn_800CCF60(loaded, 20, 0, object, 0, 0, 0, 0, 10,
                                      20, 0);
            }
            if (spawned != 0) {
                data->result = fn_80201B54(spawned);
            }
            fn_80201D2C(object, 56);
            fn_80201D14(object, 1);
            return 1;
        }
        fn_8008E078(object, resource, argument);
    }
    return 0;
}
