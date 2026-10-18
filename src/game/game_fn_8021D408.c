/* CARDFreeBlocks: CARDFreeBlocks (SDK CARDStat.c / CARDBios.c). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef int BOOL;

typedef struct CARDDir {
    u8 gameName[4];
    u8 company[2];
    u8 reserved06[2];
    u8 fileName[32];
    u8 reserved28[0xE];
    u16 startBlock;
    u16 length;
    u8 reserved3A[6];
} CARDDir;

typedef struct CARDControl {
    BOOL attached;
    s32 result;
    u8 reserved08[4];
    s32 sectorSize;
} CARDControl;

#define CARD_RESULT_READY 0
#define CARD_RESULT_BUSY -1
#define CARD_RESULT_BROKEN -6
#define CARD_MAX_FILE 127
#define CARD_FAT_FREEBLOCKS 0x0003

extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern s32 __CARDGetControlBlock(s32 chan, CARDControl **card);
extern CARDDir *__CARDGetDirBlock(CARDControl *card);
extern u16 *__CARDGetFatBlock(CARDControl *card);

static inline s32 __CARDPutControlBlock(CARDControl *card, s32 result)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();
    if (card->attached) {
        card->result = result;
    } else if (card->result == CARD_RESULT_BUSY) {
        card->result = result;
    }
    OSRestoreInterrupts(enabled);
    return result;
}

s32 CARDFreeBlocks(s32 chan, s32 *byteNotUsed, s32 *filesNotUsed)
{
    CARDControl *card;
    s32 result;
    u16 *fat;
    CARDDir *dir;
    CARDDir *ent;
    u16 fileNo;

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }

    fat = __CARDGetFatBlock(card);
    dir = __CARDGetDirBlock(card);
    if (fat == 0 || dir == 0) {
        return __CARDPutControlBlock(card, CARD_RESULT_BROKEN);
    }

    if (byteNotUsed) {
        *byteNotUsed = (s32)(card->sectorSize * fat[CARD_FAT_FREEBLOCKS]);
    }

    if (filesNotUsed) {
        *filesNotUsed = 0;
        for (fileNo = 0; fileNo < CARD_MAX_FILE; fileNo++) {
            ent = &dir[fileNo];
            if (ent->fileName[0] == 0xff) {
                ++*filesNotUsed;
            }
        }
    }

    return __CARDPutControlBlock(card, CARD_RESULT_READY);
}
