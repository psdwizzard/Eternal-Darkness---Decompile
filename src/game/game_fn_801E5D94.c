typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
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
    u32 reserved;
    u32 flags;
    s16 width;
    u16 phase;
    s8 align;
    u8 font;
    s8 text[1510];
} TextDescriptor;

extern TextDescriptor lbl_80633440[];
extern char lbl_80264994[];

extern void* memset(void*, int, unsigned long);
extern int fn_800F9E2C(char*, const char*, void*);
extern void fn_801E5920(char*);
extern void fn_801E6A8C(TextDescriptor*);
extern void fn_801E7DCC(const char*, ...);

TextDescriptor* fn_801E5D94(s16 x, s16 y, u8 font, s8 align, float scale,
                             u32 flags, u32* color, u16 phase,
                             const char* format, ...)
{
    va_list args;
    TextDescriptor* text_ptr;
    int index;

    text_ptr = lbl_80633440;
    index = 0;
    while (index < 10 && (text_ptr->text[0] != 0 || text_ptr->text[1] != 0)) {
        index++;
        if (index < 10) {
            text_ptr++;
        }
    }

    if (text_ptr->text[0] != 0 || text_ptr->text[1] != 0) {
        fn_801E7DCC(lbl_80264994);
    }

    memset(text_ptr, 0, sizeof(*text_ptr));
    va_start(args, format);
    fn_800F9E2C((char*)text_ptr->text, format, args);
    text_ptr->x = x;
    text_ptr->y = y;
    text_ptr->font = font;
    text_ptr->align = align;
    text_ptr->scale = scale;
    text_ptr->flags = flags;
    text_ptr->color = *color;
    text_ptr->phase = phase;
    text_ptr->width = 0;
    fn_801E5920((char*)text_ptr->text);
    fn_801E6A8C(text_ptr);
    return text_ptr;
}
