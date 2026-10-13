/* fn_80233AB0: libvorbis-style mdct_butterflies. */

typedef struct MDCTLookup {
    int n;
    int log2n;
    float *trig;
} MDCTLookup;

extern void fn_80233D1C(float *T);
extern void fn_80233B78(float *T, float *x, int points, int trigint);
extern void fn_80233EB0(float *x);

void fn_80233AB0(MDCTLookup *init, float *x, int points) {
    float *T = init->trig;
    int stages = init->log2n - 5;
    int i, j;
    float *p;

    if (--stages > 0) {
        fn_80233D1C(T);
    }

    for (i = 1; --stages > 0; i++) {
        for (j = 0; j < (1 << i); j++) {
            fn_80233B78(T, x + (points >> i) * j, points >> i, 4 << i);
        }
    }

    for (p = x, j = 0; j < points; j += 32, p += 32) {
        fn_80233EB0(p);
    }
}
