typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct SDIR_DATA {
    u16 id;
    u16 ref_cnt;
    u8 pad04[0x1C];
} SDIR_DATA;

typedef struct SDIR_TAB {
    SDIR_DATA* data;
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

extern u16 lbl_8064D3F0;
extern u16 lbl_8064D3F8;
extern void fn_801CE2B8(void);
extern void fn_801CE280(void);

#define dataMacTotal lbl_8064D3F8
#define dataSmpSDirNum lbl_8064D3F0
#define sndBegin fn_801CE2B8
#define sndEnd fn_801CE280


s32 fn_801BC240(SDIR_DATA* sdir)
{
    long i;
    long j;
    long index;
    SDIR_DATA* data;

    index = 0;
    for (; index < dataSmpSDirNum && dataSmpSDirs[index].data != sdir; ++index) {
    }

    if (index != dataSmpSDirNum) {
        sndBegin();

        for (data = sdir; data->id != 0xFFFF; ++data) {
            if (data->ref_cnt != 0xFFFF && data->ref_cnt != 0) {
                break;
            }
        }

        if (data->id == 0xFFFF) {
            data = sdir;

            for (data = sdir; data->id != 0xFFFF; ++data) {
                if (data->ref_cnt != 0xFFFF) {
                    for (i = 0; i < dataSmpSDirNum; ++i) {
                        if (dataSmpSDirs[i].data == sdir) {
                            continue;
                        }
                        for (j = 0; j < dataSmpSDirs[i].numSmp; ++j) {
                            if (data->id == dataSmpSDirs[i].data[j].id &&
                                dataSmpSDirs[i].data[j].ref_cnt == 0xFFFF) {
                                dataSmpSDirs[i].data[j].ref_cnt = 0;
                                break;
                            }
                        }

                        if (j != dataSmpSDirs[i].numSmp) {
                            break;
                        }
                    }
                }
            }

            for (data = sdir; data->id != 0xFFFF; ++data) {
                data->ref_cnt = 0;
            }

            for (j = index + 1; j < dataSmpSDirNum; ++j) {
                dataSmpSDirs[j - 1] = dataSmpSDirs[j];
            }

            --dataSmpSDirNum;
            sndEnd();
            return 1;
        }

        sndEnd();
    }
    return 0;
}
