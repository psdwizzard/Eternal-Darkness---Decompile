typedef struct {
    unsigned char gpr;
    unsigned char fpr;
    unsigned char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} va_list[1];

#define va_start(ap, last) __builtin_va_info(&(ap))

extern int fn_800F9E2C(char*, const char*, void*);

void fn_801E7FDC(const char* format, ...)
{
    va_list args;
    char buffer[256];

    va_start(args, format);
    fn_800F9E2C(buffer, format, args);
}
