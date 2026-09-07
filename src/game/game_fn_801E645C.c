typedef signed char s8;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct FontDescriptor {
    u8 reserved[4];
    s8 height;
    u8 widths[256];
} FontDescriptor;

extern FontDescriptor* lbl_80633418[];
extern FontDescriptor* lbl_8064D59C;
extern int lbl_8064D564;
extern int lbl_8064D57C;
extern float lbl_8064C314;
extern void fn_801E7DCC(const char*, ...);
extern int fn_801E41AC(const s8*);
extern char lbl_8026461C[];

s8* fn_801E645C(s8* text, int font_index, int* width, int* height)
{
    u32 font;
    int value;
    int digits;

    *width = 0;
    font = (u32)lbl_80633418 + (font_index << 2);
    *height = (int)(lbl_8064C314 * (*(FontDescriptor**)font)->height);

    while (text[0] != 0 || text[1] != 0) {
        lbl_8064D57C = 0;
        while (*text == '\\' && lbl_8064D57C == 0) {
            ++text;
            if (*text == 'i') {
                value = 0;
                digits = 0;
                text++;
                while (*text >= '0' && *text <= '9' && digits < 3) {
                    value = value * 10 + *text - '0';
                    digits++;
                    text++;
                }
                if (value >= 0 && value < 32) {
                    *width += (int)(lbl_8064C314 * lbl_8064D59C->widths[value]);
                    value = (int)(lbl_8064C314 * lbl_8064D59C->height);
                    if (value > *height)
                        *height = value;
                } else {
                    fn_801E7DCC(lbl_8026461C);
                }
                value = (int)(lbl_8064C314 * lbl_8064D59C->height);
                if (value > *height)
                    *height = value;
            } else if (*text == 'r') {
                value = lbl_8064D564 + 31;
                *width += (int)(lbl_8064C314 * ((u8*)lbl_8064D59C)[value]);
                value = (int)(lbl_8064C314 * lbl_8064D59C->height);
                if (value > *height)
                    *height = value;
                text += fn_801E41AC(text) + 1;
            } else {
                text += fn_801E41AC(text) + 1;
            }

            value = (int)(lbl_8064C314 * (*(FontDescriptor**)font)->height);
            if (value > *height)
                *height = value;
        }

        if (text[0] == 0 && text[1] == 0)
            break;
        if (*text == '\n')
            return text + 1;

        *width = (int)(*width + lbl_8064C314 * (*(FontDescriptor**)font)->widths[*text]);
        text++;
    }
    return text;
}
