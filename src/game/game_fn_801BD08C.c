typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    void* value;
    u16 id;
    u16 padding;
} Entry;

extern Entry lbl_8064D418;
extern Entry dataCurveTab[];
extern u16 dataCurveNum;
extern Entry* lbl_8064D420;
extern int curvecmp(void*, void*);
extern void* sndBSearch(void*, void*, u32, u32, int (*)(void*, void*));

void* dataGetCurve(u16 id)
{
    lbl_8064D418.id = id;
    if ((lbl_8064D420 = sndBSearch(&lbl_8064D418, dataCurveTab,
                                    dataCurveNum, sizeof(Entry),
                                    curvecmp)) != 0) {
        return lbl_8064D420->value;
    }
    return 0;
}
