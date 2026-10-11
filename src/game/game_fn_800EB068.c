typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct State800EB068 {
    int id;
    Vec3 position;
    void *objects[3];
    int resolved[3];
    unsigned char padding[0x17E - 0x28];
    unsigned char triggered;
    unsigned char pad17F;
    int targetId;
} State800EB068;

extern void *fn_80201814(int id);
extern void *fn_80201BC8(void *object);
extern int fn_80201B44(void);
extern int fn_80201EB8(void *object);
extern void *fn_80201B8C(unsigned char *object);
extern void *fn_8011F130(void *object);
extern unsigned short fn_8011F760(void *object);
extern unsigned short fn_801869DC(unsigned char *object);
extern int fn_8017FDF4(void *object);
extern int fn_800EB328(State800EB068 *state, int index);
extern unsigned int fn_80178E94(const float *first, const float *second);
extern int fn_800EAF7C(const Vec3 *first, const Vec3 *second, int height);

int fn_800EB068(void *object, int unused, State800EB068 *state)
{
    int result = 0;
    void *target;
    int currentId;
    int targetType;
    int i;
    void *model;
    Vec3 *position;
    int upperHeight;
    int lowerHeight;
    int height;

    if (state->targetId != 0 && state->triggered == 0) {
        target = fn_80201814(state->targetId);
        if (target != 0) {
            fn_80201BC8(object);
            currentId = fn_80201B44();
            targetType = fn_80201EB8(target);
            model = fn_80201BC8(target);
            position = fn_8011F130(model);
            upperHeight = (int)position->z + fn_8011F760(model);
            lowerHeight = (int)position->z - 150;
            height = (int)state->position.z;
            for (i = 0; i < 3; i++) {
                if (fn_800EB328(state, i)) {
                    void *candidate = state->objects[i];
                    unsigned int radius = fn_801869DC(candidate);
                    int type = fn_8017FDF4(candidate);
                    int id = state->resolved[i];
                    fn_80201B8C(target);
                    if (id != state->targetId && type == targetType &&
                        lowerHeight <= height && height <= upperHeight &&
                        fn_80178E94(&state->position.x, &position->x) < radius &&
                        fn_800EAF7C(&state->position, position, 10) == 0) {
                        if (state->targetId == currentId) {
                            result = 1;
                            state->triggered = 1;
                            break;
                        } else {
                            void *owner = fn_80201814(state->id);
                            if (owner != 0) {
                                fn_80201B8C(owner);
                            }
                            result = 1;
                            state->triggered = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    return result;
}
