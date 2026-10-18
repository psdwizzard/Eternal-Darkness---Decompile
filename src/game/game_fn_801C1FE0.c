typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

typedef struct Voice {
    u8 pad_000[0x34];
    u32 value_034;
    u8 pad_038[0xBC];
    u32 handle;
    u8 pad_0F8[0x24];
    u8 flag_11C;
    u8 flag_11D;
    u8 pad_11E[0x2E6];
} Voice;

extern Voice* synthVoice;
extern u32 voiceAllocate(u8, u8, unsigned short, u8);
extern void vidRemoveVoiceReferences(Voice*);
extern u32 hwIsActive(u32);
extern void hwBreak(u32);
extern void macMakeInactive(Voice*, s32);
extern void voiceSetPriority(Voice*, u8);

u32 voiceBlock(u8 group)
{
    u32 offset;
    u32 result;

    result = voiceAllocate(group, 0xFF, 0xFFFF, 1);

    if (result != (u32)-1) {
        offset = result * 0x404;
        synthVoice[result].flag_11C = 1;
        synthVoice[result].flag_11D = 1;
        vidRemoveVoiceReferences(&synthVoice[result]);
        synthVoice[result].handle = result | 0xFFFFFF00;
        if (hwIsActive(result) != 0) {
            hwBreak(result);
        }
        macMakeInactive(&synthVoice[result], 2);
        synthVoice[result].value_034 = 0;
        voiceSetPriority(&synthVoice[result], group);
    }
    return result;
}
