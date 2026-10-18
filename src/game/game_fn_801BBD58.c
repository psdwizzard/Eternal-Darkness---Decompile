typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct SDIR_TAB {
    u8 pad[12];
} SDIR_TAB;

typedef struct DATA_TAB {
    void* data;
    u16 id;
    u16 refCount;
} DATA_TAB;

typedef struct SynthDataTables {
    SDIR_TAB sdir[128];
    DATA_TAB curve[2048];
} SynthDataTables;

extern u8 lbl_8061C748[];
extern u16 dataCurveNum;
extern void hwDisableIrq(void);
extern void hwEnableIrq(void);

#define dataSmpSDirs lbl_8061C748

s32 dataInsertCurve(u16 cid, void* curvedata)
{
    long i;
    long j;
    SynthDataTables* t = (SynthDataTables*)dataSmpSDirs;

    hwDisableIrq();

    for (i = 0; i < dataCurveNum && ((DATA_TAB*)((u8*)t + 0x600))[i].id < cid; ++i)
        ;

    if (i < dataCurveNum) {
        if (cid != t->curve[i].id) {
            if (dataCurveNum < 2048) {
                for (j = dataCurveNum - 1; j >= i; --j)
                    ((DATA_TAB*)(t->sdir + 128))[j + 1] = ((DATA_TAB*)(t->sdir + 128))[j];
                ++dataCurveNum;
            } else {
                hwEnableIrq();
                return 0;
            }
        } else {
            hwEnableIrq();
            t->curve[i].refCount++;
            return 0;
        }
    } else if (dataCurveNum < 2048) {
        ++dataCurveNum;
    } else {
        hwEnableIrq();
        return 0;
    }

    t->curve[i].id = cid;
    t->curve[i].data = curvedata;
    t->curve[i].refCount = 1;
    hwEnableIrq();
    return 1;
}
