typedef signed short s16;

typedef struct TextDescriptor {
    float scale;
    unsigned int color;
    s16 x;
} TextDescriptor;

extern float lbl_80651278;

s16 fn_801E6350(TextDescriptor* text)
{
    return text->x - (int)(lbl_80651278 * text->scale);
}
