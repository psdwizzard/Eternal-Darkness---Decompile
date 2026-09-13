typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Node Node;
struct Node {
    Node* next;
    Node* prev;
    u8 state;
    u8 type;
    u8 pad0A[2];
    u32 key;
};

typedef struct SynthVoice {
    u8 pad000[0x324];
    u8 trackVolumeGroup[64];
    u8 pad364[0xEB0 - 0x364];
    u8 defaultVolumeGroup;
    u8 padEB1[0xECC - 0xEB1];
    u8 vol2;
    u8 padECD[0xEDA - 0xECD];
    u8 crossFlags;
    u8 padEDB;
    void* syncSeqIdPtr;
    u8 padEE0[0x1868 - 0xEE0];
} SynthVoice;

typedef struct SynthVoiceRuntime {
    u8 pad[0x1400];
    SynthVoice voices[1];
} SynthVoiceRuntime;

extern SynthVoiceRuntime lbl_8060C020;
extern Node* lbl_8064D398;
extern Node* lbl_8064D39C;
extern void fn_801B8164(u8, u16, u8, u8, u32);

static inline int resolve_handle(u32 value)
{
    u32 key = value & 0x7FFFFFFF;
    Node* node = lbl_8064D39C;

    while (node != 0) {
        if (node->key == key) {
            key = node->type;
            return key | (value & 0x80000000U);
        }
        node = node->next;
    }
    node = lbl_8064D398;
    while (node != 0) {
        if (node->key == key) {
            key = node->type;
            return key | (value & 0x80000000U);
        }
        node = node->next;
    }
    return -1;
}

#define SYNTH_VOICE_TRACK_VOLUME_GROUP_OFFSET ((u32) & (((SynthVoice*)0)->trackVolumeGroup))
#define SYNTH_RUNTIME_VOICES_OFFSET ((u32) & (((SynthVoiceRuntime*)0)->voices))

void fn_801B3CC8(u8 volume, u16 time, u32 seqId, u8 mode)
{
    SynthVoiceRuntime* runtime;
    u8* voiceBase;
    u8* voiceBytes;
    u8* voiceCursor;
    SynthVoice* voice;
    u32 voiceIndex;
    u32 studioIndex;
    u32 pub_id;

    runtime = &lbl_8060C020;
    pub_id = seqId;
    studioIndex = resolve_handle(seqId);

    if (studioIndex != 0xFFFFFFFF) {
        if ((studioIndex & 0x80000000) == 0) {
            voiceBase = (u8*)runtime + studioIndex * sizeof(SynthVoice);
            fn_801B8164(volume, time, ((SynthVoice*)(voiceBase + SYNTH_RUNTIME_VOICES_OFFSET))->defaultVolumeGroup, mode, pub_id);
            voice = (SynthVoice*)(voiceBase + SYNTH_RUNTIME_VOICES_OFFSET);
            voiceBytes = (u8*)voice;
            voiceCursor = (u8*)voice;
            voiceIndex = 0;
            do {
                if (voiceBytes[SYNTH_VOICE_TRACK_VOLUME_GROUP_OFFSET] != voice->defaultVolumeGroup) {
                    fn_801B8164(volume, time, voiceCursor[SYNTH_VOICE_TRACK_VOLUME_GROUP_OFFSET], 0, 0xFFFFFFFF);
                }
                voiceBytes++;
                voiceCursor++;
                voiceIndex++;
            } while (voiceIndex < 64);
        } else {
            seqId = studioIndex & 0x7FFFFFFF;
            switch (mode & 0xF) {
            case 0:
                runtime->voices[seqId].vol2 = volume;
                break;
            case 1:
                runtime->voices[seqId].syncSeqIdPtr = 0;
                break;
            case 2:
                runtime->voices[seqId].crossFlags |= 8;
                runtime->voices[seqId].vol2 = volume;
                break;
            case 3:
                runtime->voices[seqId].crossFlags |= 0x80;
                runtime->voices[seqId].vol2 = volume;
                break;
            }
        }
    }
}
