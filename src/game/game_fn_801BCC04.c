typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct SDIR_TAB {
    void* data;
    void* base;
    u16 numSmp;
    u16 res;
} SDIR_TAB;

typedef struct DATA_TAB {
    void* addr;
    u16 id;
    u16 refCount;
} DATA_TAB;

typedef struct LAYER_TAB {
    void* addr;
    u16 id;
    u16 refCount;
    u32 numEntries;
} LAYER_TAB;

typedef struct MAC_MAINTAB {
    u16 num;
    u16 subTabIndex;
} MAC_MAINTAB;

typedef struct MAC_SUBTAB {
    void* data;
    u16 id;
    u16 refCount;
} MAC_SUBTAB;

static SDIR_TAB dataSmpSDirs[128];
static DATA_TAB dataCurveTable[2048];
static DATA_TAB dataKeymapTable[256];
static LAYER_TAB dataLayerTable[256];
static MAC_MAINTAB dataMacroBucketTable[512];
static MAC_SUBTAB dataMacroTable[2048];

extern u16 lbl_8064D3F8;
extern void fn_801CE2B8(void);
extern void fn_801CE280(void);

#define dataMacTotal lbl_8064D3F8
#define sndBegin fn_801CE2B8
#define sndEnd fn_801CE280

s32 fn_801BCC04(u16 mid)
{
    s32 main;
    s32 base;
    s32 i;

    sndBegin();
    main = (mid >> 6) & 0x3ff;

    if (dataMacroBucketTable[main].num != 0) {
        base = dataMacroBucketTable[main].subTabIndex;
        for (i = 0; i < dataMacroBucketTable[main].num && mid != dataMacroTable[base + i].id; ++i) {
        }

        if (i < dataMacroBucketTable[main].num) {
            if (--dataMacroTable[base + i].refCount == 0) {
                for (i = base + i + 1; i < dataMacTotal; ++i) {
                    dataMacroTable[i - 1] = dataMacroTable[i];
                }

                for (i = 0; i < 512; ++i) {
                    if (dataMacroBucketTable[i].subTabIndex > base) {
                        --dataMacroBucketTable[i].subTabIndex;
                    }
                }

                --dataMacroBucketTable[main].num;
                --dataMacTotal;
            }
        }
    }

    sndEnd();
    return 0;
}
