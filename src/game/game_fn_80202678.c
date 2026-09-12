typedef unsigned short u16;

typedef struct Object80202678 {
    char pad[0x24];
    void *value;
} Object80202678;

typedef struct Output80202678 {
    char pad[4];
    int value;
    char pad2[0x2C];
    u16 state;
} Output80202678;

typedef struct Vec3i80202678 {
    int x;
    int y;
    int z;
} Vec3i80202678;

extern void *fn_801A7498(void *object);
extern void *fn_80201814(void *object);
extern int fn_80128F40(void *object);
extern void fn_80201E78(Vec3i80202678 *position, void *object);
extern unsigned int fn_80201CDC(void *object);
extern Output80202678 *fn_80201B94(void *object);
extern int fn_802006D4(int source, void *target, int value, int kind, int flags);
extern int fn_802025D8(void *resource, void *linked, void *owner, void *effect,
                       Output80202678 *output);
extern int fn_8003BD48(void *object, void *effect);
extern int fn_800459E0(void *object);
extern void fn_80201E50(void *object, unsigned int flags);
extern unsigned long long fn_8020123C(int kind, void *target, int value,
                                      int flags);
extern int fn_801AC9F4(int sound, int volume, Vec3i80202678 *position,
                       int flags);

int fn_80202678(void *owner, void *effect)
{
    int result = 0;
    void *resource = fn_801A7498(effect);
    void *linked = fn_80201814(resource);
    int height = fn_80128F40(owner) >> 17;
    Vec3i80202678 position;
    unsigned int flags;
    Output80202678 *output;

    fn_80201E78(&position, linked);
    flags = fn_80201CDC(linked);
    output = fn_80201B94(linked);

    if (flags & 0x10) {
        fn_802006D4(0, resource, -1, 0x9A, 0);
        if (height >= 5 && (flags & 8)) {
            fn_802025D8(resource, linked, owner, effect, output);
            if (output->value != 0)
                fn_8020123C(0xB5, resource, output->value, 0);
        } else {
            result = fn_8003BD48(owner, effect);
            if (result != 0) {
                int kind = fn_800459E0(linked);
                fn_80201E50(((Object80202678 *)linked)->value, flags | 8);
                output->state = 0;
                if ((unsigned int)(kind - 0x23) <= 1 || kind == 0x28)
                    fn_801AC9F4(0x157, 100, &position, 2);
            }
        }
    } else {
        result = fn_8003BD48(owner, effect);
        if (result != 0) {
            Object80202678 *object = (Object80202678 *)linked;
            ((Output80202678 *)object->value)->state = 0;
            fn_80201E50(object->value, flags | 8);
        }
    }

    return result;
}
