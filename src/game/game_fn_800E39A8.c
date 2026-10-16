typedef signed int s32;
typedef unsigned int u32;
typedef float f32;
typedef unsigned char u8;

typedef struct Vec { int x, y, z; } Vec;
typedef struct Entry80201814 Entry80201814;
typedef struct Object80201D2C Object80201D2C;
typedef struct Object80201D14 Object80201D14;
typedef struct Object80201C48 Object80201C48;
typedef struct EventData EventData;
typedef struct Owner Owner;
typedef struct RuntimeState RuntimeState;

typedef struct Vec3 {
    f32 x, y, z;
} Vec3;

/* Movement stores the same position as three raw words. */
typedef union Position {
    Vec3 vector;
    Vec words;
} Position;

extern f32 lbl_8064F680;
extern f32 lbl_8064F684;
extern f32 lbl_8064F688;
extern f32 lbl_8064F68C;

extern void *fn_80201B94(u8 *);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern int fn_80066D04(s32, s32);
extern void fn_80201D2C(Object80201D2C *, int);
extern void fn_80201D14(Object80201D14 *, u8);
extern s32 fn_800359A0(void *, void *);
extern void *fn_80201C48(Object80201C48 *);
extern Entry80201814 *fn_80201814(int);
extern s32 fn_802045AC(void *, Vec3 *);
extern u32 fn_80178E94(const float *, const float *);
extern f32 fn_800CB444(void *, void *);
extern f32 fn_8011F6F8(void *);
extern int fn_8003E1F0(void *, Vec3 *, int, f32);
extern f32 fn_8012B7D0(const void *, const void *);
extern f32 fn_8012B750(void *);
extern void fn_8017A12C(f32 *, f32, f32);
extern void fn_800E33B8(int, void *, EventData *);
extern int fn_8012AFC4(void *);
extern int fn_80129928(void *, Vec *);
extern u8 *fn_8012976C(Owner *, int, int, Vec3 *, f32);
extern int fn_800BE2CC(void *, RuntimeState *, void *);
extern void fn_800BE390(void *, RuntimeState *);

int fn_800E39A8(void *self, void *actor, void *arg2, void *arg3, int arg4, int arg5, int arg6) {
    f32 diff;
    Position actorPos;
    Vec3 selfPos;
    Position target;
    void *object;
    Entry80201814 *other;
    int reference;
    s32 dist;
    s32 range;
    f32 speed;
    f32 heading;
    int result;

    result = 0;
    object = fn_80201B94(self);
    fn_8011F114(&selfPos, actor);
    if (fn_80066D04((s32)self, 0) == 0) {
        fn_80201D2C(self, 1);
        fn_80201D14(self, 1);
        return 1;
    }
    if ((arg5 & arg6) == 0) {
        fn_800359A0(self, 0);
    }
    if ((reference = (int)fn_80201C48(object)) != 0 &&
        (other = fn_80201814(reference)) != 0) {
        fn_802045AC(self, &actorPos.vector);
        dist = fn_80178E94(&selfPos.x, &actorPos.vector.x);
        range = fn_800CB444(self, other);
        speed = fn_8011F6F8(actor);
        speed *= lbl_8064F680;
        if (dist < range || (dist < 600 && fn_8003E1F0(self, &actorPos.vector, 1, speed) != 0)) {
            {
                Vec3 headingTarget = actorPos.vector;
                heading = fn_8012B7D0(actor, &headingTarget);
            }
            fn_8017A12C(&diff, fn_8012B750(actor), heading);
            if (dist < range) {
                f32 absDiff = diff;
                if (absDiff < lbl_8064F684) {
                    absDiff = -absDiff;
                }
                if (absDiff <= lbl_8064F688) {
                    fn_800E33B8((int)arg2, actor, arg3);
                    result = 1;
                    goto done;
                }
            }
            if (fn_8012AFC4(actor) != 0) {
                fn_80129928(actor, &actorPos.words);
            } else {
                fn_8012976C(actor, 2, 0x21, &actorPos.vector, lbl_8064F68C);
            }
        } else if (fn_800BE2CC(self, arg3, &target.vector) != 0) {
            if (fn_80178E94(&selfPos.x, &target.vector.x) < 80) {
                fn_800BE390(self, arg3);
            } else if (fn_8012AFC4(actor) != 0) {
                fn_80129928(actor, &target.words);
            } else {
                fn_8012976C(actor, 2, 0x21, &target.vector, lbl_8064F68C);
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
