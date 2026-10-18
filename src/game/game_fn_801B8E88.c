typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void hwDisableIrq(void);
extern void hwEnableIrq(void);
extern u32 synthFXStart(u16, u8, u8, u8, u32);
extern u8 synthITDDefault[];

u32 sndFXStartEx(u16 effect_id, u8 volume, u8 panning, u8 studio)
{
    u32 voice_id;

    hwDisableIrq();
    voice_id = synthFXStart(effect_id, volume, panning, studio,
                           synthITDDefault[studio * 2 + 1]);
    hwEnableIrq();
    return voice_id;
}
