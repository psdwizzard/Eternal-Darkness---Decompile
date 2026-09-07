typedef signed short s16;

typedef struct TextDescriptor {
    float scale;
    unsigned int color;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} TextDescriptor;

void fn_801E6454(TextDescriptor* text, s16 height)
{
    text->height = height;
}
