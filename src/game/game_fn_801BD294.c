typedef unsigned short u16;
typedef unsigned int u32;

extern u16 dataSmpSDirNum;
extern u16 dataCurveNum;
extern u16 dataKeymapNum;
extern u16 dataLayerNum;
extern u16 dataMacTotal;
extern u16 dataFXGroupNum;
typedef struct Bucket {
    u16 count;
    u16 start;
} Bucket;

extern Bucket dataMacMainTab[];
extern void hwInitSampleMem(u32 base, u32 length);

void dataInit(u32 base, u32 length)
{
    long i;

    dataSmpSDirNum = 0;
    dataCurveNum = 0;
    dataKeymapNum = 0;
    dataLayerNum = 0;
    dataFXGroupNum = 0;
    dataMacTotal = 0;
    for (i = 0; i < 512; ++i) {
        dataMacMainTab[i].count = 0;
        dataMacMainTab[i].start = 0;
    }
    hwInitSampleMem(base, length);
}
