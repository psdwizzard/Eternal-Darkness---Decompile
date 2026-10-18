typedef void (*EntryPoint)(void);

extern int OSDisableInterrupts(void);
extern void ICFlashInvalidate(void);

/* Start execution at entry with interrupts disabled and the cache invalidated. */
void Run(register EntryPoint entry)
{
    OSDisableInterrupts();
    ICFlashInvalidate();
    __sync();
    __isync();

    /* ASM: mtlr installs the entry address in the link register. A C function
     * pointer call uses a linking branch and restores this frame on return. */
    asm { mtlr entry }

    for (;;) {
        /* ASM: blr jumps to the entry without unwinding this stack frame;
         * C cannot express this transfer with the current frame preserved. */
        asm { blr }
    }
}
