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

extern CardControl lbl_80641C60[];
extern s32 lbl_802FECE0[];
extern s32 lbl_802FED00[];
extern u16 lbl_8064C450;
extern s32 fn_80207CC8(s32 channel, u32 device, u32 *id);
extern s32 fn_80220130(u32 id);
extern s32 fn_8021C878(s32 channel);
extern s32 fn_8021C788(s32 channel, u8 *status);
extern s32 fn_802070C4(s32 channel);
extern s32 fn_8021D9B4(s32 channel, Result *result);
extern SramEx *__OSLockSramEx(void);
extern s32 __OSUnlockSramEx(s32 commit);
extern s32 fn_8021C6C8(s32 channel, s32 enable);
extern void fn_8021C484(s32 channel, void *context);
extern EXICallback fn_80206ED4(s32 channel, EXICallback callback);
extern s32 EXIUnlock(s32 channel);
extern void DCInvalidateRange(void *data, u32 size);
extern void fn_802207C0(s32 channel, s32 result);
extern s32 fn_8021E97C(s32 channel, u32 address, s32 length, void *data, CardCallback callback);
extern s32 fn_8021D374(CardControl *control, s32 result);
extern void fn_80220AB0(s32 channel, s32 result);

s32 fn_802203B0(s32 channel)
{
    CardControl *control = &lbl_80641C60[channel];
    u32 deviceID;
    u8 status;
    s32 result;
    SramEx *sram;
    u8 checksum;
    s32 i;
    u16 encoding;

    if (control->mountStep == 0) {
        if (!fn_80207CC8(channel, 0, &deviceID))
            result = -3;
        else if (fn_80220130(deviceID))
            result = 0;
        else
            result = -2;
        if (result < 0)
            goto error;
        control->deviceID = deviceID;
        control->size = deviceID & 0xFC;
        control->sectorSize = lbl_802FECE0[(deviceID >> 11) & 7];
        control->blockCount = ((s32)(control->size << 20) / 8) / control->sectorSize;
        control->latency = lbl_802FED00[(deviceID >> 8) & 7];
        result = fn_8021C878(channel);
        if (result < 0)
            goto error;
        result = fn_8021C788(channel, &status);
        if (result < 0)
            goto error;
        if (!fn_802070C4(channel)) {
            result = -3;
            goto error;
        }
        if (!(status & 0x40)) {
            result = fn_8021D9B4(channel, &control->id.result);
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
            if (lbl_8064C450 == 0xFFFF || encoding != lbl_8064C450) {
                result = -2;
                goto error;
            }
        }
        control->mountStep = 2;
        result = fn_8021C6C8(channel, 1);
        if (result < 0)
            goto error;
        fn_80206ED4(channel, fn_8021C484);
        EXIUnlock(channel);
        DCInvalidateRange(control->workArea, 0xA000);
    }
    result = fn_8021E97C(channel, control->sectorSize * (control->mountStep - 2),
                         0x2000, control->workArea + ((control->mountStep - 2) << 13),
                         fn_802207C0);
    if (result < 0)
        fn_8021D374(control, result);
    return result;
error:
    EXIUnlock(channel);
    fn_80220AB0(channel, result);
    return result;
}
