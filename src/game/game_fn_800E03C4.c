typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct TargetState {
    u8 pad[0x1E];
    s16 status;
} TargetState;

typedef struct RuntimeState RuntimeState;

typedef struct ActionState {
    u8 pad[0x94];
    Vec3 position;
} ActionState;

typedef struct OwnerState {
    u8 pad00[0x50];
    TargetState *target;
    u8 pad54[0x38];
    ActionState *action;
} OwnerState;

extern void *fn_80201B8C(unsigned char *);
extern void *fn_80201B94(unsigned char *);
extern int fn_80201B54(int *);
extern int fn_80201B44(void);
typedef struct Entry80201814 Entry80201814;
extern Entry80201814 *fn_80201814(int);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern Vec3 *lbl_8064C4E4;
extern int fn_800DE3F8(void);
extern int fn_80038308(void *, int, s16 *);
extern int fn_80038464(void *, int, s16 *);
extern int fn_80036E50(void *);
typedef struct Object80201DD8 Object80201DD8;
extern void fn_80201DD8(Object80201DD8 *, void *);
extern int fn_800BDEE4(int, RuntimeState *);
typedef struct Object80201D2C Object80201D2C;
extern void fn_80201D2C(Object80201D2C *, int);
typedef struct Object80201D14 Object80201D14;
extern void fn_80201D14(Object80201D14 *, u8);
extern u32 lbl_8064D5A8;
extern float fn_8012B7D0(const void *, const void *);
extern float fn_8012B750(void *);
extern void fn_8017A12C(float *, float, float);
extern const float lbl_8064F588;
extern const float lbl_8064F59C;
extern void *fn_801A717C(void);
extern void fn_801A74A0(void *, u32);
extern void fn_801A74A8(void *, u32);
extern void fn_801A7470(void *, u32);
extern unsigned long long fn_8020123C(int, int, int, int);
extern void fn_801A7228(void *);

int fn_800E03C4(void *owner, void *object)
{
    OwnerState *owner_state;
    TargetState *target;
    ActionState *action;
    void *related;
    void *current;
    int self_id;
    int result = 0;
    int object_id;
    Vec3 object_position;
    Vec3 reference_position;
    s16 second;
    s16 first;

    owner_state = fn_80201B8C(owner);
    target = owner_state->target;
    action = owner_state->action;
    related = fn_80201B94(owner);
    object_id = fn_80201B54(owner);
    self_id = fn_80201B44();
    current = fn_80201814(self_id);
    fn_8011F114(&object_position, object);
    fn_8011F114(&reference_position, lbl_8064C4E4);
    fn_800DE3F8();
    fn_80038308(owner, 0, &first);
    fn_80038464(owner, 0, &second);

    if (target->status == 0) {
        if (fn_80036E50(current) != 6) {
            fn_80201DD8(related, (void *)self_id);
            fn_800BDEE4((int)owner, (RuntimeState *)action);
            fn_80201D2C(owner, 3);
            fn_80201D14(owner, 1);
            result = 1;
        } else if ((u8)lbl_8064D5A8 == 0) {
            float angle;
            float magnitude;
            Vec3 angle_position = reference_position;
            angle = fn_8012B7D0(object, &angle_position);
            fn_8017A12C(&magnitude, fn_8012B750(object), angle);
            {
                float value = magnitude;
                if (value < lbl_8064F588) {
                    value = -value;
                }
                if (value > lbl_8064F59C) {
                    action->position = reference_position;
                    fn_80201D2C(owner, 0x15);
                    fn_80201D14(owner, 1);
                } else if ((lbl_8064D5A8 & 0x1FF) == 0) {
                    void *event = fn_801A717C();
                    fn_801A74A0(event, object_id);
                    fn_801A74A8(event, object_id);
                    fn_801A7470(event, 0x10);
                    fn_8020123C(0x35, object_id, object_id, (int)event);
                    fn_801A7228(event);
                }
            }
        }
    }
    return result;
}
