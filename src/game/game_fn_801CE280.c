typedef unsigned short u16;
typedef unsigned int u32;

extern volatile u16 hwIrqLevel;
extern volatile u32 oldState;
extern void OSRestoreInterrupts(u32);

void hwEnableIrq(void)
{
    u16 count = hwIrqLevel - 1;
    hwIrqLevel = count;
    if (count == 0) {
        OSRestoreInterrupts(oldState);
    }
}
