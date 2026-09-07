typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct FontDescriptor {
    u8 reserved[4];
    s8 height;
    u8 widths[256];
} FontDescriptor;

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
    s8 text[1510];
} TextDescriptor;

extern FontDescriptor* lbl_80633418[];
extern FontDescriptor* lbl_8064D59C;
extern int lbl_8064D564;
extern int lbl_8064D57C;
extern unsigned int lbl_8064D584;
extern float lbl_8064C314;
extern void fn_801E7DCC(const char*, ...);
extern int fn_801E41AC(const s8*);
extern char lbl_8026461C[];

void fn_801E6814(TextDescriptor* descriptor, unsigned int font_index)
{
    u32 fonts;
    unsigned int font_offset;
    s8* text;
    s8* space;
    int width;
    int value;
    int digits;

    if (descriptor == 0)
        return;
    if (descriptor->text == 0)
        return;
    if (font_index >= lbl_8064D584)
        return;

    text = descriptor->text;
    if (text == 0)
        return;

    fonts = (u32)lbl_80633418;
    font_offset = font_index << 2;
    space = 0;
    width = 0;

    while (text[0] != 0 || text[1] != 0) {
        lbl_8064D57C = 0;
        while (*text == '\\' && lbl_8064D57C == 0) {
            ++text;
            if (*text == 'i') {
                value = 0;
                digits = 0;
                text++;
                while (*text >= '0' && *text <= '9' && digits < 3) {
                    value = value * 10 + *text;
                    digits++;
                    text++;
                    value -= '0';
                }
                if (value >= 0 && value < 32) {
                    width += (int)(lbl_8064C314 * lbl_8064D59C->widths[value]);
                } else {
                    fn_801E7DCC(lbl_8026461C);
                }
            } else if (*text == 'r') {
                value = lbl_8064D564 + 31;
                width += (int)(lbl_8064C314 * ((u8*)lbl_8064D59C)[value]);
                text += fn_801E41AC(text) + 1;
            } else {
                text += fn_801E41AC(text) + 1;
            }
        }

        if (text[0] == 0 && text[1] == 0)
            break;
        if (*text == '\n') {
            space = 0;
            width = 0;
            text++;
            continue;
        }

        width = (int)(width + lbl_8064C314 * (*(FontDescriptor**)(fonts + font_offset))->widths[*text]);
        if (*text == ' ')
            space = text;
        if (width > 568 && space != 0) {
            *space = '\n';
            text = space;
            width = 0;
            space = 0;
        }
        text++;
    }
}
