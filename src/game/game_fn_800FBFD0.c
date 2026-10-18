typedef struct {
    unsigned char gpr;
    unsigned char fpr;
    unsigned char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} va_list[1];

#define va_start(ap, last) __builtin_va_info(&(ap))

typedef struct StringReadState {
    const char* cursor;
    int null_seen;
} StringReadState;

typedef int (*ReadProcType)(void*, int, int);

int __StringRead(StringReadState*, int, int);
int __sformatter(ReadProcType, void*, const char*, va_list);

int sscanf(const char* str, const char* format, ...)
{
    va_list args;
    StringReadState state;

    va_start(args, format);
    state.cursor = str;
    if (str == 0 || (signed char)*str == 0) {
        return -1;
    }
    state.null_seen = 0;
    return __sformatter((ReadProcType)__StringRead, &state, format, args);
}
