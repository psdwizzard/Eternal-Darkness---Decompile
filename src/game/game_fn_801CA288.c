typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SynthInfo {
    char pad00[0x210];
    u8 voice_count;
    u8 max_music;
    u8 max_sfx;
    u8 studio_count;
} SynthInfo;

extern SynthInfo lbl_80619C20;
extern u8 lbl_8064D3A0;
extern u8 lbl_8064D3D8;

extern int fn_801CC5D4(u32*, u16, u16, u32);
extern void fn_801C38C0(void);
extern void fn_801BD294(int, u32);
extern void fn_801B58F0(void);
extern void fn_801B86C0(u32, u32);
extern void fn_801B9350(void);
extern void fn_801C3158(void);
extern void fn_801CA240(u32);

static inline int DoInit(u32 mix_frequency, u32 aram_size, u32 voice_count,
                         u32 flags)
{
    int result = 0;

    fn_801C38C0();
    fn_801BD294(0, aram_size);
    fn_801B58F0();
    lbl_8064D3D8 = 0;
    fn_801B86C0(mix_frequency, voice_count);
    fn_801B9350();
    fn_801C3158();
    fn_801CA240(flags);
    lbl_8064D3A0 = 1;
    return result;
}

int fn_801CA288(u8 voices, u8 music, u8 sfx, u8 studios, u32 flags,
                u32 aram_size)
{
    int result;
    u32 frequency;

    result = 0;
    lbl_8064D3A0 = 0;
    if (voices <= 0x40) {
        lbl_80619C20.voice_count = voices;
    } else {
        lbl_80619C20.voice_count = 0x40;
    }
    if (studios <= 8) {
        lbl_80619C20.studio_count = studios;
    } else {
        lbl_80619C20.studio_count = 8;
    }
    lbl_80619C20.max_music = music;
    lbl_80619C20.max_sfx = sfx;
    frequency = 0x7D00;
    result = fn_801CC5D4(&frequency, lbl_80619C20.voice_count,
                         lbl_80619C20.studio_count, flags);
    if (result == 0) {
        result = DoInit(0x7D00, aram_size, lbl_80619C20.voice_count, flags);
    }
    return result;
}
