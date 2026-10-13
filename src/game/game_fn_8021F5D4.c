/* fn_8021F5D4: CARD VerifyDir (SDK CARDCheck.c) with __CARDCheckSum inlined. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;

#define CARD_SYSTEM_BLOCK_SIZE (8 * 1024)

typedef struct CARDDir {
    u8 data[0x40];
} CARDDir;

typedef struct CARDDirCheck {
    u8 padding0[0x3A];
    s16 checkCode;
    u16 checkSum;
    u16 checkSumInv;
} CARDDirCheck;

typedef struct CARDControl {
    u8 reserved00[0x80];
    void *workArea;
    CARDDir *currentDir;
} CARDControl;

extern void *memcpy(void *dst, const void *src, u32 n);

#define CARDGetDirCheck(dir) ((CARDDirCheck *)&(dir)[127])

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

s32 fn_8021F5D4(CARDControl *card, int *outCurrent)
{
    CARDDir *dir[2];
    CARDDirCheck *check[2];
    u16 checkSum;
    u16 checkSumInv;
    int i;
    int errors;
    int current;

    current = errors = 0;
    for (i = 0; i < 2; i++) {
        dir[i] = (CARDDir *)((u8 *)card->workArea + (1 + i) * CARD_SYSTEM_BLOCK_SIZE);
        check[i] = CARDGetDirCheck(dir[i]);
        __CARDCheckSum(dir[i], CARD_SYSTEM_BLOCK_SIZE - sizeof(u32), &checkSum, &checkSumInv);
        if (check[i]->checkSum != checkSum || check[i]->checkSumInv != checkSumInv) {
            card->currentDir = 0;
            current = i;
            ++errors;
        }
    }

    if (0 == errors) {
        if (card->currentDir == 0) {
            if ((check[0]->checkCode - check[1]->checkCode) < 0) {
                current = 0;
            } else {
                current = 1;
            }
            card->currentDir = dir[current];
            memcpy(dir[current], dir[current ^ 1], CARD_SYSTEM_BLOCK_SIZE);
        } else {
            current = (card->currentDir == dir[0]) ? 0 : 1;
        }
    }
    if (outCurrent) {
        *outCurrent = current;
    }
    return errors;
}
