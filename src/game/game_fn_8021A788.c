/* fn_8021A788: __AI_SRC_INIT (Dolphin SDK ai.c). */

typedef unsigned int u32;
typedef long long s64;
typedef s64 OSTime;

volatile u32 __AIRegs[8] : 0xCC006C00;

#define AI_CONTROL 0
#define AI_SAMPLE_COUNTER 2

#define AI_CONTROL_PSTAT 0x01
#define AI_CONTROL_AFR 0x02
#define AI_CONTROL_SCRESET 0x20

extern OSTime OSGetTime(void);

extern OSTime lbl_8064DAF0; /* bound_32KHz */
extern OSTime lbl_8064DAF8; /* bound_48KHz */
extern OSTime lbl_8064DB00; /* min_wait */
extern OSTime lbl_8064DB08; /* max_wait */
extern OSTime lbl_8064DB10; /* buffer */

void fn_8021A788(void) {
    OSTime rise32 = 0;
    OSTime rise48 = 0;
    OSTime diff = 0;
    OSTime t1 = 0;
    OSTime temp = 0;
    u32 temp0 = 0;
    u32 temp1 = 0;
    u32 done = 0;
    u32 walking = 0;
    u32 initCnt = 0;

    walking = 0;
    initCnt = 0;
    temp = 0;

    while (!done) {
        __AIRegs[AI_CONTROL] = (__AIRegs[AI_CONTROL] & ~AI_CONTROL_SCRESET) | AI_CONTROL_SCRESET;
        __AIRegs[AI_CONTROL] &= ~AI_CONTROL_AFR;
        __AIRegs[AI_CONTROL] = (__AIRegs[AI_CONTROL] & ~AI_CONTROL_PSTAT) | AI_CONTROL_PSTAT;

        temp0 = __AIRegs[AI_SAMPLE_COUNTER];
        while (temp0 == __AIRegs[AI_SAMPLE_COUNTER])
            ;
        rise32 = OSGetTime();

        __AIRegs[AI_CONTROL] = (__AIRegs[AI_CONTROL] & ~AI_CONTROL_AFR) | AI_CONTROL_AFR;
        __AIRegs[AI_CONTROL] = (__AIRegs[AI_CONTROL] & ~AI_CONTROL_PSTAT) | AI_CONTROL_PSTAT;

        temp1 = __AIRegs[AI_SAMPLE_COUNTER];
        while (temp1 == __AIRegs[AI_SAMPLE_COUNTER])
            ;
        rise48 = OSGetTime();

        diff = rise48 - rise32;
        __AIRegs[AI_CONTROL] &= ~AI_CONTROL_AFR;
        __AIRegs[AI_CONTROL] &= ~AI_CONTROL_PSTAT;

        if (diff < (lbl_8064DAF0 - lbl_8064DB10)) {
            temp = lbl_8064DB00;
            done = 1;
            ++initCnt;
        } else if (diff >= (lbl_8064DAF0 + lbl_8064DB10) && diff < (lbl_8064DAF8 - lbl_8064DB10)) {
            temp = lbl_8064DB08;
            done = 1;
            ++initCnt;
        } else {
            done = 0;
            walking = 1;
            ++initCnt;
        }
    }

    while ((rise48 + temp) > OSGetTime())
        ;
}
