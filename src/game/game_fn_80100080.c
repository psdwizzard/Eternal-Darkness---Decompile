/* __ieee754_rem_pio2: fdlibm __ieee754_rem_pio2 (MSL e_rem_pio2.c).
 * Returns x rem pi/2 in y[0]+y[1] and the quadrant count n. */

extern int __kernel_rem_pio2(double *x, double *y, int e0, int nx, int prec, const int *ipio2); /* __kernel_rem_pio2 */

extern const int two_over_pi[]; /* two_over_pi */
extern const int npio2_hw[]; /* npio2_hw */


#define __HI(x) *(int *)&x
#define __LO(x) *(1 + (int *)&x)

extern const double lbl_8064FC78; /* 0.0 */
extern const double lbl_8064FC80; /* pio2_1 */
extern const double lbl_8064FC88; /* pio2_1t */
extern const double lbl_8064FC90; /* pio2_2 */
extern const double lbl_8064FC98; /* pio2_2t */
extern const double lbl_8064FCA0; /* 0.5 */
extern const double lbl_8064FCA8; /* invpio2 */
extern const double lbl_8064FCB0; /* pio2_3 */
extern const double lbl_8064FCB8; /* pio2_3t */

#define zero lbl_8064FC78
#define pio2_1 lbl_8064FC80
#define pio2_1t lbl_8064FC88
#define pio2_2 lbl_8064FC90
#define pio2_2t lbl_8064FC98
#define half lbl_8064FCA0
#define invpio2 lbl_8064FCA8
#define pio2_3 lbl_8064FCB0
#define pio2_3t lbl_8064FCB8

int __ieee754_rem_pio2(double x, double *y)
{
    double z, t, w, r, fn;
    double tx[3];
    int e0, i, j, nx, n, ix, hx;

    hx = __HI(x);
    ix = hx & 0x7fffffff;
    if (ix <= 0x3fe921fb) {
        y[0] = x;
        y[1] = zero;
        return 0;
    }
    if (ix < 0x4002d97c) {
        if (hx > 0) {
            z = x - pio2_1;
            if (ix != 0x3ff921fb) {
                y[0] = z - pio2_1t;
                y[1] = (z - y[0]) - pio2_1t;
            } else {
                z -= pio2_2;
                y[0] = z - pio2_2t;
                y[1] = (z - y[0]) - pio2_2t;
            }
            return 1;
        } else {
            z = pio2_1 + x;
            if (ix != 0x3ff921fb) {
                y[0] = pio2_1t + z;
                y[1] = pio2_1t + (z - y[0]);
            } else {
                z += pio2_2;
                y[0] = pio2_2t + z;
                y[1] = pio2_2t + (z - y[0]);
            }
            return -1;
        }
    }
    if (ix <= 0x413921fb) {
        t = __fabs(x);
        n = (int)(invpio2 * t + half);
        fn = (double)n;
        r = t - pio2_1 * fn;
        w = pio2_1t * fn;
        if (n < 32 && ix != npio2_hw[n - 1]) {
            y[0] = r - w;
        } else {
            j = ix >> 20;
            y[0] = r - w;
            i = j - ((__HI(y[0]) >> 20) & 0x7ff);
            if (i > 16) {
                double w1, t1;
                t1 = r;
                w1 = pio2_2 * fn;
                r = t1 - w1;
                w = pio2_2t * fn - ((t1 - r) - w1);
                y[0] = r - w;
                i = j - ((__HI(y[0]) >> 20) & 0x7ff);
                if (i > 49) {
                    t = r;
                    w = pio2_3 * fn;
                    r = t - w;
                    w = pio2_3t * fn - ((t - r) - w);
                    y[0] = r - w;
                }
            }
        }
        y[1] = (r - y[0]) - w;
        if (hx < 0) {
            y[0] = -y[0];
            y[1] = -y[1];
            return -n;
        } else {
            return n;
        }
    }
    if (ix >= 0x7ff00000) {
        y[0] = y[1] = x - x;
        return 0;
    }
    __LO(z) = __LO(x);
    e0 = (ix >> 20) - 1046;
    __HI(z) = ix - (e0 << 20);
    for (i = 0; i < 2; i++) {
        tx[i] = (double)((int)(z));
        z = 16777216.0 * (z - tx[i]); /* two24 */
    }
    tx[2] = z;
    nx = 3;
    while (tx[nx - 1] == 0.0) nx--;
    n = __kernel_rem_pio2(tx, y, e0, nx, 2, two_over_pi);
    if (hx < 0) {
        y[0] = -y[0];
        y[1] = -y[1];
        return -n;
    }
    return n;
}
