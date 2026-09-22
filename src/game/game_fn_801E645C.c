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
    int value;

    *width = 0;
    font_index <<= 2;
    *height = (int)(lbl_8064C314 * (*(FontDescriptor**)((u8*)lbl_80633418 + font_index))->height);

    /* Explicit backedges keep GC/1.3 from hoisting the unsigned conversion
     * bias into f30 across the outer traversal. */
    goto check_text;
next_text:
    {
        lbl_8064D57C = 0;
        while (*text == '\\' && lbl_8064D57C == 0) {
            ++text;
            if (*text == 'i') {
                int number;
                int digits;
                digits = 0;
                number = 0;
                text++;
                while (*text >= '0' && *text <= '9' && digits < 3) {
                    number *= 10;
                    number += *text - '0';
                    digits++;
                    text++;
                }
                if (number >= 0 && number < 32) {
                    *width += (int)(lbl_8064D59C->widths[number] * lbl_8064C314);
                    value = (int)(lbl_8064D59C->height * lbl_8064C314);
                    if (value > *height)
                        *height = value;
                } else {
                    fn_801E7DCC(lbl_8026461C);
                }
                value = (int)(lbl_8064D59C->height * lbl_8064C314);
                if (value > *height)
                    *height = value;
            } else if (*text == 'r') {
                *width += (int)(lbl_8064D59C->widths[lbl_8064D564 + 26] * lbl_8064C314);
                value = (int)(lbl_8064D59C->height * lbl_8064C314);
                if (value > *height)
                    *height = value;
                text += fn_801E41AC(text) + 1;
            } else {
                text += fn_801E41AC(text) + 1;
            }

            value = (int)(lbl_8064C314 * (*(FontDescriptor**)((u8*)lbl_80633418 + font_index))->height);
            if (value > *height)
                *height = value;
        }

        if (text[0] == 0 && text[1] == 0)
            goto check_text;
        if (*text == '\n')
            return text + 1;

        *width = (int)(*width + lbl_8064C314 * (*(FontDescriptor**)((u8*)lbl_80633418 + font_index))->widths[*text]);
        text++;
    }
check_text:
    if (text[0] != 0 || text[1] != 0)
        goto next_text;
    return text;
}
