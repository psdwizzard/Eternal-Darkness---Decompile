/* fn_8021CD04: __CARDStart (Dolphin SDK CARDBios.c), with SetupTimeoutAlarm
 * inlined. */

typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef long long s64;
typedef s64 OSTime;

typedef void (*CardCallback)(s32 channel, s32 result);
typedef void (*EXICallback)(s32 channel, void *context);
typedef void (*OSAlarmHandler)(void *alarm, void *context);

typedef struct OSAlarm {
    u8 data[0x28];
} OSAlarm;

typedef struct CardControl {
    s32 attached;
    u8 reserved04[8];
    s32 sectorSize;
    u8 reserved10[0x84];
    u8 cmd[9];
    u8 reserved9D[0x2B];
    CardCallback txCallback;
    CardCallback exiCallback;
    u8 reservedD0[0xC];
    CardCallback unlockCallback;
    OSAlarm alarm;
    u8 reserved108[8];
} CardControl;

extern CardControl lbl_80641C60[];

extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32 level);
extern s32 EXILock(s32 channel, u32 device, EXICallback unlockedCallback);
extern s32 EXIUnlock(s32 channel);
extern s32 EXISelect(s32 channel, u32 device, u32 freq);
extern void fn_8020A93C(OSAlarm *alarm);
extern void OSSetAlarm(OSAlarm *alarm, OSTime tick, OSAlarmHandler handler);
extern void fn_8021CBF4(s32 channel, s32 result);
extern void fn_8021C644(s32 channel, void *context);
extern void fn_8021C924(void *alarm, void *context);

#define OS_BUS_CLOCK (*(u32 *)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSSecondsToTicks(sec) ((sec) * OS_TIMER_CLOCK)
#define OSMillisecondsToTicks(msec) ((msec) * (OS_TIMER_CLOCK / 1000))

static inline void SetupTimeoutAlarm(CardControl *card)
{
    fn_8020A93C(&card->alarm);
    switch (card->cmd[0]) {
    case 0xF2:
        OSSetAlarm(&card->alarm, OSMillisecondsToTicks(100), fn_8021C924);
        break;
    case 0xF3:
        break;
    case 0xF4:
    case 0xF1:
        OSSetAlarm(&card->alarm,
                   OSSecondsToTicks((OSTime)2) * (card->sectorSize / 0x2000),
                   fn_8021C924);
        break;
    }
}

s32 fn_8021CD04(s32 chan, CardCallback txCallback, CardCallback exiCallback)
{
    s32 enabled;
    CardControl *card;
    s32 result;

    enabled = OSDisableInterrupts();

    card = &lbl_80641C60[chan];
    if (!card->attached) {
        result = -3;
    } else {
        if (txCallback)
            card->txCallback = txCallback;
        if (exiCallback)
            card->exiCallback = exiCallback;
        card->unlockCallback = fn_8021CBF4;
        if (!EXILock(chan, 0, fn_8021C644)) {
            result = -1;
        } else {
            card->unlockCallback = 0;
            if (!EXISelect(chan, 0, 4)) {
                EXIUnlock(chan);
                result = -3;
            } else {
                SetupTimeoutAlarm(card);
                result = 0;
            }
        }
    }
    OSRestoreInterrupts(enabled);
    return result;
}
