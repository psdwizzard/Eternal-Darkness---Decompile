typedef struct Vec8007381C { float x, y, z; } Vec8007381C;

extern void fn_8011F114();
extern int fn_80201B54();
extern void *fn_80201B94();
extern void *fn_80201B8C();
extern int fn_80201C48(void *);
extern void *fn_80201814();
extern void *fn_80201BC8(void *);
extern void fn_80128EE4(void *);
extern void fn_80073AE8(void *, int *, short *, short *);
extern void *fn_801294DC(void *, int, int, int);
extern void *fn_801A717C(void);
extern float fn_8012B7D0(void *, Vec8007381C);
extern float fn_8012B750(void *);
extern void fn_8017A12C(float *, float, float);
extern void fn_80129BA4(void *, float, float);
extern int fn_80129334(void *, int, int *, int);
extern void *fn_80072354(void *);
extern void fn_801A7460(void *, int);
extern void fn_801A74A0(void *, int);
extern void fn_801A74A8(void *, int);
extern void fn_801A74C8(void *, int);
extern void fn_801A7560(void *, int);
extern void fn_800CF6AC(void *, void *, void *, void *, int, int);
extern void fn_801A7550(void *, int);
extern void fn_801A7558(void *, int);
extern void fn_801A764C(void *, void *);
extern void fn_801A7598(void *, int);
extern void fn_801287C4(void *, void *, void *, int);
extern void fn_80128C28();
extern void fn_80128C44(void *, void *, void *);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_8003B8A0(void);
extern void fn_80073728(void);
extern void fn_80204230(void);
extern void fn_802042A4(void);

extern float lbl_8064E870;
extern float lbl_8064E874;
extern float lbl_8064E878;

typedef struct Timer8007381C {
    unsigned char pad0[0x1BA];
    unsigned short cooldown;
} Timer8007381C;

typedef struct Data8007381C {
    unsigned char pad0[0x44];
    Timer8007381C *timer;
    unsigned char pad48[0x90 - 0x48];
    void *value90;
} Data8007381C;

int fn_8007381C(void *object, void *resource)
{
    short flags_a;
    short flags_b;
    int sound_id;
    float diff;
    int frame;
    Vec8007381C position;
    Vec8007381C target_position;
    Data8007381C *value;
    int target_id;
    int owner;
    void *target;
    Timer8007381C *timer;
    void *created;
    void *actor;
    void *model;
    float angle;
    float d;

    value = fn_80201B8C(object);
    target_id = fn_80201C48(fn_80201B94(object));
    owner = fn_80201B54(object);
    {
        Vec8007381C tmp;
        fn_8011F114(&tmp, resource);
        position = tmp;
    }
    target = fn_80201814(target_id);
    if (target != 0) {
        target = fn_80201BC8(target);
        if (target != 0) {
            {
                Vec8007381C tmp;
                fn_8011F114(&tmp, target);
                target_position = tmp;
            }
            timer = value->timer;
            fn_80128EE4(resource);
            fn_80073AE8(object, &sound_id, &flags_a, &flags_b);
            if (sound_id != -1 && timer->cooldown == 0) {
                created = fn_801294DC(resource, sound_id, 0x100, 6);
                if (created != 0) {
                    actor = fn_801A717C();
                    timer->cooldown = 180;
                    angle = fn_8012B7D0(resource, target_position);
                    fn_8017A12C(&diff, fn_8012B750(resource), angle);
                    d = diff;
                    if (d < lbl_8064E870)
                        d = -d;
                    if (d > lbl_8064E874)
                        fn_80129BA4(created, angle, lbl_8064E878);
                    if (fn_80129334(resource, 1, &frame, -1) != -1) {
                        model = fn_80072354(value->value90);
                        fn_801A7460(actor, sound_id);
                        fn_801A74A0(actor, owner);
                        fn_801A74A8(actor, target_id);
                        fn_801A74C8(actor, 1);
                        fn_801A7560(actor, 0x100284);
                        fn_800CF6AC(object, model, value, actor, 1, sound_id);
                        fn_801A7550(actor, 12);
                        fn_801A7558(actor, 7);
                        fn_801A764C(actor, &position);
                        fn_801A7598(actor, 400);
                        fn_801287C4(created, fn_8003B8A0, actor, frame - 2);
                        fn_801287C4(created, fn_80073728, actor, frame);
                        fn_80128C28(created, fn_80204230, actor);
                        fn_80128C44(created, fn_802042A4, actor);
                        fn_80201D2C(object, 6);
                        fn_80201D14(object, 1);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}
