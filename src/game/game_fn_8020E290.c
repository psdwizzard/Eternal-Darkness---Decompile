/* fn_8020E290: OSGetResetButtonState (Dolphin SDK OSResetSW.c). */

typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef long long s64;
typedef s64 OSTime;
typedef int BOOL;

#define TRUE 1
#define FALSE 0

extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32);
extern OSTime __OSGetSystemTime(void);
extern OSTime __OSStartTime;
extern u8 __gUnknown800030E3 : 0x800030E3;
extern s64 fn_800F5ECC(s64, s64); /* __div2i */

extern BOOL lbl_8064D96C;
extern BOOL lbl_8064D970;
extern OSTime lbl_8064D978;
extern OSTime lbl_8064D980;

#define Down lbl_8064D96C
#define LastState lbl_8064D970
#define HoldUp lbl_8064D978
#define HoldDown lbl_8064D980

#define OS_BUS_CLOCK (*(u32 *)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSSecondsToTicks(sec) ((sec) * OS_TIMER_CLOCK)
#define OSTicksToSeconds(ticks) ((ticks) / OS_TIMER_CLOCK)
#define OSMillisecondsToTicks(msec) ((msec) * (OS_TIMER_CLOCK / 1000))
#define OSMicrosecondsToTicks(usec) (((usec) * (OS_TIMER_CLOCK / 125000)) / 8)

#define __PIRegs ((volatile u32 *)0xCC003000)

BOOL fn_8020E290(void) {
    BOOL enabled;
    BOOL state;
    u32 reg;
    OSTime now;

    enabled = OSDisableInterrupts();
    now = __OSGetSystemTime();

    reg = __PIRegs[0];
    if (!(reg & 0x00010000)) {
        if (!Down) {
            Down = TRUE;
            state = HoldUp ? TRUE : FALSE;
            HoldDown = now;
        } else {
            state = (HoldUp || (OSMicrosecondsToTicks(100) < now - HoldDown)) ? TRUE : FALSE;
        }
    } else if (Down) {
        Down = FALSE;
        state = LastState;
        if (state) {
            HoldUp = now;
        } else {
            HoldUp = 0;
        }
    } else if (HoldUp && (now - HoldUp < OSMillisecondsToTicks(40))) {
        state = TRUE;
    } else {
        state = FALSE;
        HoldUp = 0;
    }

    LastState = state;

    if (__gUnknown800030E3 & 0x3F) {
        OSTime fire = (__gUnknown800030E3 & 0x3F) * 60;
        fire = __OSStartTime + OSSecondsToTicks(fire);
        if (fire < now) {
            now -= fire;
            now = fn_800F5ECC(now, OS_TIMER_CLOCK);
            now = fn_800F5ECC(now, 2);
            if ((now & 1) == 0) {
                state = TRUE;
            } else {
                state = FALSE;
            }
        }
    }

    OSRestoreInterrupts(enabled);
    return state;
}
