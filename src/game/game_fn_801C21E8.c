typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;

#pragma pack(4)
typedef struct Voice {
    u8 pad_000[0x34];
    u32 active;
    u8 pad_038[0xB4];
    u32 next;
    u8 pad_0F0[4];
    u32 index;
    u8 pad_0F8[0x18];
    u32 field_110;
    u64 field_114;
    u8 flag_11C;
    u8 pad_11D[0x2E7];
} Voice;
#pragma pack()

typedef struct HandleInfo {
    u8 pad_000[0xC];
    u32 first;
} HandleInfo;

extern u8 sndActive;
extern Voice* synthVoice;
extern HandleInfo* get_vidlist(u32);
extern void vidRemoveVoiceReferences(Voice*);
extern void voiceFree(Voice*);
extern void streamKill(u32);
extern void hwBreak(u32);

s32 voiceKillSound(u32 handle)
{
    Voice* voice;
    s32 result = -1;
    u32 next;
    u32 slot;
    HandleInfo* info;

    if (sndActive != 0) {
        if (handle != (u32)-1 && (info = get_vidlist(handle)) != 0) {
            handle = info->first;
        } else {
            handle = -1;
        }
        while (handle != (u32)-1) {
            slot = (u8)handle;
            voice = &synthVoice[slot];
            next = voice->next;
            if (handle == voice->index) {
                if (voice->active != 0) {
                    vidRemoveVoiceReferences(voice);
                    voice->field_114 &= 0xFFFFFFFFFFFFFFFCULL;
                    voice->field_110 = 0;
                    voiceFree(voice);
                }
                if (voice->flag_11C != 0) {
                    streamKill(slot);
                }
                hwBreak(slot);
                result = 0;
            }
            handle = next;
        }
    }
    return result;
}
