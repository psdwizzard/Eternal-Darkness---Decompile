/* fn_800FEDBC: fdlibm __ieee754_acos (MSL e_acos.c), with MSL's inline
 * frsqrte-based sqrt expanded in place. */

#define __HI(x) *(int *)&x
#define __LO(x) *(1 + (int *)&x)

/* __float_nan, __float_huge */
extern long lbl_8064B850[];
extern long lbl_8064B854[];

extern const double lbl_8064F988; /* 0.0 */
extern const double lbl_8064F990; /* pi */
extern const double lbl_8064F998; /* pio2_hi */
extern const double lbl_8064F9A0; /* pio2_lo */
extern const double lbl_8064F9A8; /* pS0 */
extern const double lbl_8064F9B0; /* pS1 */
extern const double lbl_8064F9B8; /* pS2 */
extern const double lbl_8064F9C0; /* pS3 */
extern const double lbl_8064F9C8; /* pS4 */
extern const double lbl_8064F9D0; /* pS5 */
extern const double lbl_8064F9D8; /* one */
extern const double lbl_8064F9E0; /* qS1 */
extern const double lbl_8064F9E8; /* qS2 */
extern const double lbl_8064F9F0; /* qS3 */
extern const double lbl_8064F9F8; /* qS4 */
extern const double lbl_8064FA00; /* 0.5 */
extern const double lbl_8064FA08; /* 3.0 */
extern const double lbl_8064FA10; /* 2.0 */

#define zero 0.0
#define pi lbl_8064F990
#define pio2_hi lbl_8064F998
#define pio2_lo lbl_8064F9A0
#define pS0 lbl_8064F9A8
#define pS1 lbl_8064F9B0
#define pS2 lbl_8064F9B8
#define pS3 lbl_8064F9C0
#define pS4 lbl_8064F9C8
#define pS5 lbl_8064F9D0
#define one lbl_8064F9D8
#define qS1 lbl_8064F9E0
#define qS2 lbl_8064F9E8
#define qS3 lbl_8064F9F0
#define qS4 lbl_8064F9F8
#define half 0.5
#define three 3.0
#define two lbl_8064FA10

#define NAN (*(float *)lbl_8064B850)
#define INFINITY (*(float *)lbl_8064B854)

static inline double sqrt(double x)
{
    if (x > zero) {
        double guess = __frsqrte(x);
        guess = half * guess * (three - guess * guess * x);
        guess = half * guess * (three - guess * guess * x);
        guess = half * guess * (three - guess * guess * x);
        guess = half * guess * (three - guess * guess * x);
        return x * guess;
    } else if (x == 0) {
        return 0;
    } else if (x) {
        return NAN;
    }
    return INFINITY;
}

double fn_800FEDBC(double x)
{
    double z, p, q, r, w, s, c, df;
    int hx, ix;

    hx = __HI(x);
    ix = hx & 0x7fffffff;
    if (ix >= 0x3ff00000) {
        if (((ix - 0x3ff00000) | __LO(x)) == 0) {
            if (hx > 0) {
                return lbl_8064F988;
            } else {
                return pi; /* pi + 2.0 * pio2_lo, folded */
            }
        }
        return NAN; /* (x - x) / (x - x) */
    }
    if (ix < 0x3fe00000) {
        if (ix <= 0x3c600000) {
            return pio2_hi; /* pio2_hi + pio2_lo, folded */
        }
        z = x * x;
        p = z * (pS0 + z * (pS1 + z * (pS2 + z * (pS3 + z * (pS4 + pS5 * z)))));
        q = one + z * (qS1 + z * (qS2 + z * (qS3 + qS4 * z)));
        r = p / q;
        return pio2_hi - (x - (pio2_lo - x * r));
    } else if (hx < 0) {
        z = (1.0 + x) * half;
        p = z * (pS0 + z * (pS1 + z * (pS2 + z * (pS3 + z * (pS4 + pS5 * z)))));
        q = 1.0 + z * (qS1 + z * (qS2 + z * (qS3 + qS4 * z)));
        s = sqrt(z);
        r = p / q;
        w = r * s - pio2_lo;
        return pi - two * (s + w);
    } else {
        z = half * (one - x);
        s = sqrt(z);
        df = s;
        __LO(df) = 0;
        c = (z - df * df) / (s + df);
        p = z * (pS0 + z * (pS1 + z * (pS2 + z * (pS3 + z * (pS4 + pS5 * z)))));
        q = one + z * (qS1 + z * (qS2 + z * (qS3 + qS4 * z)));
        r = p / q;
        w = r * s + c;
        return two * (df + w);
    }
}
