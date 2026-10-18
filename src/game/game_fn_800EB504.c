typedef unsigned int u32;

typedef struct {
    unsigned char gpr;
    unsigned char fpr;
    unsigned char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} va_list[1];

#define va_start(ap, last) __builtin_va_info(&(ap))

extern int lbl_8064CB74;

extern int vsprintf(char*, const char*, void*);
extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32);

void fn_800EB504(const char* format, ...)
{
    va_list args;
    char buffer[256];

    if (lbl_8064CB74 != 0) {
        va_start(args, format);
        vsprintf(buffer, format, args);
        OSRestoreInterrupts(OSDisableInterrupts());
    }
}
