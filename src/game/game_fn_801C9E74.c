typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct VoiceChannel {
    char pad00[0x1C];
    u8 index;
} VoiceChannel;

typedef struct Voice Voice;
struct Voice {
    Voice* prev;
    Voice* next;
    VoiceChannel* channel;
    char pad0C[4];
    u32 flags;
    char pad14[0x28];
    u32 handle;
    char pad40[4];
    u16 sound_id;
    u8 fallback_channel;
    u8 limit;
    u16 delay_count;
    char pad4A[2];
    float gain;
};

extern u8 s3dCallCnt;
extern Voice* s3dEmitterRoot;
extern u8 startGroupNum;
extern u8 startListNumnum;
extern u8 runListNum;
extern float lbl_80650FB0;
extern float lbl_80650FD4;
extern float lbl_80650FF8;

extern void synthSendKeyOff(u32);
extern u32 synthFXStart(u16, int, int, int, int);
extern u32 sndFXCheck(u32);
extern void CalcEmitter(Voice*, float*, float*, float*, float*, float*);
extern void AddRunningEmitter(Voice*, float);
extern u32 AddStartingEmitter(Voice*, float, float, float, float, float);
extern void SetFXParameters(Voice*, float, float, float, float, float);
extern void StartContinousEmitters(void);
extern void CheckRoomStatus(void);
extern void CheckDoorStatus(void);

void s3dHandle(void)
{
    Voice* voice;
    Voice* next;
    float value1;
    float value2;
    float value3;
    float value4;
    float value5;
    float one;
    float fade_step;
    float zero;

    if (s3dCallCnt != 0) {
        s3dCallCnt--;
        return;
    }

    voice = s3dEmitterRoot;
    zero = lbl_80650FB0;
    s3dCallCnt = 3;
    startGroupNum = 0;
    fade_step = lbl_80650FF8;
    startListNumnum = 0;
    one = lbl_80650FD4;
    runListNum = 0;
    while (voice != 0) {
        next = voice->prev;
        if (voice->flags & 0x40000) {
            if (voice->prev != 0) {
                voice->prev->next = voice->next;
            }
            if (voice->next != 0) {
                voice->next->prev = voice->prev;
            } else {
                s3dEmitterRoot = voice->prev;
            }
            voice->flags &= 0xFFFF;
            if (voice->handle != 0xFFFFFFFF) {
                synthSendKeyOff(voice->handle);
            }
            goto next_voice;
        }

        if (voice->flags & 0x20001) {
            CalcEmitter(voice, &value1, &value5, &value2, &value3, &value4);
        }

        if (!(voice->flags & 0x80000)) {
            if (voice->flags & 0x20000) {
                if (zero == value1 && (voice->flags & 4)) {
                    voice->flags |= 0x80000;
                    voice->flags &= ~0x20000;
                    goto update_voice;
                }
                if (zero == value1 && (voice->flags & 0x40)) {
                    if (voice->prev != 0) {
                        voice->prev->next = voice->next;
                    }
                    if (voice->next != 0) {
                        voice->next->prev = voice->prev;
                    } else {
                        s3dEmitterRoot = voice->prev;
                    }
                    voice->flags &= 0xFFFF;
                    if (voice->handle != 0xFFFFFFFF) {
                        synthSendKeyOff(voice->handle);
                    }
                    goto next_voice;
                }
                if (voice->flags & 1) {
                    if (AddStartingEmitter(voice, value1, value2, value3, value4, value5)) {
                        goto next_voice;
                    }
                    goto update_voice;
                } else {
                    VoiceChannel* channel = voice->channel;
                    if (channel == 0 || channel->index != 0xFF) {
                        int index;
                        if (channel != 0) {
                            index = channel->index;
                        } else {
                            index = voice->fallback_channel;
                        }
                        if ((voice->handle = synthFXStart(voice->sound_id, 0x7F, 0x40,
                                                        index,
                                                        (voice->flags & 0x10) != 0)) != 0xFFFFFFFF) {
                            goto update_voice;
                        }
                    }
                    if (voice->flags & 2) {
                        goto next_voice;
                    }
                    voice->flags |= 0x40000;
                    voice->flags &= ~0x20000;
                    goto update_voice;
                }
            } else {
                if ((voice->handle = sndFXCheck(voice->handle)) == 0xFFFFFFFF) {
                    if (voice->flags & 2) {
                        voice->flags |= 0x20000;
                    } else {
                        voice->flags |= 0x40000;
                    }
                }
            }

update_voice:
            if (voice->handle != 0xFFFFFFFF) {
                if (voice->flags & 1) {
                    AddRunningEmitter(voice, value1);
                }
                if (zero == value1 && (voice->flags & 4)) {
                    synthSendKeyOff(voice->handle);
                    voice->handle = 0xFFFFFFFF;
                    if (voice->flags & 2) {
                        voice->flags |= 0x80000;
                    } else {
                        voice->flags |= 0x40000;
                    }
                } else {
                    SetFXParameters(voice, value1, value2, value3, value4, value5);
                }
            }
            if (voice->flags & 0x100000) {
                voice->gain += fade_step;
                if (voice->gain >= one) {
                    voice->flags &= ~0x100000;
                }
            }
        } else {
            if (voice->channel != 0) {
                if (voice->channel == 0 || voice->channel->index == 0xFF) {
                    goto next_voice;
                }
            }
            {
                if (zero != value1) {
                    voice->flags &= ~0x80000;
                    voice->flags |= 0x20000;
                }
            }
        }
next_voice:
        voice = next;
    }
    StartContinousEmitters();
    CheckRoomStatus();
    CheckDoorStatus();
}
