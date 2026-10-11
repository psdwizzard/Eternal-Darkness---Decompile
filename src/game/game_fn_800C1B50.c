typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern int fn_800C1AB8(int);
extern void fn_800C1B18(void *, unsigned int, float);
extern void *fn_80201814(int);
extern int fn_80201EB8(void *);
extern void *fn_80201B8C(void *);
extern void *fn_80201BC8(void *);
extern int fn_8012E114(void *, int, Vec3 *);
extern void fn_8012CBE8(void *, int, Vec3 *, Vec3 *, Vec3 *, int);
extern void fn_8011F114(Vec3 *, void *);
extern float fn_80140E58(void);
extern float fn_8011F700(void *);
extern void fn_8011F788(void *, float);
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
            values.z = value;
            values.y = value;
            values.x = value;
            offset.x = position.x > (float)(double)value ? -amount : amount;
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
