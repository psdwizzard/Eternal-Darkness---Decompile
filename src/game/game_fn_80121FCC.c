typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    u32 a, b, c, d;
} Entry;

typedef struct DisplayList {
    u32* data;
    u32 unk4;
    Entry* entries;
    int size;
    int count;
    u32 unk14, unk18, unk1C;
} DisplayList;

typedef struct TransferState {
    void* source;
    void* destination;
    u16 count;
    u16 pad;
    int remaining;
    u32 transferred;
    u32 unk14;
    int size;
} TransferState;

extern int lbl_8064CEC8;
extern u32* lbl_8064CECC;
extern Entry* lbl_8064CED4;
extern int lbl_8064CED8;
extern u32 lbl_8064CEDC[2];
extern int lbl_8064D738;

TransferState fn_80121FCC(DisplayList* src, DisplayList* dst)
{
    TransferState state;
    int i;

    *dst = *src;
    dst->data = lbl_8064CECC;
    dst->entries = lbl_8064CED4;
    for (i = 0; i < dst->count; i++) {
        dst->entries[i] = src->entries[i];
    }
    state.source = src->data;
    state.destination = dst->data;
    state.remaining = src->size;
    state.size = src->size;
    state.transferred = 0;
    state.count = (src->size >> 12) + ((src->size & 0xFFF) > 0);
    lbl_8064CEC8 -= src->size;
    lbl_8064CED8 -= src->count;
    lbl_8064CED4 += dst->count;
    lbl_8064CECC = (u32*)((char*)lbl_8064CECC + dst->size);
    ++lbl_8064CEDC[lbl_8064D738];
    return state;
}
