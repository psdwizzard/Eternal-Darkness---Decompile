/* Inverse MDCT bit reversal and final split butterflies. */
typedef struct mdct_lookup {
    int n;
    int log2n;
    float *trig;
    int *bitrev;
    float scale;
} mdct_lookup;

extern float lbl_80651838; /* 0.5f */

void mdct_bitreverse(mdct_lookup *init, float *x) {
    float half = lbl_80651838;
    int n = init->n;
    int *bit = init->bitrev;
    float *lo = x;
    float *hi = x = x + (n >> 1);
    float *twiddle = init->trig + n;

    do {
        int i;
        /* Process two bit-reversed pairs per outer iteration. */
        for (i = 0; i < 2; i++) {
            float real_sum, rot_imag, half_imag_sum, imag_diff, rot_real, half_real_diff;
            float *a = x + bit[0];
            float *b = x + bit[1];
            imag_diff = a[1] - b[1];
            real_sum = a[0] + b[0];
            rot_real = real_sum * twiddle[0] + imag_diff * twiddle[1];
            rot_imag = real_sum * twiddle[1] - imag_diff * twiddle[0];

            half_imag_sum = half * (a[1] + b[1]);
            half_real_diff = half * (a[0] - b[0]);
            lo[0] = half_imag_sum + rot_real;
            hi[-2] = half_imag_sum - rot_real;
            lo[1] = half_real_diff + rot_imag;
            hi[-1] = rot_imag - half_real_diff;

            twiddle += 2;
            bit += 2;
            lo += 2;
            hi -= 2;
        }
    } while (lo < hi);
}
