#include "src/game/types.h"

typedef struct EffectState {
    u8 active;
    u8 enabled;
    u8 pad02[2];
    int field04;
    int field08;
    int mode;
    u32 type;
    int ownerId;
    int field18;
    int sequence;
    float elapsed;
    float duration;
} EffectState;

typedef struct RuntimeState {
    u8 pad[0x3C];
    EffectState *effect;
} RuntimeState;

extern void *fn_80037AF4(int);
extern void *fn_80201B8C(void *);
extern void fn_802015A4(void *);
extern int fn_801E8328(u32, u32);
extern int fn_80201B54(void *);
extern void *fn_80201814(int);
extern int fn_801CEB2C(u32);
extern void fn_8020104C(int, int, int, int, float);
extern int lbl_8064D18C;
extern const float lbl_8064F29C;
extern const float lbl_8064F31C;
extern const float lbl_8064F320;
extern const float lbl_8064F324;
extern const float lbl_8064F328;

void *fn_800CDE80(int ownerId, u32 type, int mode, float delay)
{
    void *object;
    EffectState *effect;
    int objectId;

    object = fn_80037AF4(0x22);
    if (object != 0) {
        effect = ((RuntimeState *)fn_80201B8C(object))->effect;
        effect->type = type;
        effect->ownerId = ownerId;
        effect->sequence = lbl_8064D18C;
        effect->field18 = 0;
        effect->field04 = 0;
        effect->field08 = 0;
        effect->mode = mode;
        effect->active = 0;
        effect->enabled = 1;
        effect->elapsed = lbl_8064F29C;
        effect->duration = lbl_8064F328;
        fn_802015A4(object);
        fn_801E8328(0x1F, (u32)object);
        objectId = fn_80201B54(object);
        fn_80201814(ownerId);
        if (mode != 0) {
            switch ((s16)fn_801CEB2C(type)) {
            case 3:
                delay = lbl_8064F31C;
                break;
            case 5:
                delay = lbl_8064F320;
                break;
            case 7:
                delay = lbl_8064F324;
                break;
            }
        }
        fn_8020104C(0x5F, objectId, objectId, 0, delay);
    }
    return object;
}
