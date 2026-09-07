typedef signed short s16;

typedef struct TextDescriptor {
    float scale;
    unsigned int color;
    s16 x;
    s16 y;
} TextDescriptor;

extern void fn_801E6A8C(TextDescriptor*);

void fn_801E6328(TextDescriptor* text, s16 x, s16 y)
{
    text->x = x;
    text->y = y;
    fn_801E6A8C(text);
}
