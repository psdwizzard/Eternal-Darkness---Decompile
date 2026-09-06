typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void fn_801CE2B8(void);
extern void fn_801CE280(void);
extern u32 fn_801B7DC8(u16, u8, u8, u8, u32);
extern u8 lbl_8061A4F4[];

u32 fn_801B8E88(u16 effect_id, u8 volume, u8 panning, u8 studio)
{
    u32 voice_id;

    fn_801CE2B8();
    voice_id = fn_801B7DC8(effect_id, volume, panning, studio,
                           lbl_8061A4F4[studio * 2 + 1]);
    fn_801CE280();
    return voice_id;
}
