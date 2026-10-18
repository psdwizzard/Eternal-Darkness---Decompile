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

extern u8 sndActive;
extern s16 sp;
extern ResourceLoad gs[];
extern u32 hwTransAddr(u32);
extern u32 dataInsertSDir(void*, u32);
extern void ScanIDList(u16*, void*, u8, void*);
extern u32 dataInsertFX(u16, void*, u16);
extern void hwSyncSampleMem(void);

int sndPushGroup(ResourceNode* prj_data, u16 gid, u32 kind, void* sdir, void* pool)
{
    ResourceNode* g;
    u16* sampleRef;
    ResourceLoad* gsTab = gs;
    s16 curSp;
    void* poolPtr;

    if (sndActive && (curSp = sp) < 128) {
        g = prj_data;

        while (g->next != 0xFFFFFFFF) {
            if (g->id == gid) {
                gsTab[curSp].node = g;
                gsTab[curSp].base = prj_data;
                poolPtr = pool;
                gsTab[curSp].archive = sdir;
                sampleRef = (u16*)((u8*)prj_data + g->list1);
                if (dataInsertSDir(sdir, hwTransAddr(kind))) {
                    ScanIDList(sampleRef, sdir, 1, 0);
                }
                ScanIDList((u16*)((u8*)prj_data + g->list0), poolPtr, 0, 0);
                ScanIDList((u16*)((u8*)prj_data + g->list4), poolPtr, 4, 0);
                ScanIDList((u16*)((u8*)prj_data + g->list2), pool, 2, 0);
                ScanIDList((u16*)((u8*)prj_data + g->list3), pool, 3, 0);
                if (g->flags == 1) {
                    u8* fd = (u8*)prj_data + g->extra;
                    dataInsertFX(gid, fd + 4, *(u16*)fd);
                }
                hwSyncSampleMem();
                ++sp;
                return 1;
            }

            g = (ResourceNode*)((u8*)prj_data + *(u32*)g);
        }
    }

    return 0;
}
