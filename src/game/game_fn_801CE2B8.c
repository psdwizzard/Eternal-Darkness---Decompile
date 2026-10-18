typedef unsigned short u16;
typedef unsigned int u32;

extern volatile u16 hwIrqLevel;
extern volatile u32 oldState;
extern u32 OSDisableInterrupts(void);

void hwDisableIrq(void)
{
    u16 count = hwIrqLevel;
    hwIrqLevel = count + 1;
    if (count == 0) {
        oldState = OSDisableInterrupts();
    }
}
