typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct VoiceLink {
    u8 prev;
    u8 next;
    u16 user;
} VoiceLink;

typedef struct SynthRootListNode {
    u16 next;
    u16 prev;
} SynthRootListNode;

typedef struct SynthInfo {
    u8 pad000[0x210];
    u8 voiceCount;
} SynthInfo;

extern SynthInfo synthInfo;
static u8 vidLists[0x800];
static u8 midiKeySlots[0x80];
static u8 directSlots[0x40];
static VoiceLink voicePriorityLinks[64];
static u8 voicePriorityGroupHeads[256];
static SynthRootListNode voicePrioritySortLinks[256];
static VoiceLink voiceFreeListSlots[64];
extern u16 voicePrioSortRootListRoot;
extern u8 voiceMusicRunning;
extern u8 voiceFxRunning;
extern u8 voiceListInsert;
extern u8 voiceListRoot;

#define voicePrioSortedRoot voicePrioSortRootListRoot
#define voiceFreeListTail voiceListInsert
#define voiceFreeListRoot voiceListRoot

static inline void voiceInitFreeList(void)
{
    u32 i;

    for (i = 0; i < synthInfo.voiceCount; i++) {
        voiceFreeListSlots[i].prev = i - 1;
        voiceFreeListSlots[i].next = i + 1;
        voiceFreeListSlots[i].user = 1;
    }
    voiceFreeListSlots[0].prev = 0xff;
    voiceFreeListSlots[synthInfo.voiceCount - 1].next = 0xff;
    voiceFreeListRoot = 0;
    voiceFreeListTail = synthInfo.voiceCount - 1;
}

static inline void voiceInitPrioSort(void)
{
    u32 i;

    for (i = 0; i < synthInfo.voiceCount; i++) {
        voicePriorityLinks[i].user = 0;
    }
    for (i = 0; i < 0x100; i++) {
        voicePriorityGroupHeads[i] = 0xff;
    }
    voicePrioSortedRoot = 0xffff;
}

void synthInitAllocationAids(void)
{
    voiceInitFreeList();
    voiceInitPrioSort();
    voiceFxRunning = 0;
    voiceMusicRunning = 0;
}
