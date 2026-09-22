typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TextState {
    float scale;
    u32 color;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    u32 flags;
    u32 unk14;
    u8 font;
    s8 align;
    s8 text[1];
} TextState;

typedef struct FontInfo {
    u32 word0;
    s8 height;
    u8 glyph_width[1];
} FontInfo;

extern FontInfo* lbl_80633418[];
extern u32 lbl_8064D594;
extern float lbl_8064C314;
extern s16 lbl_8064C318;
extern s8 lbl_8064C31A;
extern s16 lbl_8064D574;
extern s16 lbl_8064D578;
extern int lbl_8064D57C;
extern int lbl_8064D580;
extern float lbl_80651260;

extern void fn_801E5AD0(u8);
extern s8* fn_801E645C(s8*, int, int*, int*);
extern void fn_80226AB4(int, int, int);
extern void fn_801E4198(s16, s16, int);
extern void fn_801E418C(u16);
extern void fn_801E4188(void);

void fn_801E504C(TextState* state)
{
    int measured = 0;
    int command = 0;
    s8* cursor = state->text;

    lbl_8064D594 = state->color;
    lbl_8064C314 = state->scale;
    fn_801E5AD0(state->font);
    fn_801E645C(cursor, state->align, &measured, &command);
    lbl_8064C314 = state->scale;

    switch (lbl_8064C31A) {
    case 'l':
        lbl_8064D574 = state->x;
        break;
    case 'r':
        lbl_8064D574 = state->x + state->width - (s16)measured;
        break;
    case 'c':
        lbl_8064D574 = state->x + (state->width >> 1) - ((s16)measured >> 1);
        break;
    }

    while (cursor[0] != 0 || cursor[1] != 0) {
        float scale = lbl_8064C314;
        int glyph_height = (s16)(scale *
            lbl_80633418[(s8)state->align]->height);
        int current;
        if (glyph_height > lbl_8064C318)
            lbl_8064C318 = glyph_height;
        lbl_8064D57C = 0;
        while (*cursor == '\\')
            ++cursor;
        current = (s8)*cursor;

        if (current == '\n') {
            int advance = lbl_8064C318 ? lbl_8064C318 : glyph_height;
            lbl_8064D578 += advance;
            lbl_8064D574 = state->x;
            if (lbl_8064D578 >= state->y + state->height)
                break;
            lbl_8064C318 = 0;
            ++cursor;
            if (*cursor == 0)
                break;
            measured = command = 0;
            fn_801E645C(cursor, lbl_8064D580, &measured, &command);
            lbl_8064C314 = scale;
            switch ((s8)lbl_8064C31A - 'c') {
            case 'l' - 'c':
            case 'n' - 'c':
                lbl_8064D574 = state->x;
                break;
            case 'r' - 'c':
                lbl_8064D574 = state->x + state->width - (s16)measured;
                break;
            case 0:
                lbl_8064D574 = state->x + (state->width >> 1) - ((s16)measured >> 1);
                break;
            }
            continue;
        }

        if (lbl_8064D578 + glyph_height >= state->y) {
            float size = lbl_80651260 * scale;
            int xextent;
            int yextent;
            u16 glyph;
            xextent = (int)size;
            fn_80226AB4(0x80, 5, 4);
            yextent = (s16)size;
            fn_801E4198(lbl_8064D574, lbl_8064D578 + yextent, -1);
            glyph = (u8)current * 4;
            fn_801E418C(glyph + 3);
            fn_801E4198(lbl_8064D574, lbl_8064D578, -1);
            fn_801E418C(glyph);
            fn_801E4198(lbl_8064D574 + xextent, lbl_8064D578, -1);
            fn_801E418C(glyph + 1);
            fn_801E4198(lbl_8064D574 + xextent, lbl_8064D578 + yextent, -1);
            fn_801E418C(glyph + 2);
            fn_801E4188();
        }
        lbl_8064D574 += (s16)(lbl_8064C314 *
            lbl_80633418[lbl_8064D580]->glyph_width[current]);
        ++cursor;
    }
}
