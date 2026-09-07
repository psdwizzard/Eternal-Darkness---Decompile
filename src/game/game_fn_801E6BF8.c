typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TextDescriptor {
    float scale;
    u32 color;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    u32 flags;
    u16 unknown14;
    u16 line_limit;
    s8 align;
    s8 font;
    s8 text[1510];
} TextDescriptor;

extern float lbl_8064C314;
extern s8* fn_801E645C(s8*, int, int*, int*);

int fn_801E6BF8(TextDescriptor* descriptor)
{
    TextDescriptor* desc;
    int total_height;
    int zero;
    s8* text;
    int height;
    int width;
    u16 limit;

    desc = descriptor;
    total_height = 0;
    text = desc->text;
    limit = desc->line_limit < 1 ? 1 : desc->line_limit;
    desc->line_limit = limit;
    zero = 0;
    lbl_8064C314 = desc->scale;
    while (text[0] != 0 || text[1] != 0) {
        height = zero;
        width = zero;
        text = fn_801E645C(text, desc->font, &width, &height);
        total_height += height;
    }
    return total_height;
}
