typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    void* value;
    u16 id;
    u16 count;
    u32 unused8;
} Entry;

extern u8 lbl_8061C748[];
extern u16 dataLayerNum;
extern Entry* lbl_8064D430;
extern int layercmp(void*, void*);
extern void* sndBSearch(void*, void*, u32, u32, int (*)(void*, void*));

void* dataGetLayer(u16 id, u16* count)
{
    u8* base = lbl_8061C748;
    *(u16*)(base + 0xA624) = id;
    if ((lbl_8064D430 = sndBSearch(base + 0xA620, base + 0x4E00,
                                    dataLayerNum, sizeof(Entry),
                                    layercmp)) != 0) {
        *count = lbl_8064D430->count;
        return lbl_8064D430->value;
    }
    return 0;
}
