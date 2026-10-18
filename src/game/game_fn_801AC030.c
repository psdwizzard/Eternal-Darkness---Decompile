typedef unsigned char u8;
typedef signed char s8;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Effect {
    u8 pad0[0x50];
    Vec3 position;
    Vec3 delta;
    Vec3 previous_position;
    u8 pad_position[4];
    float range;
    u8 pad1[0x0C];
    u8 amount;
    u8 low;
    u8 high;
    u8 pad2[4];
    s8 active;
    u8 pad3;
    u8 mode;
    s8 stationary;
} Effect;

extern u8 fn_801ABF34(Vec3*, float, u8, u8, int);
extern void sndUpdateEmitter(Effect*, Vec3*, Vec3*, u8, int);

void fn_801AC030(Effect* effect)
{
    if (effect != 0 && effect->active != 0) {
        effect->amount = fn_801ABF34(&effect->position, effect->range,
                                    effect->high, effect->low, effect->mode);
        effect->previous_position = effect->position;
        effect->delta.x = effect->position.x - effect->previous_position.x;
        effect->delta.y = effect->position.y - effect->previous_position.y;
        effect->delta.z = effect->position.z - effect->previous_position.z;
        if (effect->stationary == 0) {
            sndUpdateEmitter(effect, &effect->position, &effect->delta,
                        effect->amount, 0);
        }
    }
}
