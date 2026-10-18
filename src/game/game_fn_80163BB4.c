typedef struct {
    unsigned char gpr;
    unsigned char fpr;
    unsigned char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} va_list[1];

#define va_start(ap, last) __builtin_va_info(&(ap))

extern int vsprintf(char*, const char*, void*);
extern void lua_error(void*, char*);

void luaO_verror(void* object, const char* format, ...)
{
    va_list args;
    char buffer[284];

    va_start(args, format);
    vsprintf(buffer, format, args);
    lua_error(object, buffer);
}
