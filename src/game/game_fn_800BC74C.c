typedef unsigned char u8;
typedef unsigned short u16;

typedef struct SourceEntry {
    u8 pad0[6];
    u8 count;
    u8 pad7;
    struct SourceEntry **items;
} SourceEntry;

typedef struct Collection {
    u8 pad0[0x60];
    u16 count;
    u8 pad62[2];
    SourceEntry *entries;
} Collection;

typedef struct CacheEntry {
    SourceEntry *source;
    struct CacheEntry *items[8];
    u8 pad24[0x11];
    u8 count;
    u8 index;
} CacheEntry;

extern void *fn_8015C390(int);
typedef struct Vec3 Vec3;

extern CacheEntry *fn_800BC100(SourceEntry *, Vec3 *, int *, int, int *, int *, int);
extern void *memset(void *, int, unsigned int);
extern int lbl_8064CA70;
extern CacheEntry *lbl_8064CA74;
extern int lbl_8064D18C;

void fn_800BC74C(int reset)
{
    Collection *collection;
    SourceEntry *entry;
    int i;
    int value;

    collection = fn_8015C390(2);
    if (reset != 0) {
        lbl_8064CA70 = 0;
    }
    if (lbl_8064CA70 != lbl_8064D18C) {
        SourceEntry *source;

        lbl_8064CA70 = lbl_8064D18C;
        memset(lbl_8064CA74, 0, 0x6D60);
        entry = collection->entries;
        for (i = 0; i < collection->count; entry++, i++) {
            lbl_8064CA74[i].source = entry;
            lbl_8064CA74[i].index = (u8)i;
        }
        for (i = 0; (source = lbl_8064CA74[i].source) != 0; i++) {
            int j;
            for (j = 0; j < source->count; j++) {
                SourceEntry *item = source->items[j];
                register CacheEntry *result = fn_800BC100(item, 0, &value, 1, 0, 0, 0);
                if (item != 0 && result != 0 && j < 8) {
                    register CacheEntry *cache = lbl_8064CA74;
                    register int cacheOffset = i * (int)sizeof(CacheEntry);
                    register int itemOffset = j * 4;
                    register int slotOffset;
                    /* ASM: addi/add keep the record base and slot offset
                     * separate and in retail order; MWCC reassociates C stores. */
                    asm {
                        addi slotOffset, itemOffset, 4
                        add cache, cacheOffset, cache
                    }
                    *(CacheEntry **)((u8 *)cache + slotOffset) = result;
                }
            }
            lbl_8064CA74[i].count = (u8)j;
        }
    }
}
