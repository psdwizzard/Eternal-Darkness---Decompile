typedef unsigned char u8;
typedef signed int s32;

typedef struct SynthInfo {
    u8 pad000[0x210];
    u8 voiceCount;
} SynthInfo;

typedef struct StreamInfo {
    u8 pad00[8];
    u8 state;
    u8 pad09[0x5B];
} StreamInfo;

extern u8 lbl_8064D3E8;
extern u8 lbl_8064D3E9;
extern s32 lbl_8064D3EC;
extern SynthInfo lbl_80619C20;
extern StreamInfo lbl_8061AE48[];

void fn_801B9350(void)
{
    s32 i;

    lbl_8064D3E8 = 0;
    lbl_8064D3E9 = 3;
    for (i = 0; i < lbl_80619C20.voiceCount; ++i) {
        lbl_8061AE48[i].state = 0;
    }
    lbl_8064D3EC = 0;
}
