typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

#pragma pack(4)
typedef struct Voice {
    u8 pad_000[0x34];
    u32 active;
    u8 pad_038[0xD8];
    u32 field_110;
    u64 field_114;
    u8 flag_11C;
    u8 pad_11D[0x2E7];
} Voice;
#pragma pack()

extern Voice* synthVoice;
extern void vidRemoveVoiceReferences(Voice*);
extern void voiceFree(Voice*);
extern void streamKill(u32);
extern void hwBreak(u32);

void voiceKill(u32 index)
{
    Voice* voice;

    voice = &synthVoice[index];
    if (voice->active != 0) {
        vidRemoveVoiceReferences(voice);
        voice->field_114 &= 0xFFFFFFFFFFFFFFFCULL;
        voice->field_110 = 0;
        voiceFree(voice);
    }
    if (voice->flag_11C != 0) {
        streamKill(index);
    }
    hwBreak(index);
}
