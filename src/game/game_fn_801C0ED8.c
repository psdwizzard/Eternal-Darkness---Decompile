typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Voice {
    u8 pad_000[0x34];
    u32 value_034;
    u8 pad_038[0x14];
    u32 active_04C;
    u8 pad_050[0x5A];
    u16 value_0AA;
    u8 pad_0AC[0x358];
} Voice;

typedef struct AudioConfig {
    u8 pad_000[0x210];
    u8 voice_count_210;
} AudioConfig;

extern AudioConfig lbl_80619C20;
extern Voice* lbl_8064D3D0;
extern Voice* lbl_8064D43C;
extern Voice* lbl_8064D440;
extern unsigned long long lbl_8064D448;

void fn_801C0ED8(void)
{
    u32 i;

    lbl_8064D43C = 0;
    lbl_8064D440 = 0;
    lbl_8064D448 = 0;

    for (i = 0; i < lbl_80619C20.voice_count_210; i++) {
        lbl_8064D3D0[i].value_034 = 0;
        lbl_8064D3D0[i].active_04C = 2;
        lbl_8064D3D0[i].value_0AA = 0;
    }
}
