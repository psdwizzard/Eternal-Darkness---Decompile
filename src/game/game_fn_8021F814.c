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

s32 fn_8021F814(SaveCtx* ctx, s32* outIndex) {
    SaveBlock* blocks[2];
    s32 i;
    s32 errors = 0;
    s32 index = 0;

    for (i = 0; i < 2; i++) {
        SaveBlock* blk;
        u16* p;
        u16 sum;
        u16 inv;
        s32 n;

        n = 0x2000 - 4;
        blk = (SaveBlock*)(ctx->buffer + (i + 3) * 0x2000);
        blocks[i] = blk;
        p = (u16*)&blk->serial;
        inv = 0;
        sum = 0;
        for (n /= 2; n > 0; n--) {
            sum += *p;
            inv += ~*p;
            p++;
        }
        if (sum == 0xFFFF) {
            sum = 0;
        }
        if (inv == 0xFFFF) {
            inv = 0;
        }
        if (blk->sum != sum || blk->invSum != inv) {
            ctx->current = NULL;
            index = i;
            errors++;
        } else {
            u16* q = &blk->data[0];
            u16 count = 0;
            u16 k;
            for (k = 5; k < ctx->numEntries; k++) {
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
