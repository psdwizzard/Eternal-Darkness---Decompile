/* Dolphin SDK OSResetSW.c: debounce the reset switch interrupt. */
typedef unsigned int u32;
typedef long long OSTime;
typedef int BOOL;
typedef struct OSContext OSContext;
typedef void (*OSResetCallback)(void);

extern OSTime __OSGetSystemTime(void);
extern u32 __OSMaskInterrupts(u32 mask);
extern OSResetCallback lbl_8064D968;
extern BOOL lbl_8064D96C;
extern BOOL lbl_8064D970;
extern OSTime lbl_8064D980;
extern u32 __OSBusClock : 0x800000F8;

#define ResetCallback lbl_8064D968
#define Down lbl_8064D96C
#define LastState lbl_8064D970
#define HoldDown lbl_8064D980
#define OS_TIMER_CLOCK (__OSBusClock / 4)
#define OSMicrosecondsToTicks(usec) (((usec) * (OS_TIMER_CLOCK / 125000)) / 8)
#define __PIRegs ((volatile u32 *)0xCC003000)

void __OSResetSWInterruptHandler(short interrupt, OSContext *context) {
    OSResetCallback callback;

    HoldDown = __OSGetSystemTime();
    while (__OSGetSystemTime() - HoldDown < OSMicrosecondsToTicks(100) &&
           !(__PIRegs[0] & 0x10000)) {
    }

    if (!(__PIRegs[0] & 0x10000)) {
        Down = 1;
        LastState = 1;
        __OSMaskInterrupts(0x200);
        if (ResetCallback) {
            callback = ResetCallback;
            ResetCallback = 0;
            callback();
        }
    }
    __PIRegs[0] = 2;
}
