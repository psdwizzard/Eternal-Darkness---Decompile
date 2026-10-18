typedef unsigned int u32;

typedef struct {
    unsigned char gpr;
    unsigned char fpr;
    unsigned char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} va_list[1];

#define va_start(ap, last) __builtin_va_info(&(ap))
#define va_end(ap) ((void)0)

extern int OSDisableInterrupts(void);
extern int vprintf(const char*, va_list);
extern void OSReport(const char*, ...);
extern u32* OSGetStackPointer(void); /* OSGetStackPointer */
extern void PPCHalt(void);

/* OSPanic */
void OSPanic(const char* file, int line, const char* msg, ...)
{
    va_list marker;
    u32 i;
    u32* p;

    OSDisableInterrupts();
    va_start(marker, msg);
    vprintf(msg, marker);
    va_end(marker);
    OSReport(" in \"%s\" on line %d.\n", file, line);

    OSReport("\nAddress:      Back Chain    LR Save\n");
    for (i = 0, p = OSGetStackPointer(); p && (u32)p != 0xffffffff && i++ < 16;
         p = (u32*)*p) {
        OSReport("0x%08x:   0x%08x    0x%08x\n", p, p[0], p[1]);
    }

    PPCHalt();
}
