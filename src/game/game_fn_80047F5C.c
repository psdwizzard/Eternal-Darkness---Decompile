typedef signed int s32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct QueryResult {
    s32 word0;
    s32 word4;
    Vec3 position;
    unsigned char pad14[0x14];
} QueryResult;

typedef struct EffectOwner EffectOwner;

extern s32 fn_80201A84(void *object);
extern s32 fn_8011F598(void *object, s32 type, s32 subtype, s32 previous,
                       QueryResult *result, s32 enabled);
extern void fn_8007C59C(EffectOwner *effect, Vec3 *position, void *owner);
extern s32 fn_801E855C(s32 type, void *object, void *result);
extern void fn_801E8328(s32 type, void *object);

void fn_80047F5C(void *object, EffectOwner *effect)
{
    QueryResult query;
    s32 owner;

    owner = fn_80201A84(object);
    if (fn_8011F598(object, 4, -1, -1, &query, 1) != -1 && effect != 0) {
        fn_8007C59C(effect, &query.position, (void *)owner);
        if (fn_801E855C(0x14, effect, 0) == 0) {
            fn_801E8328(0x14, effect);
        }
    }
}
