typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef signed long long s64;

typedef struct CardControl {
    u8 reserved00[8];
    u16 size;
    u8 reserved0A[0x76];
    u8 *workArea;
    u8 reserved84[0x8C];
} CardControl;

typedef struct CardHeader {
    u8 serial[12];
    /* The timestamp is stored at word-aligned offset 0x0C. */
    u32 formatTime[2];
    u32 sramBias;
    u32 sramLanguage;
    u32 deviceID;
    u16 encoding;
    u16 size;
    u16 format;
    u8 reserved26[0x1D6];
    u16 checksum;
    u16 inverse;
} CardHeader;

typedef struct SramEx {
    u8 flashID[2][12];
} SramEx;

extern CardControl __CARDBlock[];
extern u16 OSGetFontEncode(void);
extern SramEx *__OSLockSramEx(void);
extern s32 __OSUnlockSramEx(s32 commit);

static inline void CardChecksum(u16 *p, s32 length, u16 *checksum, u16 *inverse)
{
    *inverse = 0;
    *checksum = 0;
    for (length /= 2; length > 0; --length) {
        *checksum += *p;
        *inverse += ~*p;
        ++p;
    }
    if (*checksum == 0xFFFF)
        *checksum = 0;
    if (*inverse == 0xFFFF)
        *inverse = 0;
}

s32 VerifyID(CardControl *control)
{
    CardHeader *header = (CardHeader *)control->workArea;
    u16 checksum, inverse;
    s64 random;
    SramEx *sram;
    s32 i;

    if (header->encoding != 0 || header->size != control->size)
        return -6;
    CardChecksum((u16 *)header, 0x1FC, &checksum, &inverse);
    if (header->checksum != checksum || header->inverse != inverse)
        return -6;
    if (header->format != OSGetFontEncode())
        return -13;
    /* Regenerate the serial from its format timestamp and the SRAM flash ID. */
    random = *(s64 *)header->formatTime;
    sram = __OSLockSramEx();
    for (i = 0; i < 12; ++i) {
        random = (random * 0x41C64E6D + 0x3039) >> 16;
        if (header->serial[i] != (u8)(sram->flashID[control - __CARDBlock][i] + random)) {
            __OSUnlockSramEx(0);
            return -6;
        }
        random = ((random * 0x41C64E6D + 0x3039) >> 16) & 0x7FFF;
    }
    __OSUnlockSramEx(0);
    return 0;
}
