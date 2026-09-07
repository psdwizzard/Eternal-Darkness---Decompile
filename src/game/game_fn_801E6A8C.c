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
    u8 font;
    s8 text[1510];
} TextDescriptor;

extern float lbl_8064C314;
extern void fn_801E6814(TextDescriptor*, int);
extern s8* fn_801E645C(s8*, int, int*, int*);

void fn_801E6A8C(TextDescriptor* descriptor)
{
    s8* text;
    int lines;
    int total_height;
    int max_width;
    int width;
    int height;
    u16 limit;

    if (descriptor == 0 || descriptor->text == 0)
        return;
    lbl_8064C314 = descriptor->scale;
    text = descriptor->text;
    lines = 0;
    total_height = 0;
    max_width = 0;
    if (!(descriptor->flags & 0x10000))
        fn_801E6814(descriptor, (s8)descriptor->font);
    limit = descriptor->line_limit < 1 ? 1 : descriptor->line_limit;
    descriptor->line_limit = limit;
    while (text[0] != 0 || text[1] != 0) {
        width = 0;
        height = 0;
        text = fn_801E645C(text, (s8)descriptor->font, &width, &height);
        lines++;
        if (width > max_width)
            max_width = width;
        if (descriptor->flags & 0x10) {
            if (lines > descriptor->line_limit)
                break;
            total_height += height;
        } else {
            total_height += height;
        }
    }
    if (!(descriptor->flags & 8) && (descriptor->flags & 1))
        total_height += 29;
    if (descriptor->flags & 2)
        descriptor->x -= max_width >> 1;
    if (descriptor->flags & 4)
        descriptor->y -= total_height >> 1;
    if (!(descriptor->flags & 8) && (descriptor->flags & 1))
        total_height -= 30;
    descriptor->width = max_width;
    descriptor->height = total_height;
}
