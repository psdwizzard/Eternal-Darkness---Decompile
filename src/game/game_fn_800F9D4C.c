typedef struct {
    unsigned char gpr;
    unsigned char fpr;
    unsigned char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} va_list[1];
#define va_start(ap, last) __builtin_va_info(&(ap))

typedef struct StringWriteState {
    char* buffer;
    unsigned long limit;
    unsigned long used;
} StringWriteState;

int __StringWrite(StringWriteState*, const char*, unsigned long);
int __pformatter_800FA174(void*, void*, const char*, va_list);

int sprintf(char* buffer, const char* format, ...)
{
    int result;
    va_list args;
    StringWriteState state;

    va_start(args, format);
    state.buffer = buffer;
    state.limit = (unsigned long)-1;
    state.used = 0;
    result = __pformatter_800FA174(__StringWrite, &state, format, args);
    if (buffer != 0) {
        buffer[result < (unsigned long)-1 ? result : (unsigned long)-2] = 0;
    }
    return result;
}
