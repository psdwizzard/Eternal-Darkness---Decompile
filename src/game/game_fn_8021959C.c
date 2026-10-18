/* PADControlMotor: PADControlMotor */
#include "src/game/types.h"

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int level);
extern u32 SIGetType(s32 chan);
extern void SISetCommand(s32 chan, u32 command); /* SISetCommand */
extern void SITransferCommands(void);                  /* SITransferCommands */

extern u32 EnabledBits; /* EnabledBits */
extern u32 Spec; /* Spec */
extern u32 AnalogMode; /* AnalogMode */

void PADControlMotor(s32 chan, u32 command) {
    int enabled;
    u32 chanBit;

    enabled = OSDisableInterrupts();
    chanBit = 0x80000000 >> chan;
    if ((EnabledBits & chanBit) && !(SIGetType(chan) & 0x20000000)) {
        if (Spec < 2 && command == 2) {
            command = 0;
        }
        SISetCommand(chan, (0x40 << 16) | AnalogMode | (command & (0x1 | 0x2)));
        SITransferCommands();
    }
    OSRestoreInterrupts(enabled);
}
