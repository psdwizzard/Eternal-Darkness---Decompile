typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

typedef signed long long s64;
typedef unsigned long long u64;
typedef void (*CardCallback)(s32 channel, s32 result);

typedef struct CardControl {
    u8 reserved00[8];
    u16 size;
    u16 reserved0A;
    s32 sectorSize;
    u16 blockCount;
    u8 reserved12[0x16];
    s32 formatStep;
    u8 reserved2C[0x54];
    u8 *workArea;
    u8 reserved84[0x4C];
    CardCallback callback;
} CardControl;

typedef struct CardHeader {
    u8 serial[12];
    /* The on-card timestamp begins at offset 0x0C, on a word boundary. */
    u32 formatTime[2];
    u32 sramBias;
    u32 sramLanguage;
    u32 deviceID;
    u16 encoding;
    u16 size;
    u16 format;
} CardHeader;

typedef struct Sram {
    u8 reserved00[12];
    u32 bias;
    u8 reserved10[2];
    u8 language;
} Sram;

typedef struct SramEx {
    u8 flashID[2][12];
} SramEx;

extern s32 __CARDGetControlBlock(s32 channel, CardControl **control);
extern s32 __CARDPutControlBlock(CardControl *control, s32 result);
extern s32 __CARDEraseSector(s32 channel, u32 address, CardCallback callback);
extern void __CARDDefaultApiCallback(s32 channel, s32 result);
extern void FormatCallback(s32 channel, s32 result);
extern void __CARDCheckSum(void *data, s32 length, u16 *checksum, u16 *inverse);
extern void DCStoreRange(void *data, u32 length);
extern void *memset(void *data, int value, unsigned long size);
extern Sram *__OSLockSram(void);
extern SramEx *__OSLockSramEx(void);
extern s32 __OSUnlockSram(s32 commit);
extern s32 __OSUnlockSramEx(s32 commit);
extern s64 OSGetTime(void);

s32 __CARDFormatRegionAsync(s32 channel, u16 format, CardCallback callback)
{
    CardControl *control;
    CardHeader *header;
    Sram *sram;
    SramEx *sramEx;
    u64 time;
    s64 random;
    u32 deviceID;
    s32 result;
    s16 i;
    u8 *block;
    u8 *trailer;

    result = __CARDGetControlBlock(channel, &control);
    if (result < 0) {
        return result;
    }
    header = (CardHeader *)control->workArea;
    memset(header, 0xFF, 0x2000);
    deviceID = *(volatile u16 *)0xCC00206E;
    header->format = format;
    sram = __OSLockSram();
    header->sramBias = sram->bias;
    header->sramLanguage = sram->language;
    __OSUnlockSram(0);
    /* Keep the original timestamp while the generator advances its seed. */
    random = time = OSGetTime();
    sramEx = __OSLockSramEx();
    for (i = 0; i < 12; ++i) {
        random = ((random * 0x41C64E6D + 0x3039) >> 16);
        header->serial[i] = sramEx->flashID[channel][i] + random;
        random = (((random * 0x41C64E6D + 0x3039) >> 16)) & 0x7FFF;
    }
    __OSUnlockSramEx(0);
    header->deviceID = deviceID;
    *(u64 *)header->formatTime = time;
    header->encoding = 0;
    header->size = control->size;
    __CARDCheckSum(header, 0x1FC, (u16 *)((u8 *)header + 0x1FC),
               (u16 *)((u8 *)header + 0x1FE));
    /* Initialize the two directory copies and their checksum trailers. */
    for (i = 0; i < 2; ++i) {
        block = control->workArea + ((i + 1) << 13);
        memset(block, 0xFF, 0x2000);
        trailer = block + 0x1FC0;
        *(u16 *)(trailer + 0x3A) = i;
        __CARDCheckSum(block, 0x1FFC, (u16 *)(trailer + 0x3C),
                   (u16 *)(trailer + 0x3E));
    }
    /* Initialize both allocation tables with all data blocks free. */
    for (i = 0; i < 2; ++i) {
        block = control->workArea + ((i + 3) << 13);
        memset(block, 0, 0x2000);
        *(u16 *)(block + 4) = i;
        *(u16 *)(block + 6) = control->blockCount - 5;
        *(u16 *)(block + 8) = 4;
        __CARDCheckSum(block + 4, 0x1FFC, (u16 *)block, (u16 *)(block + 2));
    }
    control->callback = callback ? callback : __CARDDefaultApiCallback;
    DCStoreRange(control->workArea, 0xA000);
    control->formatStep = 0;
    result = __CARDEraseSector(channel, control->sectorSize * control->formatStep,
                         FormatCallback);
    if (result < 0) {
        __CARDPutControlBlock(control, result);
    }
    return result;
}

