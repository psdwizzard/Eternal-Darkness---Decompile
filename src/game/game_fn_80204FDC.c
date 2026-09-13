typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern int lbl_8064D18C;
extern float lbl_806515B8;

extern void fn_80204A8C(void);
extern int fn_80201B54(void *object);
extern void *fn_80201C2C(void *object);
extern void *fn_80201BC8(void *object);
extern int fn_80205110(void *object);
extern void fn_8011F114(Vec3 *position, void *object);
extern int fn_8011F134(void *object);
extern void fn_80127F90(void *object, int id, Vec3 *position);
extern void *fn_802051A4(void *node);
extern int fn_80205134(void *node);
extern void *fn_80201814(int id);
extern int fn_80201B5C(void *object);
extern void fn_8011FB54(void *object, int value);
extern void fn_8011F0E8(void *object, Vec3 *position);
extern void fn_80205680(void *object, int owner, int value);
extern void fn_8020104C(int kind, int first, int second, int value, float delay);

void fn_80204FDC(void *object)
{
    Vec3 position;
    void *list;
    void *resource;
    int owner;
    int resource_id;
    int count;
    int i;

    fn_80204A8C();
    owner = fn_80201B54(object);
    list = fn_80201C2C(object);
    resource = fn_80201BC8(object);
    count = fn_80205110(object);

    fn_8011F114(&position, resource);
    resource_id = fn_8011F134(resource);
    if (resource_id == 0xFFFF) {
        fn_80127F90(resource, 0, &position);
    } else {
        fn_80127F90(resource, resource_id, &position);
    }

    for (i = 0; i < count; i++) {
        void *current;
        void *current_resource;
        int id;

        id = fn_80205134(fn_802051A4(list));
        current = fn_80201814(id);
        current_resource = fn_80201BC8(current);

        if (fn_80201B5C(current) != 79) {
            fn_8011FB54(current_resource, lbl_8064D18C);
            fn_8011F0E8(current_resource, &position);
            fn_80205680(current, owner, 30);
            fn_8020104C(73, id, id, 0, lbl_806515B8);
        }
    }
}
