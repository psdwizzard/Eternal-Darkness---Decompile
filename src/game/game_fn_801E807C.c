typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    unsigned char gpr;
    unsigned char fpr;
    unsigned char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} va_list[1];

#define va_start(ap, last) __builtin_va_info(&(ap))

extern int fn_800F9E2C(char*, const char*, void*);
extern u32 strlen(const char*);
extern void fn_801E8170(u8, u8, int);

void fn_801E807C(u8 width, u8 fill, const char* format, ...)
{
    va_list args;
    char buffer[256];
    u8 padding;

    va_start(args, format);
    fn_800F9E2C(buffer, format, args);
    padding = (width - (u8)strlen(buffer)) >> 1;
    if (padding != 0) {
        fn_801E8170(padding, fill, 0);
    }
    if (padding != 0) {
        fn_801E8170(padding, fill, 1);
    }
}
