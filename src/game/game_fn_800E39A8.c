typedef signed int s32;
typedef unsigned int u32;
typedef float f32;

typedef struct Vec3 {
    f32 x, y, z;
} Vec3;

extern f32 lbl_8064F680;
extern f32 lbl_8064F684;
extern f32 lbl_8064F688;
extern f32 lbl_8064F68C;

extern void *fn_80201B94(void *);
extern void fn_8011F114(Vec3 *, void *);
extern int fn_80066D04(void *, int);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_800359A0(void *, int);
extern int fn_80201C48(void *);
extern void *fn_80201814();
extern void fn_802045AC(void *, Vec3 *);
extern u32 fn_80178E94(Vec3 *, Vec3 *);
extern f32 fn_800CB444(void *, void *);
extern f32 fn_8011F6F8(void *);
extern int fn_8003E1F0(void *, Vec3 *, int, f32);
extern f32 fn_8012B7D0(void *, Vec3);
extern f32 fn_8012B750(void *);
extern void fn_8017A12C(f32 *, f32, f32);
extern void fn_800E33B8(void *, void *, void *);
extern int fn_8012AFC4(void *);
extern void fn_80129928(void *, Vec3 *);
extern void fn_8012976C(void *, int, int, Vec3 *, f32);
extern int fn_800BE2CC(void *, void *, Vec3 *);
extern void fn_800BE390(void *, void *);

int fn_800E39A8(void *self, void *actor, void *arg2, void *arg3, int arg4, int arg5, int arg6) {
    f32 diff;
    Vec3 actorPos;
    Vec3 selfPos;
    Vec3 target;
    void *object;
    void *other;
    s32 dist;
    s32 range;
    f32 speed;
    f32 heading;
    int result;

    result = 0;
    object = fn_80201B94(self);
    fn_8011F114(&selfPos, actor);
    if (fn_80066D04(self, 0) == 0) {
        fn_80201D2C(self, 1);
        fn_80201D14(self, 1);
        return 1;
    }
    if ((arg5 & arg6) == 0) {
        fn_800359A0(self, 0);
    }
    if (fn_80201C48(object) != 0 && (other = fn_80201814()) != 0) {
        fn_802045AC(self, &actorPos);
        dist = fn_80178E94(&selfPos, &actorPos);
        range = fn_800CB444(self, other);
        speed = fn_8011F6F8(actor);
        speed *= lbl_8064F680;
        if (dist < range || (dist < 600 && fn_8003E1F0(self, &actorPos, 1, speed) != 0)) {
            heading = fn_8012B7D0(actor, actorPos);
            fn_8017A12C(&diff, fn_8012B750(actor), heading);
            if (dist < range) {
                f32 absDiff = diff;
                if (absDiff < lbl_8064F684) {
                    absDiff = -absDiff;
                }
                if (absDiff <= lbl_8064F688) {
                    fn_800E33B8(arg2, actor, arg3);
                    result = 1;
                    goto done;
                }
            }
            if (fn_8012AFC4(actor) != 0) {
                fn_80129928(actor, &actorPos);
            } else {
                fn_8012976C(actor, 2, 0x21, &actorPos, lbl_8064F68C);
            }
        } else if (fn_800BE2CC(self, arg3, &target) != 0) {
            if (fn_80178E94(&selfPos, &target) < 80) {
                fn_800BE390(self, arg3);
            } else if (fn_8012AFC4(actor) != 0) {
                fn_80129928(actor, &target);
            } else {
                fn_8012976C(actor, 2, 0x21, &target, lbl_8064F68C);
            }
        } else {
            result = 1;
            fn_80201D2C(self, 1);
            fn_80201D14(self, 1);
        }
    } else {
        fn_80201D2C(self, 1);
        fn_80201D14(self, 1);
    }
done:
    return result;
}
