typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

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

static SDIR_TAB dataSmpSDirsStatic[128];
extern u16 lbl_8064D3F0;
extern void fn_801CE2B8(void);
extern void fn_801CE280(void);

#define dataSmpSDirs dataSmpSDirsStatic
#define dataSmpSDirNum lbl_8064D3F0

static inline void dataFindSampleDir(SDIR_DATA* sample, s32* dirIndex, u16* k)
{
    for (*dirIndex = 0; *dirIndex < dataSmpSDirNum; ++*dirIndex) {
        for (*k = 0; *k < dataSmpSDirs[*dirIndex].numSmp; ++*k) {
            if (sample->id == dataSmpSDirs[*dirIndex].data[*k].id)
                return;
        }
    }
}

u32 fn_801BC0D4(SDIR_DATA* sdir, void* smp_data)
{
    s32 i;
    SDIR_DATA* s;
    u16 n;
    u16 j;
    u16 k;

    for (i = 0; i < dataSmpSDirNum && dataSmpSDirs[i].data != sdir; ++i)
        ;

    if (i == dataSmpSDirNum) {
        if (dataSmpSDirNum < 128) {
            n = 0;
            for (s = sdir; s->id != 0xFFFF; ++s) {
                ++n;
            }

            fn_801CE2B8();
            for (j = 0; j < n; ++j) {
                dataFindSampleDir(&sdir[j], &i, &k);
                if (i != dataSmpSDirNum) {
                    sdir[j].ref_cnt = 0xFFFF;
                } else {
                    sdir[j].ref_cnt = 0;
                }
            }

            dataSmpSDirs[dataSmpSDirNum].data = sdir;
            dataSmpSDirs[dataSmpSDirNum].numSmp = n;
            dataSmpSDirs[dataSmpSDirNum].base = smp_data;
            ++dataSmpSDirNum;
            fn_801CE280();
            return 1;
        } else {
            return 0;
        }
    }

    return 1;
}
