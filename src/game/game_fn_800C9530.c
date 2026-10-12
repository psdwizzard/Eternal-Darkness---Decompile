typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Vec4 {
    float x, y, z, w;
} Vec4;

typedef struct PendingEntry {
    int object_id;
    void *target;
} PendingEntry;

extern PendingEntry lbl_80325450[];
extern int lbl_8064CAB0;
extern Vec3 lbl_80248910;
extern float lbl_8064F298;

extern void *fn_80201814(int id);
extern void *fn_80201BC8(void *object);
extern int fn_8015C4A4(void *target, int selector);
extern int fn_80158B20(int index, int key, Vec3 *position, Vec3 *axis, float *angle);
extern void fn_8017A244(const Vec3 *axis, Vec4 *rotation, float angle);
extern void fn_8017A34C(const Vec4 *left, const Vec4 *right, Vec4 *output);
extern void *fn_8011FE34(void *object);
extern void fn_8011F0E8(Vec3 *destination, Vec3 *source);
extern void fn_801D13D8(int id, int notify);
extern void fn_800C94FC(void);

void fn_800C9530(void)
{
    Vec3 axis;
    Vec3 position;
    Vec4 base_rotation;
    Vec4 rotation;
    float angle;
    PendingEntry *entry;
    void *model;
    int i;
    int id;
    void *target;
    void *object;
    int index;

    for (i = 0; i < lbl_8064CAB0; i++) {
        entry = &lbl_80325450[i];
        id = entry->object_id;
        target = entry->target;
        object = fn_80201814(id);

        if (object != 0) {
            model = fn_80201BC8(object);
            index = fn_8015C4A4(target, 2);

            if (index != -1 && fn_80158B20(index, 2, &position, &axis, &angle) != 0) {
                axis.x = -axis.x;
                axis.y = -axis.y;
                axis.z = -axis.z;
                fn_8017A244(&axis, &rotation, angle);
                fn_8017A244(&lbl_80248910, &base_rotation, lbl_8064F298);
                fn_8017A34C(&rotation, &base_rotation, fn_8011FE34(model));
                fn_8011F0E8(model, &position);
                fn_801D13D8(id, 1);
            }
        }
    }
    fn_800C94FC();
}
