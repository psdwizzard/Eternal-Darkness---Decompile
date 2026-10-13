/* fn_80233978: FFT real-output post-processing (split butterfly). */

typedef struct FFTState {
    int n;
    int unk4;
    float *twiddle;
    int *index;
} FFTState;

extern float lbl_80651838; /* 0.5 */

void fn_80233978(FFTState *fft, float *out) {
    int n;
    float *lo;
    float *hi;
    float *tw;
    int *idx;
    float *a;
    float *b;
    float ai, bi, ar, br, di, sr, s, t, x, y;

    n = fft->n;
    lo = out;
    tw = fft->twiddle + n;
    out += n >> 1;
    idx = fft->index;
    hi = out;

    do {
        a = out + idx[0];
        b = out + idx[1];
        ai = a[1];
        bi = b[1];
        ar = a[0];
        br = b[0];
        di = ai - bi;
        sr = ar + br;
        s = lbl_80651838 *(ai + bi);
        x = sr * tw[0] + di * tw[1];
        y = sr * tw[1] - di * tw[0];
        t = lbl_80651838 *(ar - br);
        lo[0] = s + x;
        hi[-2] = s - x;
        lo[1] = t + y;
        hi[-1] = y - t;

        a = out + idx[2];
        b = out + idx[3];
        ai = a[1];
        bi = b[1];
        ar = a[0];
        br = b[0];
        di = ai - bi;
        sr = ar + br;
        s = lbl_80651838 *(ai + bi);
        x = sr * tw[2] + di * tw[3];
        y = sr * tw[3] - di * tw[2];
        t = lbl_80651838 *(ar - br);
        lo[2] = s + x;
        hi[-4] = s - x;
        lo[3] = t + y;
        hi[-3] = y - t;

        idx += 4;
        tw += 4;
        lo += 4;
        hi -= 4;
    } while (lo < hi);
}
