typedef signed short s16;
typedef unsigned int u32;

typedef struct {
    unsigned char gpr;
    unsigned char fpr;
    unsigned char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} va_list[1];

#define va_start(ap, last) __builtin_va_info(&(ap))

extern char lbl_80637040[];
extern int fn_800F9E2C(char*, const char*, void*);
extern u32 fn_801E3A34(u32*);
extern void fn_801E5448(s16, s16, float, const char*, ...);

void fn_801E5594(s16 x, s16 y, float scale, u32* color, u32* shadow,
                 const char* format, ...)
{
    va_list args;
    u32 shadow_value;
    u32 color_value;

    va_start(args, format);
    fn_800F9E2C(lbl_80637040, format, args);
    shadow_value = *shadow;
    fn_801E3A34(&shadow_value);
    fn_801E5448(x + 2, y + 2, scale, lbl_80637040);
    color_value = *color;
    fn_801E3A34(&color_value);
    fn_801E5448(x, y, scale, lbl_80637040);
}
