typedef signed short s16;
typedef unsigned int u32;

/* Complete honest-C reconstruction of the bitfield-to-vector dispatcher. */
#define MAGNITUDE_SWITCH(first, second, third) \
    switch (value & 0x70000) {                 \
    case 0x10000:                              \
        *x = 0; *y = 0; *z = first; return;   \
    case 0x20000:                              \
        *x = 0; *y = 0; *z = second; return;  \
    case 0x40000:                              \
        *x = 0; *y = 0; *z = third; return;   \
    default: return;                            \
    }

#define LOW_SWITCH(a1, a2, a3, b1, b2, b3, c1, c2, c3, d1, d2, d3) \
    switch (value & 0xF) {                                         \
    case 1: MAGNITUDE_SWITCH(a1, a2, a3);                          \
    case 4: MAGNITUDE_SWITCH(b1, b2, b3);                          \
    case 2: MAGNITUDE_SWITCH(c1, c2, c3);                          \
    case 8: MAGNITUDE_SWITCH(d1, d2, d3);                          \
    default: return;                                                \
    }

void fn_801D3E0C(u32 value, s16* x, s16* y, s16* z)
{
    switch (value & 0x1FF0) {
    case 0x300:
        LOW_SWITCH(-5, -10, -15, -5, -10, -15, -5, -10, -15,
                   -15, -30, -50);
    case 0x1040:
        LOW_SWITCH(-30, -40, -50, -10, -20, -30, -30, -40, -50,
                   -40, -50, -60);
    case 0x410:
        LOW_SWITCH(-30, -40, -50, -30, -40, -50, -30, -40, -50,
                   -30, -40, -50);
    case 0x810:
        LOW_SWITCH(-20, -40, -60, -20, -40, -60, -20, -40, -60,
                   -20, -40, -60);
    case 0x1010:
        LOW_SWITCH(-20, -40, -60, -20, -40, -60, -20, -40, -60,
                   -30, -50, -70);
    case 0x480:
        LOW_SWITCH(-10, -20, -30, -10, -20, -30, -10, -20, -30,
                   -10, -20, -30);
    case 0x500:
        LOW_SWITCH(-30, -50, -70, -30, -50, -70, -30, -50, -70,
                   -40, -60, -90);
    case 0x820:
        LOW_SWITCH(-50, -60, -75, -50, -60, -75, -50, -60, -75,
                   -50, -60, -75);
    case 0x440:
        LOW_SWITCH(-10, -15, -20, -10, -15, -20, -10, -15, -20,
                   -20, -30, -40);
    case 0x420:
        LOW_SWITCH(-40, -50, -60, -30, -40, -50, -30, -40, -50,
                   -50, -70, -90);
    }
}
