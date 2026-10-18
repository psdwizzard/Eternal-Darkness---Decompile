typedef struct {
    unsigned char gpr;
    unsigned char fpr;
    unsigned char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} va_list[1];
#define va_start(ap, last) __builtin_va_info(&(ap))

int fwide(void*, int);
int __FileWrite(void*, const char*, unsigned long);
int __pformatter_800FA174(void*, void*, const char*, va_list);

int fprintf(void* stream, const char* format, ...)
{
    va_list args;

    if (fwide(stream, -1) >= 0) {
        return -1;
    }
    va_start(args, format);
    return __pformatter_800FA174(__FileWrite, stream, format, args);
}
