typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct ObjectInfo ObjectInfo;
typedef struct Entry80201814 Entry80201814;
typedef struct Object80201EB8 Object80201EB8;

extern int fn_800C1AB8(int);
extern void fn_800C1B18(ObjectInfo *, unsigned int, float);
extern Entry80201814 *fn_80201814(int);
extern int fn_80201EB8(Object80201EB8 *);
extern void *fn_80201B8C(unsigned char *);
extern void *fn_80201BC8(void *);
extern int fn_8012E114(unsigned char *, unsigned int, void *);
extern void fn_8012CBE8(unsigned char *, int, Vec3 *, Vec3 *, Vec3 *, int);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern float fn_80140E58(void);
extern float fn_8011F700(void *);
extern float fn_8011F788(void *, float);
extern void fn_8011F798(void *, float);
extern int lbl_8064D18C;
extern const Vec3 lbl_80239830;

void fn_800C1B50(int objectId, int kind, int flags, float amount, float value)
{
    void *object;
    void *model;
    int room;
    int index;
    Vec3 offset;
    Vec3 values;
    Vec3 position;
    Vec3 copyPosition;
    Vec3 copyOffset;
    Vec3 copyValues;
    float scale;

    object = fn_80201814(objectId);
    if (object != 0) {
        room = fn_80201EB8(object);
    } else {
        room = -1;
    }
    if (object != 0) {
        index = fn_800C1AB8(kind);
        fn_800C1B18(fn_80201B8C(object), index, value);
        if (room == lbl_8064D18C) {
            model = fn_80201BC8(object);
            position = lbl_80239830;
            fn_8012E114(model, kind, &position);
            values.x = values.y = values.z = value;
            offset.x = position.x > values.x ? -amount : amount;
            offset.y = position.y > values.y ? -amount : amount;
            offset.z = position.z > values.z ? -amount : amount;
            copyValues = values;
            copyOffset = offset;
            copyPosition = position;
            fn_8012CBE8(model, kind, &copyPosition, &copyOffset, &copyValues, 1);
            if (!(flags & 2) && kind == 15) {
                Vec3 unusedPosition;
                fn_8011F114(&unusedPosition, model);
                if (flags & 1) {
                    scale = fn_80140E58();
                } else {
                    scale = fn_8011F700(model);
                }
                scale = values.z * (scale * values.z);
                fn_8011F788(model, scale);
                fn_8011F798(model, scale);
            }
        }
    }
}
