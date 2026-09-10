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

void fn_801C1520(SYNTH_VOICE* s)
{
    VidListTables* vb;
    SynthVoiceListNode* vps;
    SynthRootListNode* pr;

    vb = (VidListTables*)vidList;
    vps = &((SynthVoiceListNode*)((u8*)vb + offsetof(VidListTables, priorityLinks)))[s->id & 0xff];
    if (vps->user != 1) {
        return;
    }
    if (vps->prev != 0xff) {
        vb->priorityLinks[vps->prev].next = vps->next;
    } else {
        vb->priorityGroupHeads[s->prio] = vps->next;
    }
    if (vps->next != 0xff) {
        vb->priorityLinks[vps->next].prev = vps->prev;
    } else if (vps->prev == 0xff) {
        u32 prevv;
        pr = &((SynthRootListNode*)((u8*)vb + offsetof(VidListTables, prioritySortLinks)))[s->prio];
        prevv = pr->prev;
        if (prevv != 0xffff) {
            vb->prioritySortLinks[prevv].next = pr->next;
        } else {
            voicePrioSortedRoot = pr->next;
        }
        if (pr->next != 0xffff) {
            vb->prioritySortLinks[pr->next].prev = pr->prev;
        }
    }
    vps->user = 0;
}
