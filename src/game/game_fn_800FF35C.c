/* fdlibm __ieee754_exp: reduce by ln(2), approximate, then scale. */
#define __HI(x) (*(int *)&(x))
#define __LO(x) (*((int *)&(x) + 1))

extern const volatile double lbl_80239EC0[6];
extern const double lbl_8064FA70; /* zero */
extern const double lbl_8064FA78; /* overflow threshold */
extern const double lbl_8064FA80; /* overflow result */
extern const double lbl_8064FA88; /* underflow threshold */
extern const double lbl_8064FA90; /* 1/ln(2) */
extern const double lbl_8064FA98; /* huge */
extern const double lbl_8064FAA0; /* one */
extern const double lbl_8064FAA8; /* P1 */
extern const double lbl_8064FAB0; /* P2 */
extern const double lbl_8064FAB8; /* P3 */
extern const double lbl_8064FAC0; /* P4 */
extern const double lbl_8064FAC8; /* P5 */
extern const double lbl_8064FAD0; /* two */
extern const double lbl_8064FAD8; /* 2^-1000 */

#define half (constants)
#define ln2HI (constants + 2)
#define ln2LO (constants + 4)

double fn_800FF35C(double x) {
    const double *constants = (const double *)lbl_80239EC0;
    double y, hi, lo, c, t;
    unsigned int hx;
    int k;
    int xsb;
    unsigned int high;

    high = __HI(x);
    hx = high & 0x7fffffff;
    xsb = high >> 31;
    if (hx >= 0x40862e42) {
        if (hx >= 0x7ff00000) {
            if (((high & 0xfffff) | __LO(x)) != 0)
                return x + x;
            return xsb == 0 ? x : lbl_8064FA70;
        }
        if (x > lbl_8064FA78) return lbl_8064FA80;
        if (x < lbl_8064FA88) return lbl_8064FA70;
    }
    if (hx > 0x3fd62e42) {
        if (hx < 0x3ff0a2b2) {
            hi = x - ln2HI[xsb];
            lo = ln2LO[xsb];
            k = 1 - xsb - xsb;
        } else {
            k = (int)(lbl_8064FA90 * x + half[xsb]);
            t = k;
            hi = x - t * ln2HI[0];
            lo = t * ln2LO[0];
        }
        x = hi - lo;
    } else if (hx < 0x3e300000) {
        double one = 1.0;
        if (lbl_8064FA98 + x > one) return one + x;
    } else {
        k = 0;
    }
    t = x * x;
    c = x - t * (lbl_8064FAA8 + t * (lbl_8064FAB0 + t *
        (lbl_8064FAB8 + t * (lbl_8064FAC0 + lbl_8064FAC8 * t))));
    if (k == 0) return lbl_8064FAA0 - ((x * c) / (c - lbl_8064FAD0) - x);
    y = lbl_8064FAA0 - ((lo - (x * c) / (lbl_8064FAD0 - c)) - hi);
    if (k >= -1021) {
        __HI(y) += k << 20;
        return y;
    } else {
        __HI(y) += (k + 1000) << 20;
        return lbl_8064FAD8 * y;
    }
}
