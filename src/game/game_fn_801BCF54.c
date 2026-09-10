typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct SDIR_DATA {
    u16 id;
    u16 ref_cnt;
    u32 pad04;
    u32 addr;
    u32 info;
    u32 length;
    u32 loopOffset;
    u32 loopLength;
    u32 extraData;
} SDIR_DATA;

typedef struct SAMPLE_HEADER {
    u32 info;
    u32 length;
    u32 loopOffset;
    u32 loopLength;
} SAMPLE_HEADER;

typedef struct SAMPLE_INFO {
    u32 info;
    u32 addr;
    void* extraData;
    u32 offset;
    u32 length;
    u32 loop;
    u32 loopLength;
    u8 compType;
} SAMPLE_INFO;

typedef struct SDIR_TAB {
    SDIR_DATA* data;
    u32 pad;
    u16 numSmp;
    u16 pad0A;
} SDIR_TAB;

typedef struct SynthDataTables {
    SDIR_TAB sdir[0x800];
    u8 pad6000[0x4600];
    SDIR_DATA getSampleKey;
} SynthDataTables;

extern u8 lbl_8061C748[];
extern u16 lbl_8064D3F0;
extern SDIR_DATA* lbl_8064D410;
extern SAMPLE_HEADER* lbl_8064D414;
extern s32 fn_801BCF44(void*, void*);
extern void* fn_801CC370(void*, void*, int, u32, s32 (*)(void*, void*));

#define dataSmpSDirs lbl_8061C748
#define dataSmpSDirNum lbl_8064D3F0
#define dataGetSample_result lbl_8064D410
#define dataGetSample_sheader lbl_8064D414

s32 fn_801BCF54(u16 sid, SAMPLE_INFO* newsmp)
{
    long i;
    SynthDataTables* t = (SynthDataTables*)dataSmpSDirs;

    t->getSampleKey.id = sid;

    for (i = 0; i < dataSmpSDirNum; ++i) {
        if ((dataGetSample_result = (SDIR_DATA*)fn_801CC370(&t->getSampleKey, t->sdir[i].data, t->sdir[i].numSmp, sizeof(SDIR_DATA), fn_801BCF44)) != 0) {
            if (dataGetSample_result->ref_cnt != 0xFFFF) {
                dataGetSample_sheader = (SAMPLE_HEADER*)&dataGetSample_result->info;
                newsmp->info = dataGetSample_sheader->info;
                newsmp->addr = dataGetSample_result->addr;
                newsmp->offset = 0;
                newsmp->loop = dataGetSample_sheader->loopOffset;
                newsmp->length = dataGetSample_sheader->length & 0xFFFFFF;
                newsmp->loopLength = dataGetSample_sheader->loopLength;
                newsmp->compType = dataGetSample_sheader->length >> 24;

                if (dataGetSample_result->extraData) {
                    newsmp->extraData = (void*)((u32) & (t->sdir[i].data)->id + dataGetSample_result->extraData);
                }
                return 0;
            }
        }
    }

    return -1;
}
