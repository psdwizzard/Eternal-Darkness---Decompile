typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct FX_TAB {
    u16 id;
    u8 pad[8];
} FX_TAB;

typedef struct FX_GROUP {
    u16 pad;
    u16 fxNum;
    FX_TAB* fxTab;
} FX_GROUP;

typedef struct SynthDataTables {
    u8 pad0000[0xA200];
    FX_GROUP fxGroup[128];
    u8 getSampleKey[0x2C];
    FX_TAB getFXKey;
} SynthDataTables;

extern u8 lbl_8061C748[];
extern u16 lbl_8064D3FA;
extern s32 fn_801BD1DC(void*, void*);
extern void* fn_801CC370(void*, void*, int, u32, s32 (*)(void*, void*));

#define dataSmpSDirs lbl_8061C748
#define dataFXGroupNum lbl_8064D3FA

FX_TAB* fn_801BD1EC(u16 fid)
{
    FX_TAB* ret;
    long i;
    FX_TAB* tab;
    SynthDataTables* t = (SynthDataTables*)dataSmpSDirs;
    FX_GROUP* g;
    int zero;

    t->getFXKey.id = fid;
    g = t->fxGroup;
    for (i = (zero = 0); i < dataFXGroupNum; ++i) {
        tab = g[i].fxTab;
        if ((ret = (FX_TAB*)fn_801CC370(&t->getFXKey, tab, g[i].fxNum, sizeof(FX_TAB), fn_801BD1DC))) {
            return ret;
        }
    }

    return 0;
}
