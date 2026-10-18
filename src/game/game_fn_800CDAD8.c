typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef unsigned int u32;

typedef struct Entry80201814 Entry80201814;
typedef struct Object802015A4 Object802015A4;
typedef struct State State;

typedef struct EffectLink {
    u8 pad[0x3C];
    int id;
} EffectLink;

typedef struct EffectParameters {
    int owner;
    u32 spell;
} EffectParameters;

typedef struct ObjectData {
    u8 pad0[0x34];
    EffectParameters *parameters;
    u8 pad38[0x54];
    EffectLink *effect;
} ObjectData;

extern void *fn_80037AF4(int);
extern void fn_8012C478(State *, int, int);
extern void *fn_8012C62C(u8 *, int, void *, s8 *, void *, int);
extern void fn_8016B400(int, void *, void *);
extern int fn_801CEB2C(u32);
extern int fn_801D38E8(int);
extern void fn_801E79A0(u8 *, u32);
extern int fn_801E79FC(u32 *, u32);
extern int fn_801E8328(u32, u32);
extern void fn_8020104C(int, int, int, int, float);
extern void fn_802015A4(Object802015A4 *);
extern Entry80201814 *fn_80201814(int);
extern int fn_802019EC(int, int);
extern int fn_80201B54(int *);
extern void *fn_80201B8C(u8 *);
extern void *fn_80201BC8(void *);

extern u32 lbl_8023BA30[13];
extern void *lbl_8064C4E0;
extern int *lbl_8064C5A8;
extern int lbl_8064D18C;
extern u32 lbl_8064F310, lbl_8064F314, lbl_8064F318;
extern float lbl_8064F31C, lbl_8064F320, lbl_8064F324;

void *fn_800CDAD8(u32 spell, int owner, int useDefaultTime, float duration)
{
    struct Word { u32 value; } color, mask, mode;
    struct Word colorCopy, modeCopy, maskCopy;
    void *result = 0;
    Entry80201814 *entry;
    ObjectData *data;
    EffectParameters *parameters;
    int effectId;
    u32 trigger;
    int enabled;
    void *state;

    entry = fn_80201814(owner);
    if (entry != 0) {
        data = fn_80201B8C((u8 *)entry);
        result = fn_80037AF4(0x31);
        effectId = fn_80201B54((int *)result);
        data->effect->id = effectId;
        parameters = ((ObjectData *)fn_80201B8C((u8 *)result))->parameters;
        parameters->owner = owner;
        parameters->spell = spell;
        fn_802015A4((Object802015A4 *)result);
        fn_801E8328(0x15, (u32)result);
        if (useDefaultTime) {
            if (fn_801D38E8(spell) == 4) {
                switch ((s16)fn_801CEB2C(spell)) {
                case 3: duration = lbl_8064F31C; break;
                case 5: duration = lbl_8064F320; break;
                case 7: duration = lbl_8064F324; break;
                default: duration = lbl_8064F31C; break;
                }
            } else {
                duration = lbl_8064F31C;
            }
        }
        fn_8020104C(0x39, effectId, effectId, 0, duration);
        trigger = 0;
        if (lbl_8064D18C == 0x5A)
            trigger = 0x1C7;
        else if (lbl_8064D18C == 0xCA)
            trigger = 0x34A;
        if (trigger != 0 && fn_801E79FC(lbl_8064C4E0, trigger)) {
            /* The packed words hold a table of signed halfwords, five per row. */
            enabled = ((s16 (*)[5])lbl_8023BA30)[fn_801D38E8(spell)][*lbl_8064C5A8] == 1;
            if (lbl_8064D18C == 0xCA)
                enabled = enabled && (spell & 0x70000) == 0x20000;
            else if (lbl_8064D18C == 0x5A)
                enabled = enabled && (spell & 0x70000) == 0x40000;
            if (enabled) {
                fn_801E79A0(lbl_8064C4E0, trigger);
                if (lbl_8064D18C == 0xCA)
                    fn_8016B400(0x397, 0, 0);
                entry = fn_80201814(fn_802019EC(trigger, lbl_8064D18C));
                if (entry != 0) {
                    state = fn_80201BC8(entry);
                    if (state != 0) {
                        color.value = lbl_8064F310;
                        mask.value = lbl_8064F314;
                        mode.value = lbl_8064F318;
                        fn_8012C478((State *)state, 0xF, 1);
                        maskCopy = mask;
                        modeCopy = mode;
                        colorCopy = color;
                        fn_8012C62C(state, 0xF, &colorCopy, (s8 *)&modeCopy, &maskCopy, 4);
                    }
                }
            }
        }
    }
    return result;
}
