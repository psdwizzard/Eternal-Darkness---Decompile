typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TextState {
    float scale; u32 color; s16 x, y, width, height; u32 flags;
    s16 phase; u16 line_limit; u8 align; s8 font; s8 text[1];
} TextState;
typedef struct FontInfo { int value; s8 height; u8 widths[256]; } FontInfo;

extern FontInfo* lbl_80633418[];
extern TextState lbl_80633440[];
extern u32 lbl_8064C2A8, lbl_8064D594;
extern float lbl_8064C314;
extern s16 lbl_8064C318, lbl_8064D574, lbl_8064D578;
extern s8 lbl_8064C31A;
extern char lbl_8064C334, lbl_8064C338;
extern u8 lbl_8064D56C;
extern char lbl_802558E8[0xED10];
extern int lbl_8064D57C, lbl_8064D580;
extern TextState* lbl_8064D598;
extern FontInfo* lbl_8064D59C;
extern float lbl_80651260, lbl_80651280, lbl_80651284;
extern int fn_801E6BF8(TextState*);
extern u32 fn_801E3A34(void*);
extern s8 fn_801E5AD0(u8);
extern s8* fn_801E645C(s8*, int, int*, int*);
extern s8* fn_801E3B08(s8*);
extern void fn_801A8D38(int), fn_801ECF50(u32), fn_801A8EDC(void*);
extern void fn_801ECD74(u32*), fn_801E39A8(u32);
extern s16 fn_80144A2C(u32, s16, s16, int);
extern void fn_8022B970(u32, u32, u32, u32);
extern void fn_801E4314(s16, s16, s16, s16, float, int);
extern void fn_801E4198(int, int, int), fn_801E418C(u16), fn_801E4188(void);
extern void fn_801E5430(s16, s16), fn_801E4704(TextState*);
extern void fn_801E5FB0(TextState*), fn_801E7004(void);
extern void fn_80226AB4(int, int, u16);

#define ABS(a) ((a) < 0 ? -(a) : (a))

void fn_801E47B8(TextState* state)
{
    int measured = 0;
    int command = 0;
    int glyph_height;
    int drew_quad = 0;
    s8* cursor = state->text;
    int scroll_step = 1;
    int line_step;
    u32 setup_color;
    u32 text_color;

    line_step = fn_801E6BF8(state) - state->height;
    setup_color = state->color;
    fn_801E3A34(&setup_color);
    lbl_8064C314 = state->scale;
    fn_801E5AD0(state->align);
    fn_801E645C(cursor, state->font, &measured, &command);
    lbl_8064C314 = state->scale;
    switch (lbl_8064C31A) {
    case 'l': lbl_8064D574 = state->x; break;
    case 'r': lbl_8064D574 = state->x + state->width - (s16)measured; break;
    case 'c': lbl_8064D574 = state->x + (state->width >> 1) - ((s16)measured >> 1); break;
    }

    fn_801A8D38(6);
    if (state->flags & 1) {
        s16 y = state->y;
        s16 height = state->height;
        s16 width;
        if (lbl_80633418[lbl_8064D580]->value <= 255) y += 6;
        if (!(state->flags & 8) && (state->flags & 1)) height += 30;
        width = state->width;
        fn_801E4314(state->x, y, width, height,
                    lbl_8064C314, state->flags & 0x2000);
    }
    fn_801ECF50(6);
    fn_801A8EDC(lbl_802558E8);
    text_color = state->color;
    fn_801ECD74(&text_color);
    fn_801E39A8(state->font);

    if (state->flags & 0x10) {
        int input_step;
        u16 top;
        u16 height;
        if ((s16)fn_80144A2C(0xA00C0000, 0x1FFF, 2, 0) < 1)
            input_step = 1;
        else
            input_step = (s16)fn_80144A2C(0xA00C0000, 0x1FFF, 2, 0);
        line_step += 2;
        if (state->flags & 0x400) {
            state->phase += input_step;
            lbl_8064D578 -= input_step;
            if (state->phase >= line_step) {
                --line_step;
                lbl_8064D578 += state->phase - line_step;
                state->phase = line_step;
                state->flags &= ~0x400U;
                state->flags |= 0x4000;
            }
        } else if (state->flags & 0x1000) {
            state->phase -= input_step;
            lbl_8064D578 += input_step;
            if (state->phase <= 0) {
                lbl_8064D578 += state->phase;
                state->phase = 0;
                state->flags &= ~0x1000U;
            }
        }
        line_step -= 2;
        top = state->y + 6;
        height = state->height;
        fn_8022B970(state->x, top, state->width, height);
    }

    while (cursor[0] != 0 || cursor[1] != 0) {
        float scale;
        int current;
        if (ABS(state->y - lbl_8064D578) < scroll_step)
            scroll_step = ABS(state->y - lbl_8064D578);
        scale = lbl_8064C314;
        glyph_height = (int)(scale * lbl_80633418[state->font]->height);
        if ((s16)glyph_height > lbl_8064C318) lbl_8064C318 = glyph_height;
        lbl_8064D57C = 0;
        while (*cursor == '\\' && lbl_8064D57C == 0)
            cursor = fn_801E3B08(cursor + 1);
        if (*cursor == 0 && cursor[1] == 0) continue;
        current = (s8)*cursor;

        if (current == '\n') {
            int advance = lbl_8064C318 ? lbl_8064C318 : glyph_height;
            float newline_scale;
            lbl_8064D578 += advance;
            lbl_8064D574 = state->x;
            if (lbl_8064D578 > state->y + state->height) break;
            lbl_8064C318 = 0;
            ++cursor;
            if (*cursor == 0) continue;
            measured = 0;
            command = 0;
            newline_scale = lbl_8064C314;
            fn_801E645C(cursor, lbl_8064D580, &measured, &command);
            lbl_8064C314 = newline_scale;
            switch (lbl_8064C31A) {
            case 'l': case 'n': lbl_8064D574 = state->x; break;
            case 'r': lbl_8064D574 = state->x + state->width - (s16)measured; break;
            case 'c': lbl_8064D574 = state->x + (state->width >> 1) - ((s16)measured >> 1); break;
            }
            continue;
        }

        if (lbl_8064D578 + (s16)glyph_height >= state->y) {
            float size = lbl_80651260 * lbl_8064C314;
            int xextent = (int)size;
            s16 yextent;
            int glyph;
            fn_80226AB4(0x80, 5, 4);
            yextent = (s16)size;
            fn_801E4198(lbl_8064D574, (s16)(lbl_8064D578 + yextent), -1);
            glyph = (u16)(current * 4);
            fn_801E418C((u16)(glyph + 3));
            fn_801E4198(lbl_8064D574, lbl_8064D578, -1);
            fn_801E418C(glyph);
            xextent = (s16)xextent;
            fn_801E4198((s16)(lbl_8064D574 + xextent), lbl_8064D578, -1);
            fn_801E418C((u16)(glyph + 1));
            fn_801E4198((s16)(lbl_8064D574 + xextent), (s16)(lbl_8064D578 + yextent), -1);
            fn_801E418C((u16)(glyph + 2));
            fn_801E4188();
            drew_quad = 1;
        }
        lbl_8064D574 += (s16)(lbl_8064C314 *
            lbl_80633418[lbl_8064D580]->widths[(s8)*cursor]);
        ++cursor;
    }

    if (state->flags & 0x10) {
        FontInfo* font;
        s16 indicator_x;
        s16 indicator_y;

        font = lbl_8064D59C;
        indicator_x = state->x +
            ((int)(state->width - lbl_80651280 * font->widths[31]) >> 1);
        indicator_y = state->y - font->height;
        lbl_8064C314 = lbl_80651284;
        if (state->phase >= line_step - 1) {
            if (state->phase >= line_step + 1) state->flags &= ~0x1400;
        } else if (scroll_step == 0) {
            state->flags &= ~0x1400;
        }
        fn_8022B970(0, 0, 640, 480);
        lbl_8064D594 = lbl_8064C2A8;
        ((u8*)&lbl_8064D594)[3] = lbl_8064D56C;
        if (state->phase && !(state->flags & 0x100)) {
            lbl_8064C314 = lbl_80651280;
            fn_801E5430(indicator_x, indicator_y);
            fn_801E3B08((s8*)&lbl_8064C334);
            lbl_8064C314 = lbl_80651284;
        }
        indicator_y += (s8)lbl_8064D59C->height * 2 + state->height;
        if (!(state->flags & 8) && (state->flags & 1)) indicator_y += 30;
        if (!(state->flags & 0x100)) {
            int total = fn_801E6BF8(state);
            if (state->phase < total - state->height - 1) {
                lbl_8064C314 = lbl_80651280;
                fn_801E5430(indicator_x, indicator_y);
                fn_801E3B08((s8*)&lbl_8064C338);
                lbl_8064C314 = lbl_80651284;
            } else fn_801E4704(state);
        }
        if (!drew_quad && state == lbl_8064D598) {
            if (state->flags & 0x200) state->phase = -480;
            else {
                TextState* end = (TextState*)((u8*)lbl_80633440 + 0x3C00);
                TextState* it = lbl_80633440;
                for (; it < end; it = (TextState*)((u8*)it + 0x600))
                    if (it == lbl_8064D598) fn_801E5FB0(it);
                fn_801E7004();
            }
        }
    } else fn_801E4704(state);
}
