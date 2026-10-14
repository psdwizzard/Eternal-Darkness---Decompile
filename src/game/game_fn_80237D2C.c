typedef int s32;
typedef struct OSThread OSThread;

extern OSThread lbl_8064A1F8;
extern s32 lbl_8064DC6C;
extern s32 fn_802101F4(OSThread *thread, s32 priority);

void fn_80237D2C(s32 highPriority) {
    register OSThread *thread;
    register s32 priority;

    if (highPriority != 0) {
        /* ASM: lis/addi/addi keep the immediate priority load between the
         * two address instructions; C schedules it after both. */
        asm {
            lis thread, lbl_8064A1F8@ha
            addi priority, 0, 8
            addi thread, thread, lbl_8064A1F8@l
        }
        fn_802101F4(thread, priority);
        /* ASM: li/stw use r0 for the recorded priority; following inline
         * argument setup, C selects r3 for this constant store. */
        asm {
            li r0, 8
            stw r0, lbl_8064DC6C
        }
    } else {
        /* ASM: lis/addi/addi keep the immediate priority load between the
         * two address instructions; C schedules it after both. */
        asm {
            lis thread, lbl_8064A1F8@ha
            addi priority, 0, 0x12
            addi thread, thread, lbl_8064A1F8@l
        }
        fn_802101F4(thread, priority);
        /* ASM: li/stw use r0 for the recorded priority; following inline
         * argument setup, C selects r3 for this constant store. */
        asm {
            li r0, 0x12
            stw r0, lbl_8064DC6C
        }
    }
}
