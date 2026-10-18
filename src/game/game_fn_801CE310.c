extern void OSEnableInterrupts(void);

void hwIRQLeaveCritical(void)
{
    OSEnableInterrupts();
}
