typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct FX_TAB {
    u16 id;
    u8 pad02[7];
    u8 vGroup;
} FX_TAB;

typedef struct FX_GROUP {
    u16 gid;
    u16 fxNum;
    FX_TAB* fxTab;
} FX_GROUP;

typedef struct SynthDataTables {
    u8 pad0000[0xA200];
    FX_GROUP fxGroup[128];
} SynthDataTables;

extern u8 lbl_8061C748[];
extern u16 lbl_8064D3FA;
extern void fn_801CE2B8(void);
extern void fn_801CE280(void);

#define dataSmpSDirs lbl_8061C748
#define dataFXGroupNum lbl_8064D3FA

u32 fn_801BC670(u16 gid, FX_TAB* fx, u16 fxNum)
{
    long i;
    FX_GROUP* g;
    SynthDataTables* t = (SynthDataTables*)dataSmpSDirs;

    g = t->fxGroup;
    for (i = 0; i < dataFXGroupNum && gid != g[i].gid; ++i) {
    }

    if (i == dataFXGroupNum && dataFXGroupNum < 128) {
        fn_801CE2B8();
        i = dataFXGroupNum;
        t->fxGroup[i].gid = gid;
        t->fxGroup[i].fxNum = fxNum;
        t->fxGroup[i].fxTab = fx;

        for (i = 0; i < fxNum; ++i, ++fx) {
            fx->vGroup = 31;
        }

        dataFXGroupNum++;
        fn_801CE280();
        return 1;
    }
    return 0;
}
