typedef unsigned int u32;

typedef struct Entry {
    u32 a;
    u32 b;
    u32 c;
    u32 d;
} Entry;

typedef struct DisplayList {
    u32* data;
    u32 unk4;
    Entry* entries;
    int size;
    int count;
    u32 unk14;
    u32 unk18;
    u32 unk1C;
} DisplayList;

extern int lbl_8064CEC8;
extern u32* lbl_8064CECC;
extern Entry* lbl_8064CED4;
extern int lbl_8064CED8;

extern volatile u32* GXRedirectWriteGatherPipe(volatile u32*);
extern void GXRestoreWriteGatherPipe(void);
extern void DCInvalidateRange(void*, u32);

void fn_80121AE4(DisplayList* src, DisplayList* dst)
{
    int i;
    int j;
    int blocks;
    u32* data;
    volatile u32* fifo;

    *dst = *src;
    dst->data = lbl_8064CECC;
    dst->entries = lbl_8064CED4;
    for (i = 0; i < dst->count; i++) {
        dst->entries[i] = src->entries[i];
    }

    data = src->data;
    blocks = src->size >> 5;
    fifo = GXRedirectWriteGatherPipe(dst->data);
    for (j = 0; j < blocks; j++) {
        *fifo = *data++;
        *fifo = *data++;
        *fifo = *data++;
        *fifo = *data++;
        *fifo = *data++;
        *fifo = *data++;
        *fifo = *data++;
        *fifo = *data++;
    }
    GXRestoreWriteGatherPipe();

    lbl_8064CEC8 -= src->size;
    lbl_8064CED8 -= dst->count;
    lbl_8064CED4 += dst->count;
    lbl_8064CECC = (u32*)((char*)lbl_8064CECC + dst->size);
    DCInvalidateRange(src->data, src->size);
}
