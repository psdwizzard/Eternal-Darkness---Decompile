typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ResourceNode {
    u32 next;
    u16 id;
    u16 flags;
    u32 list0;
    u32 list1;
    u32 list4;
    u32 list2;
    u32 list3;
    u32 extra;
} ResourceNode;

typedef struct ResourceLoad {
    ResourceNode* node;
    void* archive;
    ResourceNode* base;
} ResourceLoad;

extern s16 sp;
extern ResourceLoad gs[];
extern void hwDisableIrq(void);
extern void s3dKillEmitterByFXID(void*, u16);
extern void seqKillInstancesByGroupID(u16);
extern void synthKillVoicesByMacroReferences(void*);
extern void hwEnableIrq(void);
extern void ScanIDListReverse(u16*, void*, u8, void*);
extern void dataRemoveSDir(void*);
extern void ScanIDList(u16*, void*, u8, void*);
extern void dataRemoveFX(u16);

int sndPopGroup(void)
{
    ResourceNode* node;
    void* archive;
    ResourceNode* base;
    u8* extra;

    node = gs[sp-- - 1].node;
    base = gs[sp].base;
    archive = gs[sp].archive;

    hwDisableIrq();
    if (node->flags == 1) {
        extra = (u8*)base + node->extra;
        s3dKillEmitterByFXID(extra + 4, *(u16*)extra);
    } else {
        seqKillInstancesByGroupID(node->id);
    }
    synthKillVoicesByMacroReferences((u8*)base + node->list0);
    hwEnableIrq();
    ScanIDListReverse((u16*)((u8*)base + node->list1), 0, 1, (void*)1);
    dataRemoveSDir(archive);
    ScanIDList((u16*)((u8*)base + node->list0), 0, 0, (void*)1);
    ScanIDList((u16*)((u8*)base + node->list4), 0, 4, (void*)1);
    ScanIDList((u16*)((u8*)base + node->list2), 0, 2, (void*)1);
    ScanIDList((u16*)((u8*)base + node->list3), 0, 3, (void*)1);
    if (node->flags == 1) {
        dataRemoveFX(node->id);
    }
    return 1;
}
