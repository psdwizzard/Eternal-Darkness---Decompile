typedef unsigned short u16;

typedef struct Bucket {
    u16 count;
    u16 start;
} Bucket;

typedef struct ResourceEntry8 {
    void* value;
    u16 id;
    u16 references;
} ResourceEntry8;

extern unsigned char lbl_8061C748[];
extern unsigned int lbl_8064D3FC;
extern unsigned int lbl_8064D400;
extern ResourceEntry8 lbl_8064D404;
extern ResourceEntry8* lbl_8064D40C;

extern int maccmp(ResourceEntry8*, ResourceEntry8*);
extern void* sndBSearch(void*, void*, unsigned int, unsigned int,
                        int (*)(ResourceEntry8*, ResourceEntry8*));

void* dataGetMacro(u16 id)
{
    unsigned char* base = lbl_8061C748;
    u16 count;
    lbl_8064D400 = id >> 6;
    count = ((Bucket*)(base + 0x5A00))[lbl_8064D400].count;
    if (count != 0) {
        lbl_8064D3FC = ((Bucket*)(base + 0x5A00))[lbl_8064D400].start;
        lbl_8064D404.id = id;
        if ((lbl_8064D40C = sndBSearch(
                 &lbl_8064D404,
                 &((ResourceEntry8*)(base + 0x6200))[lbl_8064D3FC],
                 count,
                 sizeof(ResourceEntry8), maccmp)) != 0) {
            return lbl_8064D40C->value;
        }
    }
    return 0;
}
