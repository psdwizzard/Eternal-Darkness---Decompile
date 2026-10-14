typedef unsigned char u8;
typedef void (*OSExceptionHandler)(u8 exception, void* context);

extern OSExceptionHandler __OSSetExceptionHandler(u8 exception, OSExceptionHandler handler);
extern void OSSwitchFPUContext_8020C484(u8 exception, void* context);
extern void DBPrintf(const char* format, ...);

void __OSContextInit(void) {
    register OSExceptionHandler handler;
    register unsigned int address;

    /* ASM: lis, addi keep handler address setup after the stack prologue;
     * MWCC hoists this setup into the prologue when expressed in C. */
    asm {
        lis address, OSSwitchFPUContext_8020C484@ha
        addi handler, address, OSSwitchFPUContext_8020C484@l
    }
    __OSSetExceptionHandler(7, handler);

    *(void**)0x800000D8 = 0;
    DBPrintf("FPU-unavailable handler installed\n");
}
