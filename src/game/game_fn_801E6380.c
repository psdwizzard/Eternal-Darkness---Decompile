typedef signed short s16;
typedef unsigned int u32;

typedef struct TextDescriptor {
    float scale;
    u32 color;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    u32 flags;
} TextDescriptor;

typedef struct FontInfo {
    int value;
} FontInfo;

extern float lbl_80651278;
extern u32 lbl_8064D580;
extern FontInfo* lbl_80633418[];

s16 fn_801E6380(TextDescriptor* text)
{
    int offset = (int)(lbl_80651278 * text->scale);

    if ((text->flags & 1) && lbl_80633418[lbl_8064D580]->value <= 255)
        return text->y - offset + 6;
    return text->y - offset;
}
