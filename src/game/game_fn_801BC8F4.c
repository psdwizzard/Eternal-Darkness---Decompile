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

s32 fn_801BC8F4(u16 mid, void* macroaddr)
{
    u32 main;
    long pos;
    long base;
    long i;

    sndBegin();

    main = mid >> 6;

    if (dataMacroBucketTable[main].num == 0) {
        pos = base = dataMacroBucketTable[main].subTabIndex = dataMacTotal;
    } else {
        base = dataMacroBucketTable[main].subTabIndex;
        for (i = 0; i < dataMacroBucketTable[main].num && dataMacroTable[base + i].id < mid; ++i) {
        }

        if (i < dataMacroBucketTable[main].num) {
            pos = base + i;
            if (mid == dataMacroTable[pos].id) {
                dataMacroTable[pos].refCount++;
                sndEnd();
                return 0;
            }
        } else {
            pos = base + i;
        }
    }

    if (dataMacTotal < 2048) {
        for (i = 0; i < 512; ++i) {
            if (dataMacroBucketTable[i].subTabIndex > base) {
                dataMacroBucketTable[i].subTabIndex++;
            }
        }

        for (i = dataMacTotal - 1; i >= pos; --i) {
            dataMacroTable[i + 1] = dataMacroTable[i];
        }

        dataMacroTable[pos].id = mid;
        dataMacroTable[pos].data = macroaddr;
        dataMacroTable[pos].refCount = 1;
        dataMacroBucketTable[main].num++;
        dataMacTotal++;
        sndEnd();
        return 1;
    }
    sndEnd();
    return 0;
}
