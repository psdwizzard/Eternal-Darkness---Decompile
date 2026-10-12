typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct EventData {
    unsigned char pad[0x8C];
    void *data;
} EventData;

extern void fn_8011F114(Vec3 *);
extern int fn_80201B54(void *);
extern void fn_80201B94(void *);
extern void fn_80201C48(void);
extern void *fn_80201814(void);
extern int fn_800359A0(void *, int);
extern void fn_802045AC(void *, Vec3 *);
extern int fn_80179064(int, int, int, int);
extern float fn_800CB444(void *, void *);
extern int fn_80204578(void *, Vec3 *);
extern EventData *fn_80201B8C(void *);
extern int fn_8012AFC4(void *);
extern void fn_8012B344(void *);
extern void fn_800E33B8(int, void *, EventData *);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void *fn_80201B3C(void);
extern void fn_80038308(void *, int, void *);

int fn_800E34B4(void *object, void *resource)
{
    Vec3 action_pos;
    Vec3 object_pos;
    int temporary;
    register int object_id;
    register int mode;
    register int distance;


    fn_8011F114(&action_pos);
    object_id = fn_80201B54(object);
    if (fn_800359A0(object, 0) != 0) {
        fn_80201B94(object);
        fn_80201C48();
        mode = (int)fn_80201814();
        fn_802045AC(object, &object_pos);
        distance = fn_80179064((int)action_pos.x, (int)action_pos.y,
                               (int)object_pos.x, (int)object_pos.y);
        if (distance < (int)fn_800CB444(object, (void *)mode) &&
            (unsigned char)fn_80204578(object, &object_pos) != 0) {
            EventData *data = fn_80201B8C(object)->data;
            if (fn_8012AFC4(resource) != 0)
                fn_8012B344(resource);
            fn_800E33B8(object_id, resource, data);
        } else {
            fn_80201D2C(object, 3);
            fn_80201D14(object, 1);
            return 1;
        }
    } else {
        fn_80038308(fn_80201B3C(), 0, &temporary);
    }
    return 0;
}
