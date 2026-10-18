/* GXSetFogRangeAdj: program the fog range adjustment table and center. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct GXData {
    u16 reserved0;
    u16 bpSentNot;
} GXData;
extern GXData *gx;

typedef struct GXFogAdjTable {
    u16 r[10];
} GXFogAdjTable;

typedef union GXWGPipe { u8 byte; u32 word; } GXWGPipe;
extern volatile GXWGPipe GXWGFifo : 0xCC008000;

#define SET_FIELD(reg, width, shift, value) \
    ((reg) = ((reg) & ~(((1UL << (width)) - 1) << (shift))) | ((u32)(value) << (shift)))

void GXSetFogRangeAdj(u8 enable, u16 center, GXFogAdjTable *table)
{
    u32 i;
    u32 range_adj;
    u32 range_c;

    if (enable) {
        for (i = 0; i < 10; i += 2) {
            range_adj = 0;
            SET_FIELD(range_adj, 12, 0, table->r[i]);
            SET_FIELD(range_adj, 12, 12, table->r[i + 1]);
            SET_FIELD(range_adj, 8, 24, 0xE9 + (i / 2));
            GXWGFifo.byte = 0x61;
            GXWGFifo.word = range_adj;
        }
    }
    range_c = 0;
    SET_FIELD(range_c, 10, 0, center + 342);
    SET_FIELD(range_c, 1, 10, enable);
    SET_FIELD(range_c, 8, 24, 0xE8);
    GXWGFifo.byte = 0x61;
    GXWGFifo.word = range_c;
    gx->bpSentNot = 0;
}
