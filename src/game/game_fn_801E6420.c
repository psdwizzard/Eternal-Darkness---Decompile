typedef signed short s16;

typedef struct TextDescriptor {
    float scale;
    unsigned int color;
    s16 x;
    s16 y;
    s16 width;
    volatile s16 height;
} TextDescriptor;

extern volatile float lbl_80651278;

s16 fn_801E6420(TextDescriptor* text)
{
    int converted = (int)(lbl_80651278 * text->scale);
    return converted + text->height + 6;
}
