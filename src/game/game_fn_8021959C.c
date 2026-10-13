/* fn_8021959C: PADControlMotor */
#include "src/game/types.h"

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern u32 SIGetType(s32 chan);
extern void fn_80208ED4(s32 chan, u32 command); /* SISetCommand */
extern void fn_80208EE8(void);                  /* SITransferCommands */

extern u32 lbl_8064DAB4; /* EnabledBits */
extern u32 lbl_8064C434; /* Spec */
extern u32 lbl_8064C430; /* AnalogMode */

void fn_8021959C(s32 chan, u32 command) {
    int enabled;
    u32 chanBit;

    enabled = OSDisableInterrupts();
    chanBit = 0x80000000 >> chan;
    if ((lbl_8064DAB4 & chanBit) && !(SIGetType(chan) & 0x20000000)) {
        if (lbl_8064C434 < 2 && command == 2) {
            command = 0;
        }
        fn_80208ED4(chan, (0x40 << 16) | lbl_8064C430 | (command & (0x1 | 0x2)));
        fn_80208EE8();
    }
    OSRestoreInterrupts(enabled);
}
