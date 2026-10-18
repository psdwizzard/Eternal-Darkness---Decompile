typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    void* value;
    u16 id;
    u16 padding;
} Entry;

extern Entry lbl_8064D424;
extern Entry dataKeymapTab[];
extern u16 dataKeymapNum;
extern Entry* lbl_8064D42C;
extern int curvecmp(void*, void*);
extern void* sndBSearch(void*, void*, u32, u32, int (*)(void*, void*));

void* dataGetKeymap(u16 id)
{
    lbl_8064D424.id = id;
    if ((lbl_8064D42C = sndBSearch(&lbl_8064D424, dataKeymapTab,
                                    dataKeymapNum, sizeof(Entry),
                                    curvecmp)) != 0) {
        return lbl_8064D42C->value;
    }
    return 0;
}
