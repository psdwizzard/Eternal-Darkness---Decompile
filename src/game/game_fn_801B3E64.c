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

typedef struct SynthStartRequest {
    u32 seqId1;
    u16 time1;
    u8 pad06[2];
    u32 seqId2;
    u16 time2;
    u8 pad0E[2];
    u32 arr2;
    u16 gid2;
    u16 sid2;
    u8 vol2;
    u8 studio2;
    u8 pad1A[2];
    u32 trackMute2[2];
    u16 speed2;
    u8 flags;
    u8 pad27;
} SynthStartRequest;

typedef struct SynthPlayParams {
    u32 flags;
    u32 trackMute[2];
    u16 speed;
    u16 volumeTime;
    u8 volumeTarget;
    u8 pad11[7];
    u8 numFaded;
} SynthPlayParams;

typedef struct SynthSyncCrossInfo {
    u8 pad00[4];
    u8 vol2;
    u8 pad05[3];
    u32 trackMute2[2];
    u16 speed2;
    u8 flags;
    u8 pad13;
} SynthSyncCrossInfo;

typedef struct SynthSection {
    u8 pad00[0xE];
    u16 speed;
    u8 pad10[0x38 - 0x10];
} SynthSection;

typedef struct SynthVoice {
    u8 pad000[0x11C];
    u32 trackMute[2];
    u8 pad124[0xEC8 - 0x124];
    SynthSyncCrossInfo syncCrossInfo;
    u32* syncSeqIdPtr;
    u8 syncPending;
    u8 padEE1[0x150C - 0xEE1];
    SynthSection section[15];
    u8 pad1854[0x1868 - 0x1854];
} SynthVoice;

typedef struct SynthVoiceRuntime {
    u8 pad[0x1400];
    SynthVoice voices[1];
} SynthVoiceRuntime;

extern SynthVoiceRuntime lbl_8060C020;
extern Node* lbl_8064D398;
extern Node* lbl_8064D39C;
extern void fn_801B3CC8(u8, u16, u32, u8);
extern void fn_801B3B08(u32);
extern u32 fn_801B2914(u32);
extern void fn_801B8D00(u8, u16, u32, u8);
extern void fn_801B8C70(u32);
extern void fn_801B8CA8(u32, u32, u32);
extern void fn_801B8C28(u32, u16);
extern u32 fn_801C3F6C(u16, u16, void*, SynthPlayParams*, u8, u8);
extern u32 fn_801C40AC(u16, u16, void*, SynthPlayParams*, u8);

static inline int resolve_handle(u32 value)
{
    u32 key = value & 0x7FFFFFFF;
    Node* node = lbl_8064D39C;
    while (node != 0) {
        if (node->key == key)
            return node->type | (value & 0x80000000U);
        node = node->next;
    }
    node = lbl_8064D398;
    while (node != 0) {
        if (node->key == key)
            return node->type | (value & 0x80000000U);
        node = node->next;
    }
    return -1;
}

#define seqVolume fn_801B3CC8
#define sndSeqVolume fn_801B8D00
#define seqContinue fn_801B3B08
#define sndSeqContinue fn_801B8C70
#define sndSeqMute fn_801B8CA8
#define sndSeqSpeed fn_801B8C28
#define seqPlaySong fn_801C3F6C
#define sndSeqPlayEx fn_801C40AC
#define seqGetPrivateId fn_801B2914

void fn_801B3E64(SynthStartRequest* ci, u32* new_seqId, u8 irq_call)
{
    SynthVoiceRuntime* runtime;
    SynthPlayParams params;
    u32 deadSlot2;
    u32 slot;
    u32 newHandle;
    u32 mixValue0;
    u32 mixValue1;
    u16 speed;
    u16 fadeTime;
    u8 flags;
    SynthVoice* pendingVoice;
    SynthStartRequest* pendingRequest;

    runtime = &lbl_8060C020;

    slot = resolve_handle(ci->seqId1);
    flags = ci->flags;
    if ((flags & 4) != 0) {
        pendingVoice = (SynthVoice*)((u8*)runtime + slot * sizeof(SynthVoice));
        pendingRequest = (SynthStartRequest*)((u8*)pendingVoice + 0x22B4);
        *pendingRequest = *ci;
        *(u8*)((u8*)pendingVoice + 0x22E0) = 1;
        *(u32**)((u8*)pendingVoice + 0x22DC) = new_seqId;
        pendingRequest->flags &= ~4;
        *new_seqId = ci->seqId1 | 0x80000000;
        return;
    }

    if (irq_call != 0) {
        fadeTime = ci->time1 < 5 ? 5 : ci->time1;
        if ((flags & 1) != 0) {
            seqVolume(0, fadeTime, ci->seqId1, 2);
        } else if ((flags & 0x40) != 0) {
            seqVolume(0, fadeTime, ci->seqId1, 3);
        } else {
            seqVolume(0, fadeTime, ci->seqId1, 1);
        }
    } else {
        if ((flags & 1) != 0) {
            sndSeqVolume(0, ci->time1, ci->seqId1, 2);
        } else if ((flags & 0x40) != 0) {
            sndSeqVolume(0, ci->time1, ci->seqId1, 3);
        } else {
            sndSeqVolume(0, ci->time1, ci->seqId1, 1);
        }
    }

    if (new_seqId == 0) {
        return;
    }

    if ((ci->flags & 2) != 0) {
        if ((slot = resolve_handle(ci->seqId2)) != 0xFFFFFFFF) {
            if (irq_call != 0) {
                seqContinue(ci->seqId2);
                seqVolume(ci->vol2, ci->time2, ci->seqId2, 0);
                if ((ci->flags & 0x10) != 0) {
                    newHandle = ci->seqId2;
                    mixValue1 = ci->trackMute2[1];
                    mixValue0 = ci->trackMute2[0];
                    newHandle = seqGetPrivateId(newHandle);
                    if (newHandle != 0xFFFFFFFF) {
                        if ((newHandle & 0x80000000) == 0) {
                            runtime->voices[newHandle].trackMute[0] = mixValue0;
                            runtime->voices[newHandle].trackMute[1] = mixValue1;
                        } else {
                            runtime->voices[newHandle & 0x7FFFFFFF].syncCrossInfo.flags |= 0x10;
                            runtime->voices[newHandle & 0x7FFFFFFF].syncCrossInfo.trackMute2[0] = mixValue0;
                            runtime->voices[newHandle & 0x7FFFFFFF].syncCrossInfo.trackMute2[1] = mixValue1;
                        }
                    }
                }
                if ((ci->flags & 0x20) != 0) {
                    newHandle = ci->seqId2;
                    speed = ci->speed2;
                    newHandle = seqGetPrivateId(newHandle);
                    if ((newHandle & 0x80000000) == 0) {
                        u32 section;
                        for (section = 0; section < 16; section++) {
                            runtime->voices[newHandle].section[section].speed = speed;
                        }
                    } else {
                        runtime->voices[newHandle & 0x7FFFFFFF].syncCrossInfo.flags |= 0x20;
                        runtime->voices[newHandle & 0x7FFFFFFF].syncCrossInfo.speed2 = speed;
                    }
                }
            } else {
                sndSeqContinue(ci->seqId2);
                sndSeqVolume(ci->vol2, ci->time2, ci->seqId2, 0);
                if ((ci->flags & 0x10) != 0) {
                    sndSeqMute(ci->seqId2, ci->trackMute2[0], ci->trackMute2[1]);
                }
                if ((ci->flags & 0x20) != 0) {
                    sndSeqSpeed(ci->seqId2, ci->speed2);
                }
            }
            *new_seqId = ci->seqId2;
            return;
        }
        *new_seqId = 0xFFFFFFFF;
        return;
    }

    params.flags = 4;
    if ((ci->flags & 8) != 0) {
        params.flags |= 0x10;
    }
    if ((ci->flags & 0x20) != 0) {
        params.flags |= 2;
        params.speed = ci->speed2;
    }
    if ((ci->flags & 0x10) != 0) {
        params.flags |= 1;
        params.trackMute[0] = ci->trackMute2[0];
        params.trackMute[1] = ci->trackMute2[1];
    }
    params.volumeTime = ci->time2;
    params.volumeTarget = ci->vol2;
    params.numFaded = 0;

    if (irq_call != 0) {
        newHandle = seqPlaySong(ci->gid2, ci->sid2, (void*)ci->arr2, &params, 1, ci->studio2);
        *new_seqId = newHandle;
        if ((newHandle != 0xFFFFFFFF) && ((ci->flags & 0x80) != 0)) {
            newHandle = seqGetPrivateId(*new_seqId);
            if (newHandle != 0xFFFFFFFF) {
                if ((newHandle & 0x80000000) == 0) {
                    runtime->voices[newHandle].trackMute[0] = 0;
                    runtime->voices[newHandle].trackMute[1] = 0;
                } else {
                    runtime->voices[newHandle & 0x7FFFFFFF].syncCrossInfo.flags |= 0x10;
                    runtime->voices[newHandle & 0x7FFFFFFF].syncCrossInfo.trackMute2[0] = 0;
                    runtime->voices[newHandle & 0x7FFFFFFF].syncCrossInfo.trackMute2[1] = 0;
                }
            }
        }
    } else {
        newHandle = sndSeqPlayEx(ci->gid2, ci->sid2, (void*)ci->arr2, &params, ci->studio2);
        *new_seqId = newHandle;
        if ((newHandle != 0xFFFFFFFF) && ((ci->flags & 0x80) != 0)) {
            sndSeqMute(*new_seqId, 0, 0);
        }
    }
}
