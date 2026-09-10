typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

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
    u8 pad_000[0xF4];
    u32 id;
    u8 pad_0F8[0x14];
    u8 prio;
    u8 pad_10D[3];
    u32 age;
} SYNTH_VOICE;

extern VidListTables lbl_80626DA0;
extern u16 lbl_8064D464;

#define vidList (&lbl_80626DA0)
#define voicePrioSortedRoot lbl_8064D464
#define offsetof(type, member) ((u32)&((type*)0)->member)
extern void fn_801C1520(SYNTH_VOICE* s);
extern void fn_801CC704(u32, u32);

#define VB_PRIO_HEAD(vb, p) (*(u8*)((u8*)&(vb)->priorityGroupHeads[0] + (p)))
#define VB_PRIO_LINK(vb, i) ((SynthVoiceListNode*)((u8*)&(vb)->priorityLinks[0] + (i) * sizeof(SynthVoiceListNode)))
#define VB_PRIO_SORT_NEXT(vb, p) (((SynthRootListNode*)&(vb)->prioritySortLinks[0])[p].next)
#define VB_PRIO_SORT_PREV(vb, p) (((SynthRootListNode*)((u8*)&(vb)->prioritySortLinks[0] + offsetof(SynthRootListNode, prev)))[p].next)

void fn_801C1600(SYNTH_VOICE* svoice, u8 prio)
{
    u32 voiceIdx;
    VidListTables* vb;
    u16 li;
    SynthVoiceListNode* vps;
    u16 root;
    u16 i;
    u32 p;
    u8* head;

    voiceIdx = (u8)svoice->id;
    vb = (VidListTables*)vidList;
    vps = VB_PRIO_LINK(vb, voiceIdx);
    if (vps->user == 1) {
        if (svoice->prio == prio) {
            return;
        }

        fn_801C1520(svoice);
    }

    vps->user = 1;
    p = prio;
    head = &VB_PRIO_HEAD(vb, p);
    vps->prev = 0xff;
    if ((vps->next = *head) != 0xFF) {
        VB_PRIO_LINK(vb, *head)->prev = voiceIdx;
    } else if (root = voicePrioSortedRoot, root != 0xFFFF) {
        if (prio >= root) {
            for (i = root; i != 0xFFFF; i = VB_PRIO_SORT_NEXT(vb, i)) {
                if (i > prio) {
                    break;
                }
                li = i;
            }

            VB_PRIO_SORT_NEXT(vb, li) = prio;
            VB_PRIO_SORT_PREV(vb, p) = li;
            VB_PRIO_SORT_NEXT(vb, p) = i;
            if (i != 0xFFFF) {
                VB_PRIO_SORT_PREV(vb, i) = prio;
            }
        } else {
            VB_PRIO_SORT_NEXT(vb, p) = root;
            VB_PRIO_SORT_PREV(vb, p) = 0xFFFF;
            VB_PRIO_SORT_PREV(vb, root) = prio;
            voicePrioSortedRoot = prio;
        }
    } else {
        VB_PRIO_SORT_NEXT(vb, p) = 0xFFFF;
        VB_PRIO_SORT_PREV(vb, p) = 0xFFFF;
        voicePrioSortedRoot = prio;
    }

    *head = voiceIdx;
    svoice->prio = prio;
    fn_801CC704(svoice->id & 0xFF, ((u32)prio << 24) | (svoice->age >> 15));
}
