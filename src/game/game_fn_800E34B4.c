typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct EventData EventData;
typedef struct Entry80201814 Entry80201814;
typedef struct Entry80201B3C Entry80201B3C;
typedef struct Object80201C48 Object80201C48;
typedef struct Object80201D2C Object80201D2C;
typedef struct Object80201D14 Object80201D14;

typedef struct ObjectInfo {
    unsigned char pad[0x8C];
    EventData *data;
} ObjectInfo;

extern void fn_8011F114(Vec3 *, Vec3 *);
extern int fn_80201B54(int *);
extern void *fn_80201B94(unsigned char *);
extern void *fn_80201C48(Object80201C48 *);
extern Entry80201814 *fn_80201814(int);
extern int fn_800359A0(void *, void *);
extern int fn_802045AC(void *, Vec3 *);
extern int fn_80179064(int, int, int, int);
extern float fn_800CB444(void *, void *);
extern unsigned char fn_80204578(void *, const Vec3 *);
extern void *fn_80201B8C(unsigned char *);
extern int fn_8012AFC4(void *);
extern void fn_8012B344(void *);
extern void fn_800E33B8(int, void *, EventData *);
extern void fn_80201D2C(Object80201D2C *, int);
extern void fn_80201D14(Object80201D14 *, unsigned char);
extern Entry80201B3C *fn_80201B3C(void);
extern int fn_80038308(void *, int, short *);

int fn_800E34B4(void *object, void *resource)
{
    Vec3 action_pos;
    Vec3 object_pos;
    short temporary;
    register int object_id;
    register void *target;
    register int distance;

    fn_8011F114(&action_pos, resource);
    object_id = fn_80201B54(object);
    if (fn_800359A0(object, 0) != 0) {
        target = fn_80201814((int)fn_80201C48(fn_80201B94(object)));
        fn_802045AC(object, &object_pos);
        distance = fn_80179064((int)action_pos.x, (int)action_pos.y,
                               (int)object_pos.x, (int)object_pos.y);
        if (distance < (int)fn_800CB444(object, target) &&
            (unsigned char)fn_80204578(object, &object_pos) != 0) {
            EventData *data = ((ObjectInfo *)fn_80201B8C(object))->data;
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
