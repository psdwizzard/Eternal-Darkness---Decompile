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
    s16 phase;
    u8 font;
    s8 align;
    char text[1];
} TextState;

typedef struct FontInfo {
    u32 word0;
    s8 height;
    u8 glyph_width[1];
} FontInfo;

extern FontInfo* lbl_80633418[];
extern float lbl_8064D594;
extern s16 lbl_8064D598;
extern double lbl_8064E7F0;
extern s16 lbl_8064E7F8;
extern int lbl_8064E7FC;
extern int lbl_8064E800;
extern u32 lbl_8064E814;
extern TextState* lbl_8064E818;
extern u8 lbl_8064E7EC;
extern u32 lbl_8064D528;
extern char lbl_8064D5B4[];
extern char lbl_8064D5B8[];
extern float lbl_8065127C;
extern float lbl_80651280;

#define text_x (*(s16*)((char*)&lbl_8064E7F0 + 4))

extern int fn_801E6BF8(TextState*);
extern void fn_801E3A34(u32*);
extern void fn_801E5AD0(u8);
extern char* fn_801E645C(char*, int, int*, int*);
extern char* fn_801E3B08(char*);
extern void fn_801A8D38(int);
extern void fn_801ECF50(int);
extern void fn_801A8EDC(void*);
extern void fn_801ECD74(u32*);
extern void fn_801E39A8(int);
extern s16 fn_80144A2C(u32, int, int, int);
extern void fn_8022B970(s16, u16, s16, u16);
extern void fn_801E4314(s16, s16, s16, s16, float, u32);
extern void fn_801E4198(s16, s16, int);
extern void fn_801E418C(u16);
extern void fn_801E4188(void);
extern void fn_801E5430(s16, s16);
extern void fn_801E4704(TextState*);
extern void fn_801E5FB0(TextState*);
extern void fn_801E7004(void);
extern void fn_80226AB4(int, int, int);

/*
 * Main text-box renderer.  This intentionally keeps the recovered phases in
 * one function: measure the command stream, establish alignment and clipping,
 * consume glyphs/escapes while advancing the pen, then draw scroll indicators
 * and service the active-box transition.  Register coloring and several
 * graphics-state details remain under investigation.
 */
void fn_801E47B8(TextState* state)
{
    int measured = 0;
    int command = 0;
    int line_step;
    int scroll_step = 1;
    int drew_quad = 0;
    char* text = state->text;
    char* cursor;
    u32 color;

    line_step = fn_801E6BF8(state) - state->height;
    color = state->color;
    fn_801E3A34(&color);
    lbl_8064D594 = state->scale;
    fn_801E5AD0(state->font);
    cursor = fn_801E645C(text, state->align, &measured, &command);
    lbl_8064D594 = state->scale;

    switch ((s8)cursor[-1]) {
    case 'l':
        text_x = state->x;
        break;
    case 'r':
        text_x = state->x + state->width - (s16)measured;
        break;
    case 'c':
        text_x = state->x + state->width / 2 - (s16)measured / 2;
        break;
    }

    fn_801A8D38(6);
    if (state->flags & 1) {
        s16 y = state->y;
        FontInfo* font = lbl_80633418[lbl_8064E800];
        if (font->word0 <= 255)
            y += 6;
        if (!(state->flags & 8))
            y += 30;
        fn_801E4314(state->x, y, state->width, state->height,
                    lbl_8064D594, state->flags & 0x2000);
    }
    fn_801ECF50(6);
    fn_801A8EDC((void*)0x802558E8);
    color = state->color;
    fn_801ECD74(&color);
    fn_801E39A8(state->align);

    if (state->flags & 0x10) {
        scroll_step = fn_80144A2C(0xA00C0000, 0x1FFF, 2, 0);
        if (scroll_step < 1)
            scroll_step = 1;
        line_step += 2;
        if (state->flags & 0x400) {
            state->phase += scroll_step;
            lbl_8064E7F8 -= scroll_step;
            if (state->phase >= line_step) {
                lbl_8064E7F8 += state->phase - (line_step - 1);
                state->phase = line_step - 1;
                state->flags &= ~0x400;
                state->flags |= 0x4000;
            }
        } else if (state->flags & 0x1000) {
            state->phase -= scroll_step;
            lbl_8064E7F8 += scroll_step;
            if (state->phase <= 0) {
                lbl_8064E7F8 += state->phase;
                state->phase = 0;
                state->flags &= ~0x1000;
            }
        }
        line_step -= 2;
        fn_8022B970(state->x, state->y + 6, state->width, state->height);
    }

    while (cursor[0] != 0 || cursor[1] != 0) {
        int glyph_width;
        int delta = lbl_8064E7F8 - state->y;
        if (delta < 0)
            delta = -delta;
        if (delta < scroll_step)
            scroll_step = delta;

        glyph_width = (s16)(lbl_8064D594 *
            lbl_80633418[(s8)state->align]->height);
        if (glyph_width > lbl_8064D598)
            lbl_8064D598 = glyph_width;
        lbl_8064E7FC = 0;
        while (*cursor == '\\' && !lbl_8064E7FC)
            cursor = fn_801E3B08(cursor + 1);
        if (*cursor == 0 && cursor[1] == 0)
            break;

        if (*cursor == '\n') {
            int advance = lbl_8064D598 ? lbl_8064D598 : glyph_width;
            lbl_8064E7F8 += advance;
            text_x = state->x;
            if (lbl_8064E7F8 > state->y + state->height)
                break;
            lbl_8064D598 = 0;
            ++cursor;
            if (*cursor == 0)
                break;
            fn_801E645C(cursor, lbl_8064E800, &measured, &command);
            lbl_8064D594 = state->scale;
            switch ((s8)cursor[-1]) {
            case 'l': text_x = state->x; break;
            case 'r': text_x = state->x + state->width - (s16)measured; break;
            case 'c': text_x = state->x + state->width / 2 - (s16)measured / 2; break;
            }
            continue;
        }

        if (lbl_8064E7F8 + glyph_width >= state->y) {
            float quad = lbl_8065127C * lbl_8064D594;
            int h = (s16)quad;
            int w;
            fn_80226AB4(0x80, 5, 4);
            w = (s16)quad;
            fn_801E4198(text_x, lbl_8064E7F8 + w, -1);
            fn_801E418C((u16)((u8)*cursor * 4 + 3));
            fn_801E4198(text_x, lbl_8064E7F8, -1);
            fn_801E418C((u16)((u8)*cursor * 4));
            fn_801E4198(text_x + h, lbl_8064E7F8, -1);
            fn_801E418C((u16)((u8)*cursor * 4 + 1));
            fn_801E4198(text_x + h, lbl_8064E7F8 + w, -1);
            fn_801E418C((u16)((u8)*cursor * 4 + 2));
            fn_801E4188();
            drew_quad = 1;
        }
        text_x += (s16)(lbl_8064D594 *
            lbl_80633418[lbl_8064E800]->glyph_width[(u8)*cursor + 5]);
        ++cursor;
    }

    if (state->flags & 0x10) {
        fn_8022B970(0, 0, 640, 480);
        lbl_8064E814 = lbl_8064D528;
        ((u8*)&lbl_8064E814)[3] = lbl_8064E7EC;
        if (state->phase && !(state->flags & 0x100)) {
            lbl_8064D594 = lbl_8065127C;
            fn_801E5430(state->x, state->y);
            fn_801E3B08(lbl_8064D5B4);
            lbl_8064D594 = lbl_80651280;
        }
        if (!(state->flags & 0x100)) {
            if (state->phase < fn_801E6BF8(state) - state->height - 1) {
                lbl_8064D594 = lbl_8065127C;
                fn_801E5430(state->x, state->y + state->height);
                fn_801E3B08(lbl_8064D5B8);
                lbl_8064D594 = lbl_80651280;
            } else {
                fn_801E4704(state);
            }
        }
    }
    if (!drew_quad && state == lbl_8064E818) {
        if (state->flags & 0x200) {
            state->phase = -480;
        } else {
            TextState* it = (TextState*)0x80633440;
            TextState* end = (TextState*)0x80637040;
            for (; it < end; it = (TextState*)((char*)it + 0x600)) {
                if (it == lbl_8064E818)
                    fn_801E5FB0(it);
            }
            fn_801E7004();
        }
    } else if (!(state->flags & 0x10)) {
        fn_801E4704(state);
    }
}
