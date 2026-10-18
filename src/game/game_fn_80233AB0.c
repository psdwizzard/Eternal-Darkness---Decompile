/* mdct_butterflies: libvorbis-style mdct_butterflies. */

typedef struct MDCTLookup {
    int n;
    int log2n;
    float *trig;
} MDCTLookup;

extern void mdct_butterfly_first(float *T, float *x, int points);
extern void mdct_butterfly_generic(float *T, float *x, int points, int trigint);
extern void mdct_butterfly_32(float *x);

void mdct_butterflies(MDCTLookup *init, register float *data, register int count) {
    register int offset, trigint, bound;
    register float *p;
    register int stride, k;
    register float *T;
    int stages;
    int i, j;
    register int points;
    register float *x;

    /* ASM: mr preserves the incoming argument copies; C selects addi. */
    asm {
        mr x, data
        mr points, count
    }
    T = init->trig;
    stages = init->log2n - 5;

    if (--stages > 0) {
        mdct_butterfly_first(T, data, count);
    }

    for (i = 1; --stages > 0; i++) {
        stride = points >> i;
        trigint = 4 << i;
        bound = 1 << i;
        for (j = 0, offset = 0; j < bound; j++, offset += stride) {
            register float *callT;
            register int callStride, callTrigint;
            unsigned int byteOffset = offset * sizeof(float);
            /* ASM: mr and or retain register argument copies; C selects addi. */
            asm {
                mr callT, T
                mr callStride, stride
                or callTrigint, trigint, trigint
            }
            mdct_butterfly_generic(callT, (float *)((char *)x + byteOffset), callStride, callTrigint);
        }
    }

    /* ASM: mr and li preserve the buffer copy; C selects addi. */
    asm {
        mr p, x
        li k, 0
    }
    for (; k < points; k += 32) {
        mdct_butterfly_32(p);
        p += 32;
    }
}
