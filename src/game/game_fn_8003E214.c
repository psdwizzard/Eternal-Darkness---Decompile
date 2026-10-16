typedef struct Vec3 { float x, y, z; } Vec3;

extern const float lbl_8064E294, lbl_8064E2DC, lbl_8064E2E0, lbl_8064E2E4;
extern void *fn_80201B94(void *), *fn_80201C48(void *);
extern void *fn_80201814(int), *fn_80201BC8(void *);
extern void fn_8011F114(Vec3 *, void *);
extern int fn_800BCE94(void *, int), fn_80066D04(void *, int);
extern void fn_80201D2C(void *, int), fn_80201D14(void *, int);
extern int fn_800359A0(void *, void *);
extern int fn_802045AC(void *, Vec3 *);
extern int fn_80179004(const float *, const float *);
extern unsigned int fn_80178E94(Vec3 *, Vec3 *);
extern int fn_80126070(void *);
extern void fn_8012FE10(void *, int, Vec3 *);
extern int fn_8012FF34(void *, Vec3 *, int, int);
extern void fn_801302BC(void *, int);
extern float fn_800CB444(void *, void *), fn_8011F6F8(void *);
extern int fn_8003E1F0(void *, Vec3 *, int, float);
extern float fn_8012B7D0(const void *, const void *), fn_8012B750(void *);
extern void fn_8017A12C(float *, float, float);
extern int fn_8003CD0C(void *, void *, void *), fn_8012AFC4(void *);
extern int fn_80129928(void *, Vec3 *);
extern float fn_8003C210(void *);
extern int fn_8003C280(void *);
extern unsigned char *fn_8012976C(void *, int, int, Vec3 *, float);
extern int fn_800BE260(void *, void *), fn_800BE2CC(void *, void *, Vec3 *);
extern void fn_800BE390(void *, void *), fn_8012B344(void *);

int fn_8003E214(void *owner, void *object, int unused, void *route,
                void *event, unsigned int flags, unsigned int mask)
{
    Vec3 target_position, other_position, route_position, position, facing_position;
    float angle;
    float difference, facing, scale, radius;
    void *link, *target, *target_object;
    int target_id;
    int distance, range;
    int result = 0;

    link = fn_80201B94(owner);
    fn_8011F114(&position, object);
    fn_800BCE94(owner, 10);
    if (fn_80066D04(owner, 0) == 0) {
        fn_80201D2C(owner, 1);
        fn_80201D14(owner, 1);
        return 1;
    }
    if (!(flags & mask)) fn_800359A0(owner, 0);
    if ((target_id = (int)fn_80201C48(link)) != 0 &&
        (target = fn_80201814(target_id)) != 0) {
        fn_802045AC(owner, &target_position);
        difference = position.z - target_position.z;
        if (difference < lbl_8064E294) difference = -difference;
        if (difference < lbl_8064E2DC)
            distance = fn_80179004(&position.x, &target_position.x);
        else
            distance = fn_80178E94(&position, &target_position);
        target_object = fn_80201BC8(target);
        if (target_object != 0 && fn_80126070(target_object) != 0) {
            fn_8012FE10(target_object, 0, &other_position);
            if (fn_8012FF34(object, &other_position, 4, 4) != 0)
                fn_801302BC(object, 60);
        }
        range = (int)fn_800CB444(owner, target);
        radius = fn_8011F6F8(object);
        radius *= lbl_8064E2E0;
        if (distance < range ||
            (distance < 550 && fn_8003E1F0(owner, &target_position, 1, radius) != 0)) {
            facing_position = target_position;
            facing = fn_8012B7D0(object, &facing_position);
            fn_8017A12C(&angle, fn_8012B750(object), facing);
            if (distance < range) {
                difference = angle;
                if (difference < lbl_8064E294) difference = -difference;
                if (difference <= lbl_8064E2E4) {
                    if (fn_8003CD0C(owner, object, event) == 0) {
                        fn_80201D2C(owner, 1);
                        fn_80201D14(owner, 1);
                    }
                    result = 1;
                    goto done;
                }
            }
            if (fn_8012AFC4(object) != 0) {
                fn_80129928(object, &target_position);
            } else {
                scale = fn_8003C210(owner);
                fn_8012976C(object, fn_8003C280(owner), 33, &target_position, scale);
            }
        } else if (fn_800BE260(owner, route) != 0) {
            fn_8012B344(object);
            result = 1;
            fn_80201D2C(owner, 1);
            fn_80201D14(owner, 1);
        } else if (fn_800BE2CC(owner, route, &route_position) != 0) {
            if (fn_80178E94(&position, &route_position) < 80U) {
                fn_800BE390(owner, route);
            } else if (fn_8012AFC4(object) != 0) {
                fn_80129928(object, &route_position);
            } else {
                scale = fn_8003C210(owner);
                fn_8012976C(object, fn_8003C280(owner), 33, &route_position, scale);
            }
        } else {
            result = 1;
            fn_80201D2C(owner, 1);
            fn_80201D14(owner, 1);
        }
    } else {
        fn_80201D2C(owner, 1);
        fn_80201D14(owner, 1);
        result = 1;
    }
done:
    return result;
}
