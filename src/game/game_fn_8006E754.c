typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Config {
    unsigned char pad_00[0x60];
    short channels[4];
    Vec3 direction;
    Vec3 position;
    float angle;
    unsigned char pad_84[0x18];
    int effect1;
    int effect2;
    int effect4;
} Config;

typedef struct Owner {
    unsigned char pad_00[0x38];
    void *resource;
    unsigned char pad_3c[0x88];
    Config *config;
} Owner;

extern void *fn_80201814();
extern void *fn_80201BC8();
extern int fn_8006BCE4(Owner *owner);
extern void fn_8011F104(void *object, float x, float y, float z);
extern void fn_8012B7A0(void *object, float angle);
extern void fn_801D13D8(void *resource, int value);
extern void fn_8011F114(Vec3 *out, void *object);
extern Vec3 *fn_8011F770(void *object);
extern short *fn_8006ED3C(Owner *owner, int type, short *result);
extern void fn_8012AC74(void *object, Vec3 *value, int count);
extern void fn_800C1B50(void *resource, int type, int value, float a, float b);
extern void fn_8012C478(void *object, int index, int value);
extern void *fn_80201B54(void *object);
extern void *fn_80158598(void *object, int value);
extern void *fn_80201C24(void *object);
extern void fn_80157E34(void *object, int effect, int type, void *callback, int value);
extern int fn_800389E0(void *resource, int channel, int value, int zero);
extern const float lbl_8064E7E0;

void fn_8006E754(Owner *owner, int enabled)
{
    Config *config;
    void *resource_object;
    void *object;
    int kind;
    Vec3 saved_23;
    Vec3 saved_20;
    Vec3 value_23;
    Vec3 value_20;
    Vec3 *target;
    short count;
    short *count_result;

    config = owner->config;
    resource_object = fn_80201814(owner->resource);
    object = fn_80201BC8(resource_object);
    kind = fn_8006BCE4(owner);

    if (!enabled) {
        fn_8011F104(object, config->position.x, config->position.y, config->position.z);
        fn_8012B7A0(object, config->angle);
        fn_801D13D8(owner->resource, 0);
    } else {
        switch (kind) {
        case 0x23:
            fn_8011F114(&value_23, object);
            saved_23 = value_23;
            target = fn_8011F770(object);
            count_result = fn_8006ED3C(owner, 0x23, &count);
            if (count_result[4] > 0) {
                *target = config->direction;
                fn_8012AC74(object, &saved_23, 3);
            }
            break;
        case 0x20:
        case 0x21:
            fn_8011F114(&value_20, object);
            saved_20 = value_20;
            fn_800C1B50(owner->resource, 0xF, 1, lbl_8064E7E0, lbl_8064E7E0);
            fn_8012AC74(object, &saved_20, 3);
            break;
        case 0x22:
        default:
            break;
        }
    }

    fn_8012C478(object, 0, 1);
    fn_8012C478(object, 1, 1);
    fn_8012C478(object, 2, 1);
    fn_8012C478(object, 3, 1);

    if (config->effect2 != -1) {
        void *effect_object = fn_80201814((void *)config->effect2);
        if (effect_object != 0) {
            void *effect_target = fn_80158598(fn_80201B54(resource_object), 0);
            void **vtable = (void **)fn_80201C24(effect_object);
            fn_80157E34(effect_target, config->effect2, 2,
                        *(void **)((unsigned char *)*vtable + 0x18), 0);
        }
    }
    if (config->effect1 != -1) {
        void *effect_object = fn_80201814((void *)config->effect1);
        if (effect_object != 0) {
            void *effect_target = fn_80158598(fn_80201B54(resource_object), 0);
            void **vtable = (void **)fn_80201C24(effect_object);
            fn_80157E34(effect_target, config->effect1, 1,
                        *(void **)((unsigned char *)*vtable + 0x18), 0);
        }
    }
    if (config->effect4 != -1) {
        void *effect_object = fn_80201814((void *)config->effect4);
        if (effect_object != 0) {
            void *effect_target = fn_80158598(fn_80201B54(resource_object), 0);
            void **vtable = (void **)fn_80201C24(effect_object);
            fn_80157E34(effect_target, config->effect4, 4,
                        *(void **)((unsigned char *)*vtable + 0x18), 0);
        }
    }

    fn_800389E0(resource_object, 0, config->channels[0], 0);
    fn_800389E0(resource_object, 2, config->channels[1], 0);
    fn_800389E0(resource_object, 3, config->channels[2], 0);
    fn_800389E0(resource_object, 1, config->channels[3], 0);
}
