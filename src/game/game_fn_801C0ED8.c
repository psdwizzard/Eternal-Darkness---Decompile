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

extern AudioConfig synthInfo;
extern Voice* synthVoice;
extern Voice* macActiveMacroRoot;
extern Voice* macTimeQueueRoot;
extern unsigned long long macRealTime;

void macInit(void)
{
    u32 i;

    macActiveMacroRoot = 0;
    macTimeQueueRoot = 0;
    macRealTime = 0;

    for (i = 0; i < synthInfo.voice_count_210; i++) {
        synthVoice[i].value_034 = 0;
        synthVoice[i].active_04C = 2;
        synthVoice[i].value_0AA = 0;
    }
}
