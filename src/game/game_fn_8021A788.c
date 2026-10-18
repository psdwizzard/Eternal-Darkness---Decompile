/* __AI_SRC_INIT: __AI_SRC_INIT (Dolphin SDK ai.c). */

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

extern OSTime bound_32KHz; /* bound_32KHz */
extern OSTime bound_48KHz; /* bound_48KHz */
extern OSTime min_wait; /* min_wait */
extern OSTime max_wait; /* max_wait */
extern OSTime buffer; /* buffer */

void __AI_SRC_INIT(void) {
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

        if (diff < (bound_32KHz - buffer)) {
            temp = min_wait;
            done = 1;
            ++initCnt;
        } else if (diff >= (bound_32KHz + buffer) && diff < (bound_48KHz - buffer)) {
            temp = max_wait;
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
