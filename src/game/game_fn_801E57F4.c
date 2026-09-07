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
    s16 width;
    s16 height;
    u32 flags;
    u32 reserved;
    s8 align;
    u8 font;
    char text[1510];
} TextDescriptor;

extern s8 lbl_8064C31A;
extern u32 lbl_8064D580;
extern s16 lbl_8064D576;
extern s16 lbl_8064D578;
extern u32 lbl_8064D594;

extern void* memset(void*, int, unsigned long);
extern int fn_800F9E2C(char*, const char*, void*);
extern void fn_801E5920(char*);
extern void fn_801E6A8C(TextDescriptor*);
extern void fn_801E504C(TextDescriptor*);

void fn_801E57F4(float scale, const char* format, ...)
{
    va_list args;
    TextDescriptor text;
    TextDescriptor* text_ptr = &text;
    s8 align;

    memset(text_ptr, 0, sizeof(text));
    align = lbl_8064C31A;
    text_ptr->x = lbl_8064D576;
    text_ptr->y = lbl_8064D578;
    text_ptr->font = lbl_8064D580;
    text_ptr->align = align;
    text_ptr->scale = scale;
    text_ptr->flags = (u16)(align == 'c' ? 2 : 0);
    text_ptr->color = lbl_8064D594;
    va_start(args, format);
    fn_800F9E2C(text_ptr->text, format, args);
    fn_801E5920(text_ptr->text);
    fn_801E6A8C(text_ptr);
    fn_801E504C(text_ptr);
}
