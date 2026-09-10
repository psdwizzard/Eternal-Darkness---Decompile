typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;

typedef struct SynthVoiceListNode {
    u8 prev;
    u8 next;
    u16 user;
} SynthVoiceListNode;

typedef struct SynthRootListNode {
    u16 next;
    u16 prev;
} SynthRootListNode;

typedef struct VidListTables {
    u8 vidLists[0x800];
    u8 midiKeySlots[0x80];
    u8 directSlots[0x40];
    SynthVoiceListNode priorityLinks[0x40];
    u8 priorityGroupHeads[0x100];
    SynthRootListNode prioritySortLinks[0x100];
    SynthVoiceListNode freeList[0x40];
} VidListTables;

typedef struct SYNTH_VOICE {
    u8 pad_000[0x100];
    u16 allocId;
    u8 pad_102[0xA];
    u8 prio;
    u8 pad_10D[3];
    u32 age;
    u32 cFlagsHi;
    u32 cFlagsLo;
    u8 block;
    u8 fxFlag;
    u8 pad_11E[0x2E6];
} SYNTH_VOICE;

typedef struct SynthInfo {
    u8 pad000[0x210];
    u8 voiceCount;
    u8 musicVoiceCount;
    u8 fxVoiceCount;
} SynthInfo;

extern VidListTables lbl_80626DA0;
extern SynthInfo lbl_80619C20;
extern SYNTH_VOICE* lbl_8064D3D0;
extern u8 lbl_8064D3D8;
extern u16 lbl_8064D464;
extern u8 lbl_8064D466;
extern u8 lbl_8064D467;
extern u8 lbl_8064D468;
extern u8 lbl_8064D469;

#define vidList (&lbl_80626DA0)
#define SYNTH_CONFIGURATION (&lbl_80619C20)
#define synthVoice lbl_8064D3D0
#define synthIdleWaitActive lbl_8064D3D8
#define voicePrioSortedRoot lbl_8064D464
#define voiceMusicRunning lbl_8064D466
#define voiceFxRunning lbl_8064D467
#define voiceFreeListTail lbl_8064D468
#define voiceFreeListRoot lbl_8064D469
#define offsetof(type, member) ((u32)&((type*)0)->member)
#define VB_PRIO_HEAD(vb, p) (*(u8*)((u8*)&(vb)->priorityGroupHeads[0] + (p)))
#define VB_PRIO_LINK_NEXT(vb, i) (((SynthVoiceListNode*)((u8*)&(vb)->priorityLinks[0] + (i) * 4))->next)
#define VB_PRIO_SORT_NEXT(vb, p) (((SynthRootListNode*)&(vb)->prioritySortLinks[0])[p].next)
#define VOICE_CFLAGS(i) (*(u64*)&synthVoice[i].cFlagsHi)

u32 fn_801C1790(u8 priority, u8 maxInstances, u16 allocId, u8 fxFlag)
{
    s32 i;
    s32 allocationCount;
    s32 selectedVoice;
    u16 prio;
    u32 restrictToStreamKind;
    u16 priorityGroupIndex;
    SynthVoiceListNode* freeSlot;
    SynthVoiceListNode* slotBase;
    VidListTables* voiceLists = (VidListTables*)vidList;

    if (!synthIdleWaitActive) {
        if (fxFlag) {
            restrictToStreamKind = (voiceFxRunning >= SYNTH_CONFIGURATION->fxVoiceCount &&
                                    SYNTH_CONFIGURATION->voiceCount > SYNTH_CONFIGURATION->fxVoiceCount);

            if (SYNTH_CONFIGURATION->fxVoiceCount <= maxInstances) {
                goto steal;
            }
        } else {
            restrictToStreamKind = (voiceMusicRunning >= SYNTH_CONFIGURATION->musicVoiceCount &&
                                    SYNTH_CONFIGURATION->voiceCount > SYNTH_CONFIGURATION->musicVoiceCount);

            if (SYNTH_CONFIGURATION->musicVoiceCount <= maxInstances) {
                goto steal;
            }
        }

        {
            allocationCount = 0;
            selectedVoice = -1;

            prio = voicePrioSortedRoot;
            while (prio != 0xFFFF && priority >= prio && selectedVoice == -1) {
                u32 group = prio;
                for (i = VB_PRIO_HEAD(voiceLists, group); i != 0xFF; i = VB_PRIO_LINK_NEXT(voiceLists, i)) {
                    if (allocId != synthVoice[i].allocId)
                        continue;
                    ++allocationCount;
                    if (synthVoice[i].block)
                        continue;

                    if (!restrictToStreamKind || fxFlag == synthVoice[i].fxFlag) {
                        if (VOICE_CFLAGS(i) & 2)
                            continue;
                        if (selectedVoice != -1) {
                            if (synthVoice[i].age < synthVoice[selectedVoice].age)
                                selectedVoice = i;
                        } else
                            selectedVoice = i;
                    }
                }

                prio = VB_PRIO_SORT_NEXT(voiceLists, group);
            }

            if (allocationCount >= maxInstances) {
                goto have_voice;
            }

            while (prio != 0xFFFF && allocationCount < maxInstances) {
                u32 group = prio;
                i = VB_PRIO_HEAD(voiceLists, group);
                while (i != 0xFF) {
                    if (allocId == synthVoice[i].allocId) {
                        allocationCount++;
                    }

                    i = VB_PRIO_LINK_NEXT(voiceLists, i);
                }

                prio = VB_PRIO_SORT_NEXT(voiceLists, group);
            }

            if (allocationCount >= maxInstances) {
                goto have_voice;
            }
        }

    steal:
        {
            selectedVoice = -1;
            if (voiceFreeListRoot != 0xFF && restrictToStreamKind == 0) {
                selectedVoice = voiceFreeListRoot;
            } else {
                if (priority < voicePrioSortedRoot) {
                    return 0xFFFFFFFF;
                }

                prio = voicePrioSortedRoot;

                while (prio != 0xFFFF && priority >= prio && selectedVoice == -1) {
                    priorityGroupIndex = prio;
                    for (i = VB_PRIO_HEAD(voiceLists, priorityGroupIndex); i != 0xFF; i = VB_PRIO_LINK_NEXT(voiceLists, i)) {
                        if ((synthVoice[i].block == 0) && (!restrictToStreamKind || fxFlag == synthVoice[i].fxFlag)) {
                            if ((VOICE_CFLAGS(i) & 2) == 0) {
                                if (selectedVoice != -1) {
                                    if (synthVoice[selectedVoice].age > synthVoice[i].age)
                                        selectedVoice = i;
                                } else {
                                    selectedVoice = i;
                                }
                            }
                        }
                    }
                    prio = VB_PRIO_SORT_NEXT(voiceLists, priorityGroupIndex);
                }

                if (selectedVoice == -1) {
                    return 0xFFFFFFFF;
                }
            }

            if (synthVoice[selectedVoice].prio > priority) {
                goto ret_invalid;
            }
        }

    have_voice:
        if (selectedVoice == -1) {
            goto ret_invalid;
        }

        slotBase = (SynthVoiceListNode*)((u8*)voiceLists + selectedVoice * 4);
        if (slotBase[offsetof(VidListTables, freeList) / sizeof(*slotBase)].user == 1) {
            freeSlot = (SynthVoiceListNode*)((u8*)slotBase + offsetof(VidListTables, freeList));
            i = freeSlot->prev;

            if (i != 0xFF) {
                voiceLists->freeList[i].next = freeSlot->next;
            } else {
                voiceFreeListRoot = freeSlot->next;
            }

            i = freeSlot->next;
            if (i != 0xFF) {
                voiceLists->freeList[i].prev = freeSlot->prev;
            }

            if (selectedVoice == voiceFreeListTail) {
                voiceFreeListTail = freeSlot->prev;
            }

            freeSlot->user = 0;
        } else if (synthVoice[selectedVoice].fxFlag) {
            voiceFxRunning--;
        } else {
            voiceMusicRunning--;
        }
        if (fxFlag != 0) {
            ++voiceFxRunning;
        } else {
            ++voiceMusicRunning;
        }
        return selectedVoice;
    }

ret_invalid:
    return 0xFFFFFFFF;
}
