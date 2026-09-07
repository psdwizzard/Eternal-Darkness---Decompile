typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct {
    u8 gpr;
    u8 fpr;
    u8 reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} va_list[1];

#define va_start(ap, last) __builtin_va_info(&(ap))

typedef struct TextDescriptor {
    float scale;
    u32 color;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    u32 flags;
    u32 reserved;
    s8 align;
    u8 font;
    char text[1510];
} TextDescriptor;

extern void* memset(void*, int, unsigned long);
extern int fn_800F9E2C(char*, const char*, void*);
extern void fn_801E5920(char*);
extern void fn_801E6A8C(TextDescriptor*);

void fn_801E6228(TextDescriptor* text, const char* format, ...)
{
    va_list args;

    memset(text->text, 0, sizeof(text->text));
    va_start(args, format);
    fn_800F9E2C(text->text, format, args);
    fn_801E5920(text->text);
    if (text->flags & 2)
        text->x += text->width >> 1;
    if (text->flags & 4)
        text->y += text->height >> 1;
    fn_801E6A8C(text);
}
