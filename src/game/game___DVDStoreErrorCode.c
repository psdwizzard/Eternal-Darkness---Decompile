typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

typedef struct SramEx {
    u8 reserved00[0x24];
    u8 dvdErrorCode;
} SramEx;

extern u8 ErrorCode2Num_802165E0(u32 errorCode);
extern SramEx *__OSLockSramEx(void);
extern s32 __OSUnlockSramEx(s32 commit);

void __DVDStoreErrorCode(u32 errorCode)
{
    u8 storedCode;
    u32 status;
    u8 errorNumber;
    SramEx *sram;

    if (errorCode == 0x01234567) {
        storedCode = 0xFF;
    } else if (errorCode == 0x01234568) {
        storedCode = 0xFE;
    } else {
        status = errorCode >> 24;
        errorNumber = ErrorCode2Num_802165E0(errorCode & 0x00FFFFFF);
        if (status >= 6) {
            status = 6;
        }
        storedCode = errorNumber + status * 30;
    }

    sram = __OSLockSramEx();
    sram->dvdErrorCode = storedCode;
    __OSUnlockSramEx(1);
}
