typedef unsigned char u8;
typedef signed short s16;

typedef struct Color {
    u8 r, g, b, a;
} Color;

typedef struct RectState {
    s16 x0, y0, z0;
    s16 x1, y1, z1;
    s16 x2, y2, z2;
    s16 x3, y3, z3;
} RectState;

typedef struct DisplayBody {
    RectState rects[2];
    Color colors[2][4];
    Color secondary[2][4];
} DisplayBody;

typedef struct DisplayState {
    unsigned int first;
    Color color;
    DisplayBody background;
    DisplayBody foreground;
    u8 pad_E8[4];
    s16 top;
    s16 height;
} DisplayState;

extern Color lbl_80651A90;

void fn_800CD1FC(DisplayState *state, Color *background, Color *foreground,
                 s16 height)
{
    DisplayBody *back_rect = &state->background;
    DisplayBody *back_color = back_rect;
    DisplayBody *front_rect = &state->foreground;
    DisplayBody *front_color = front_rect;
    Color faded = *foreground;
    Color clear = lbl_80651A90;
    int y = 0;
    int i;

    state->color = *background;
    faded.a -= 60;
    state->height = height;
    state->top = 0;
    for (i = 0; i < 2; i++) {
        RectState *v = &back_rect->rects[i];
        v->x0 = 0;
        v->y0 = y;
        v->z0 = -1;
        v->x1 = 640;
        v->y1 = y;
        v->z1 = -1;
        v->x2 = 640;
        v->y2 = y + 480;
        v->z2 = -1;
        v->x3 = 0;
        v->y3 = y + 480;
        v->z3 = -1;
        back_color->colors[i][0] = back_color->colors[i][1] =
            back_color->colors[i][2] = back_color->colors[i][3] = *background;
        back_color->secondary[i][0] = back_color->secondary[i][1] =
            back_color->secondary[i][2] = back_color->secondary[i][3] = clear;
        y = state->top;
        {
            RectState *f = &front_rect->rects[i];
            f->x0 = 0;
            f->y0 = y;
            f->z0 = -1;
            f->x1 = 640;
            f->y1 = y;
            f->z1 = -1;
            f->x2 = 640;
            f->y2 = y + height;
            f->z2 = -1;
            f->x3 = 0;
            f->y3 = y + height;
            f->z3 = -1;
        }
        front_color->colors[i][0] = front_color->colors[i][1] = faded;
        front_color->colors[i][2] = front_color->colors[i][3] = *foreground;
        front_color->secondary[i][0] = front_color->secondary[i][1] =
            front_color->secondary[i][2] = front_color->secondary[i][3] = clear;
    }
}
