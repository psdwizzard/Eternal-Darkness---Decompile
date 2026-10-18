typedef unsigned int u32;

extern u32 OSDisableInterrupts(void);

void hwIRQEnterCritical(void)
{
    OSDisableInterrupts();
}
