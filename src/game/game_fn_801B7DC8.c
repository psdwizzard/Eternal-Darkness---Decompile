typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;

typedef struct FXTab {
    u16 id;
    u16 macro;
    u8 max_voices;
    u8 priority;
    u8 volume;
    u8 panning;
    u8 key;
    u8 volume_group;
} FXTab;

extern FXTab* fn_801BD1EC(u16);
extern u32 fn_801B64D0(u16, u8, u8, u8, u8, u8, u8, u8, u8, u16, u16,
                       u8, s16, u8, u32);

u32 fn_801B7DC8(u16 effect_id, u8 volume, u8 panning, u8 studio, u32 itd)
{
    u32 voice_id = -1;
    FXTab* effect = fn_801BD1EC(effect_id);

    if (effect != 0) {
        if (volume == 0xFF) {
            volume = effect->volume;
        }
        if (panning == 0xFF) {
            panning = effect->panning;
        }
        voice_id = fn_801B64D0(effect->macro, effect->priority,
                               effect->max_voices, effect->key | 0x80,
                               volume, panning, 0xFF, 0xFF, 0, 0, 0xFF,
                               effect->volume_group, 0, studio, itd);
    }
    return voice_id;
}
