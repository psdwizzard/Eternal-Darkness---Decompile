typedef signed short s16;

typedef struct TextDescriptor {
    float scale;
    unsigned int color;
    s16 x;
    s16 y;
    s16 width;
} TextDescriptor;

extern volatile float lbl_80651278;

s16 fn_801E63F0(TextDescriptor* text)
{
    int offset = (int)(lbl_80651278 * text->scale);
    return offset + text->width;
}
