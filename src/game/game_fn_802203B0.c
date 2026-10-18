typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct Result { u32 first, second, third; } Result;
typedef void (*CardCallback)(s32 channel, s32 result);
typedef void (*EXICallback)(s32 channel, void *context);

typedef struct CardControl {
    u8 reserved00[8];
    u16 size;
    u16 reserved0A;
    s32 sectorSize;
    u16 blockCount;
    u16 reserved12;
    s32 latency;
    union { Result result; u8 bytes[12]; } id;
    s32 mountStep;
    u8 reserved28[0x58];
    u8 *workArea;
    u8 reserved84[0x84];
    u32 deviceID;
    u8 reserved10C[4];
} CardControl;

typedef struct SramEx {
    u8 flashID[2][12];
    u8 reserved18[0xE];
    u8 flashIDChecksum[2];
} SramEx;

extern CardControl __CARDBlock[];
extern s32 SectorSizeTable[];
extern s32 LatencyTable[];
extern u16 __CARDVendorID;
extern s32 EXIGetID(s32 channel, u32 device, u32 *id);
extern s32 IsCard(u32 id);
extern s32 __CARDClearStatus(s32 channel);
extern s32 __CARDReadStatus(s32 channel, u8 *status);
extern s32 EXIProbe(s32 channel);
extern s32 __CARDUnlock(s32 channel, Result *result);
extern SramEx *__OSLockSramEx(void);
extern s32 __OSUnlockSramEx(s32 commit);
extern s32 __CARDEnableInterrupt(s32 channel, s32 enable);
extern void __CARDExiHandler(s32 channel, void *context);
extern EXICallback EXISetExiCallback(s32 channel, EXICallback callback);
extern s32 EXIUnlock(s32 channel);
extern void DCInvalidateRange(void *data, u32 size);
extern void __CARDMountCallback(s32 channel, s32 result);
extern s32 __CARDRead(s32 channel, u32 address, s32 length, void *data, CardCallback callback);
extern s32 __CARDPutControlBlock(CardControl *control, s32 result);
extern void DoUnmount(s32 channel, s32 result);

s32 DoMount(s32 channel)
{
    CardControl *control = &__CARDBlock[channel];
    u32 deviceID;
    u8 status;
    s32 result;
    SramEx *sram;
    u8 checksum;
    s32 i;
    u16 encoding;

    if (control->mountStep == 0) {
        if (!EXIGetID(channel, 0, &deviceID))
            result = -3;
        else if (IsCard(deviceID))
            result = 0;
        else
            result = -2;
        if (result < 0)
            goto error;
        control->deviceID = deviceID;
        control->size = deviceID & 0xFC;
        control->sectorSize = SectorSizeTable[(deviceID >> 11) & 7];
        control->blockCount = ((s32)(control->size << 20) / 8) / control->sectorSize;
        control->latency = LatencyTable[(deviceID >> 8) & 7];
        result = __CARDClearStatus(channel);
        if (result < 0)
            goto error;
        result = __CARDReadStatus(channel, &status);
        if (result < 0)
            goto error;
        if (!EXIProbe(channel)) {
            result = -3;
            goto error;
        }
        if (!(status & 0x40)) {
            result = __CARDUnlock(channel, &control->id.result);
            if (result < 0)
                goto error;
            sram = __OSLockSramEx();
            checksum = 0;
            for (i = 0; i < 12; ++i) {
                sram->flashID[channel][i] = control->id.bytes[i];
                checksum += control->id.bytes[i];
            }
            sram->flashIDChecksum[channel] = ~checksum;
            __OSUnlockSramEx(1);
            return result;
        }
        control->mountStep = 1;
        sram = __OSLockSramEx();
        checksum = 0;
        for (i = 0; i < 12; ++i)
            checksum += sram->flashID[channel][i];
        __OSUnlockSramEx(0);
        if (sram->flashIDChecksum[channel] != (u8)~checksum) {
            result = -5;
            goto error;
        }
    }
    if (control->mountStep == 1) {
        if (control->deviceID == 0x80000004) {
            sram = __OSLockSramEx();
            encoding = *(u16 *)sram->flashID[channel];
            __OSUnlockSramEx(0);
            if (__CARDVendorID == 0xFFFF || encoding != __CARDVendorID) {
                result = -2;
                goto error;
            }
        }
        control->mountStep = 2;
        result = __CARDEnableInterrupt(channel, 1);
        if (result < 0)
            goto error;
        EXISetExiCallback(channel, __CARDExiHandler);
        EXIUnlock(channel);
        DCInvalidateRange(control->workArea, 0xA000);
    }
    result = __CARDRead(channel, control->sectorSize * (control->mountStep - 2),
                         0x2000, control->workArea + ((control->mountStep - 2) << 13),
                         __CARDMountCallback);
    if (result < 0)
        __CARDPutControlBlock(control, result);
    return result;
error:
    EXIUnlock(channel);
    DoUnmount(channel, result);
    return result;
}
