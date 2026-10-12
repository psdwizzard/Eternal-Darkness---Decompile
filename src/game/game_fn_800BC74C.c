typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SourceEntry {
    u8 pad0[6];
    u8 count;
    u8 pad7;
    void **items;
} SourceEntry;

typedef struct Collection {
    u8 pad0[0x60];
    u16 count;
    u8 pad3e[2];
    u8 *entries;
} Collection;

typedef struct CacheEntry {
    u32 *source;
    u8 pad4[0x31];
    u8 count;
    u8 index;
} CacheEntry;

extern Collection *fn_8015C390(int);
extern void *fn_800BC100(void *, void *, int *, int, int, int, int);
extern void *memset(void *, int, unsigned int);
extern int lbl_8064CA70;
extern CacheEntry *lbl_8064CA74;
extern int lbl_8064D18C;

void fn_800BC74C(register int reset)
{
    register Collection *collection;
    register SourceEntry *source;
    register void *item;
    register int i;
    register int j;
    register int offset;
    int value;
    register void *result;

    collection = fn_8015C390(2);
    if (reset != 0) {
        lbl_8064CA70 = 0;
    }
    if (lbl_8064CA70 != lbl_8064D18C) {
        lbl_8064CA70 = lbl_8064D18C;
        memset(lbl_8064CA74, 0, 0x6D60);
        source = (SourceEntry *)collection->entries;
        for (i = 0; i < collection->count; i++, source++) {
            lbl_8064CA74[i].source = (u32 *)source;
            lbl_8064CA74[i].index = (u8)i;
        }
        for (i = 0; lbl_8064CA74[i].source != 0; i++) {
            source = (SourceEntry *)lbl_8064CA74[i].source;
            offset = 0;
            for (j = 0; j < source->count; j++, offset += 4) {
                item = source->items[j];
                result = fn_800BC100(item, 0, &value, 1, 0, 0, 0);
                if (item != 0 && result != 0 && j < 8) {
                    *(void **)((u8 *)&lbl_8064CA74[i] + offset + 4) = result;
                }
            }
            lbl_8064CA74[i].count = (u8)j;
        }
    }
}
