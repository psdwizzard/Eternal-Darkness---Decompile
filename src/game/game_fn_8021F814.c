typedef int s32;
typedef unsigned int u32;
typedef short s16;
typedef unsigned short u16;
typedef unsigned char u8;

#ifndef NULL
#define NULL 0
#endif

extern void* memcpy(void*, const void*, u32);

typedef struct SaveBlock {
    u16 sum;
    u16 invSum;
    s16 serial;
    u16 emptyCount;
    u16 pad;
    u16 data[1];
} SaveBlock;

typedef struct SaveCtx {
    u8 pad0[0x10];
    u16 numEntries;
    u8 pad12[0x80 - 0x12];
    u8* buffer;
    u8 pad84[0x88 - 0x84];
    SaveBlock* current;
} SaveCtx;

/* Sum the allocation-table words and their bitwise complements. */
static inline void __CARDCheckSum(void *ptr, int length, u16 *checksum, u16 *checksumInv)
{
    u16 *p;
    int i;

    length /= sizeof(u16);
    *checksum = *checksumInv = 0;
    for (i = 0, p = ptr; i < length; i++, p++) {
        *checksum += *p;
        *checksumInv += ~*p;
    }
    if (*checksum == 0xFFFF) {
        *checksum = 0;
    }
    if (*checksumInv == 0xFFFF) {
        *checksumInv = 0;
    }
}

s32 VerifyFAT(SaveCtx* ctx, s32* outIndex) {
    SaveBlock* blocks[2];
    SaveBlock* blk;
    u16* q;
    u16 limit;
    u16 sum;
    u16 inv;
    u16 k;
    SaveBlock** next = blocks;
    s32 i;
    s32 errors = 0;
    s32 index = 0;

    for (i = 0; i < 2; i++, next++) {
        blk = *next = (SaveBlock*)(ctx->buffer + (i + 3) * 0x2000);
        __CARDCheckSum(&blk->serial, 0x1FFC, &sum, &inv);
        if (blk->sum != sum || blk->invSum != inv) {
            ctx->current = NULL;
            index = i;
            errors++;
        } else {
            u16 count;
            limit = ctx->numEntries;
            q = &blk->data[0];
            count = 0;
            for (k = 5; k < limit; k++) {
                if (*q == 0) {
                    count++;
                }
                q++;
            }
            if (count != blk->emptyCount) {
                ctx->current = NULL;
                index = i;
                errors++;
            }
        }
    }

    if (errors == 0) {
        if (ctx->current == NULL) {
            if (blocks[0]->serial - blocks[1]->serial < 0) {
                index = 0;
            } else {
                index = 1;
            }
            ctx->current = blocks[index];
            memcpy(blocks[index], blocks[index ^ 1], 0x2000);
        } else {
            index = (ctx->current == blocks[0]) ? 0 : 1;
        }
    }
    if (outIndex != NULL) {
        *outIndex = index;
    }
    return errors;
}
