typedef struct {
    unsigned char gpr;
    unsigned char fpr;
    unsigned char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} va_list[1];

#define va_start(ap, last) __builtin_va_info(&(ap))

extern unsigned char __files[];
extern char lbl_8024F008[];
extern char lbl_8064BA18[8];
extern int vsprintf(char*, const char*, void*);
extern int fprintf(void*, const char*, ...);
extern void exit(int);

void fn_80155BB0(const char* file, const char* format, ...)
{
    va_list args;
    char buffer[512];

    va_start(args, format);
    vsprintf(buffer, format, args);
    if (file == 0)
        file = lbl_8024F008;
    fprintf(__files + 0xA0, lbl_8064BA18, file, buffer);
    exit(1);
}
