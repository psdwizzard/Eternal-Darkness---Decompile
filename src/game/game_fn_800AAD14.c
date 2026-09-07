typedef struct Vec3i {
    int x;
    int y;
    int z;
} Vec3i;

typedef struct EffectState {
    unsigned char pad0[0xA0];
    int timer;
    signed char active;
    signed char dispatched;
} EffectState;

typedef struct ObjectState {
    unsigned char pad0[0x5C];
    EffectState* effect;
} ObjectState;

extern int fn_80201B54();
extern void *fn_80201B8C();
extern unsigned long long fn_8020123C();
extern Vec3i* fn_8011F130(void*);
extern int* lbl_8064C5A8;
extern int lbl_8023BA20[];
extern void fn_800AA7F0(EffectState*, Vec3i*, int*, int, int, int);

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int fn_800AAD14(void* object, void* position)
{
    EffectState* effect;
    int owner = fn_80201B54(object);
    effect = ((ObjectState*)fn_80201B8C(object))->effect;

    if (effect->active == 1) {
        if (effect->timer > 0) {
            effect->timer--;
        } else {
            fn_8020123C(0x69, owner, owner, 17);
        }
    }

    if (effect->active == 1 && effect->dispatched == 0) {
        Vec3i* point = fn_8011F130(position);
        int value = *lbl_8064C5A8 - 1;
        int color;
        if (MAX(value, 0) > 2) {
            color = 2;
        } else {
            color = MAX(value, 0);
        }
        fn_800AA7F0(effect, point, &lbl_8023BA20[color], 600, 0, owner);
        effect->dispatched = 1;
    }
    return 0;
}
