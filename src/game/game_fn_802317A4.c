#include "src/game/types.h"

extern const float FLOOR_fromdB_LOOKUP[256];

/* Apply a linearly interpolated Vorbis floor curve to the spectrum. */
void render_line(s32 x, s32 end, s32 y, s32 end_y, float *spectrum)
{
    s32 dy, dx, base, remainder, step, error;
    const float *table;

    dy = end_y - y;
    table = FLOOR_fromdB_LOOKUP;
    dx = end - x;
    remainder = __abs(dy);
    base = dy / dx;
    step = base + 1;
    if (dy < 0) {
        step = base - 1;
    }

    spectrum += x;
    error = 0;
    /* Remove the magnitude of the integral rise to get the error increment. */
    remainder -= (((base * dx) >> 31) ^ (base * dx))
                 - ((base * dx) >> 31);
    *spectrum *= table[y];

    while (++x, ++spectrum, x < end) {
        error += remainder;
        if (error >= dx) {
            error -= dx;
            y += step;
        } else {
            y += base;
        }
        *spectrum *= table[y];
    }
}
