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

extern FXTab* dataGetFX(u16);
extern u32 synthStartSound(u16, u8, u8, u8, u8, u8, u8, u8, u8, u16, u16,
                       u8, s16, u8, u32);

u32 synthFXStart(u16 effect_id, u8 volume, u8 panning, u8 studio, u32 itd)
{
    u32 voice_id = -1;
    FXTab* effect = dataGetFX(effect_id);

    if (effect != 0) {
        if (volume == 0xFF) {
            volume = effect->volume;
        }
        if (panning == 0xFF) {
            panning = effect->panning;
        }
        voice_id = synthStartSound(effect->macro, effect->priority,
                               effect->max_voices, effect->key | 0x80,
                               volume, panning, 0xFF, 0xFF, 0, 0, 0xFF,
                               effect->volume_group, 0, studio, itd);
    }
    return voice_id;
}
