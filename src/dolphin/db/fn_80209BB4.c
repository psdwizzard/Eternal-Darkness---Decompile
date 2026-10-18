typedef unsigned int u32;

typedef struct OSContext OSContext;

extern void OSReport(const char* format, ...);
extern void OSDumpContext(OSContext* context);
extern void PPCHalt(void);

void __DBExceptionDestinationAux(void)
{
    volatile u32 unused;
    OSContext* context = (OSContext*)(*(u32*)0xC0 + 0x80000000);

    OSReport("DBExceptionDestination\n");
    OSDumpContext(context);
    PPCHalt();
}
