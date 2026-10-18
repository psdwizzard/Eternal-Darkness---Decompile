typedef unsigned char u8;
typedef unsigned int u32;

typedef struct MapBounds {
    short x0, y0, x1, y1;
} MapBounds;

typedef struct MapEntry {
    short x0, y0, x1, y1;
    signed char region;
    u8 layer;
    u8 icon;
    u8 padding;
} MapEntry;

typedef struct MapResource {
    u8 padding[0x14];
    int field14;
    int field18;
} MapResource;

typedef struct EntryPair {
    void *first;
    void *second;
} EntryPair;

typedef struct ResourceTable {
    void *base;
    u32 count;
    EntryPair *entries;
} ResourceTable;

typedef struct Entry80201814 Entry80201814;
typedef struct Object8020216C Object8020216C;
typedef struct TextDescriptor TextDescriptor;
typedef struct Entry {
    int field0;
    int field4;
    int field8;
    int fieldC;
    int state;
    int owner;
    int field18;
    int flags;
} Entry;

extern int lbl_803003C8[];
extern int lbl_8064B990;
extern void *lbl_8064C508;
extern void (*lbl_8064CD88)(void);
extern void (*lbl_8064CD8C)(u8);
extern volatile int lbl_8064CDA8;
extern volatile int lbl_8064CDAC;
extern TextDescriptor *lbl_8064CDB0;
extern TextDescriptor *lbl_8064CDB4;
extern Entry *lbl_8064CDC0;
extern ResourceTable *lbl_8064CDE0;
extern MapEntry *lbl_8064CDE4;
extern int lbl_8064CDE8;
extern int lbl_8064CDEC;
extern MapBounds lbl_8064CDF0;
extern float lbl_8064CDF8;
extern int lbl_8064CDFC;
extern int lbl_8064CE00;
extern int lbl_8064CE04;
extern int lbl_8064CE08;
extern u8 lbl_8064CE0C;
extern u32 *lbl_8064D158;
extern int lbl_8064D184;
extern MapBounds lbl_803323F0[7];
extern u8 lbl_8024E878[];
extern const char lbl_8024E9D8[];
extern const float lbl_8064FFB0;

extern int fn_80201B44(void);
extern Entry80201814 *fn_80201814(int);
extern u32 fn_8020216C(Object8020216C *);
extern int fn_801118E8(void);
extern Entry *fn_80144628(int, int, int);
extern void fn_801446D4(void **, void *);
extern EntryPair *fn_8015DB74(ResourceTable *, u32);
extern TextDescriptor *fn_801E6CA0(void *, u32, u32, u32, int);
extern u32 fn_801E7998(u32 *);
extern int fn_801E79FC(u32 *, u32);
extern void fn_801E7F3C(const char *, ...);
extern void fn_80119A5C(int, int);
extern void fn_80119E90(void);
extern void fn_80119F98(u8);

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

static inline int RevealMap(void)
{
    int reveal;
    reveal = 1;
    if (!(fn_8020216C((Object8020216C *)fn_80201814(fn_80201B44())) & 0x40000)
        && lbl_803003C8[0] != 8) {
        reveal = 0;
    }
    return reveal;
}

/* Prepare the map layers and their combined visible-room bounds. */
void fn_80119568(void)
{
    u32 offset;
    MapBounds *bounds;
    MapBounds *combined;
    int reveal;
    u32 roomIndex;
    int layer;

    reveal = RevealMap();
    while (lbl_8064CDA8 == 0 || lbl_8064CDAC == 0) {}
    lbl_8064CDC0 = fn_80144628(11, (int)lbl_8024E878, 0);
    fn_801446D4((void **)lbl_8064CDC0, fn_80119A5C);
    lbl_8064CD8C = fn_80119F98;
    lbl_8064CD88 = fn_80119E90;
    if (lbl_8064B990 != 0) {
        TextDescriptor *text;
        if (fn_801118E8() != 0) {
            text = fn_801E6CA0(lbl_8064C508, 1, 6, 0, 1);
        } else {
            text = fn_801E6CA0(lbl_8064C508, 1, 8, 0, 1);
        }
        lbl_8064CDB4 = text;
        lbl_8064CDB0 = fn_801E6CA0(lbl_8064C508, 1, 3, 0, 1);
    }
    lbl_8064CE08 = 0;
    lbl_8064CDF8 = lbl_8064FFB0;
    lbl_8064CE04 = 0;
    if (lbl_8064CDE0 != 0) {
        for (offset = 0; offset < lbl_8064CDE0->count; offset++) {
            EntryPair *pair = fn_8015DB74(lbl_8064CDE0, offset);
            ((MapResource *)pair->first)->field14 = 1;
            ((MapResource *)pair->first)->field18 = 1;
        }
    }
    {
        int width = 640;
        int height = 480;
        int zero = 0;
        bounds = lbl_803323F0;
        combined = &lbl_8064CDF0;
        for (layer = 0; layer < 7; layer++) {
            bounds[layer].x0 = width;
            bounds[layer].y0 = height;
            bounds[layer].x1 = zero;
            bounds[layer].y1 = zero;
        }
        /* Retain the base for the reduction below. This explicit assignment
         * lets MWCC reuse its initialization register across the intervening calls. */
        bounds = lbl_803323F0;
        combined->x0 = width;
        combined->y0 = height;
        combined->x1 = zero;
        combined->y1 = zero;
    }
    if (lbl_8064D184 >= 0) {
        lbl_8064CDEC = lbl_8064CDE4[lbl_8064D184].region;
    } else {
        lbl_8064CDEC = -1;
    }
    lbl_8064CE0C = 0;
    for (roomIndex = 0, offset = 0; roomIndex < 351; roomIndex++, offset += sizeof(MapEntry)) {
        signed char region = ((MapEntry *)((u8 *)lbl_8064CDE4 + offset))->region;
        if (region >= 0 && lbl_8064CDEC == region
            && (fn_801E79FC(lbl_8064D158, roomIndex) != 0 || reveal != 0)) {
            MapEntry *entry = (MapEntry *)((u8 *)lbl_8064CDE4 + offset);
            MapBounds *layerBounds;
            u32 entryLayer = entry->layer;
            lbl_8064CE0C |= 1 << entryLayer;
            layerBounds = &lbl_803323F0[entryLayer];
            {
                short *bound = &layerBounds->x0;
                *bound = *bound < entry->x0 ? *bound : entry->x0;
            }
            {
                short *bound = &layerBounds->y0;
                *bound = *bound < entry->y0 ? *bound : entry->y0;
            }
            {
                short *bound = &layerBounds->x1;
                *bound = *bound > entry->x1 ? *bound : entry->x1;
            }
            {
                short *bound = &layerBounds->y1;
                *bound = *bound > entry->y1 ? *bound : entry->y1;
            }
        }
    }
    if (lbl_8064D184 >= 0 && (u32)lbl_8064D184 < fn_801E7998(lbl_8064D158)) {
        int selected = lbl_8064D184;
        MapEntry *table = lbl_8064CDE4;
        lbl_8064CDE8 = table[selected].layer;
        lbl_8064CE08 = ((table[selected].x0 + table[selected].x1) >> 1) - 360;
        lbl_8064CE04 = ((table[selected].y0 + table[selected].y1) >> 1) - 240;
    } else {
        lbl_8064CDE8 = -1;
        lbl_8064CE08 = 360;
        lbl_8064CE04 = 240;
    }
    fn_801E7F3C(lbl_8024E9D8, lbl_8064CDE8, lbl_8064D184);
    lbl_8064CE00 = lbl_8064CE08;
    lbl_8064CDFC = lbl_8064CE04;
    /* The first field uses direct small-data addressing in the original;
     * the other fields use the retained combined-bounds pointer. */
    for (layer = 7; layer != 0; layer--, bounds++) {
        lbl_8064CDF0.x0 = MIN(lbl_8064CDF0.x0, bounds->x0);
        combined->y0 = MIN(combined->y0, bounds->y0);
        combined->x1 = MAX(combined->x1, bounds->x1);
        combined->y1 = MAX(combined->y1, bounds->y1);
    }
}
