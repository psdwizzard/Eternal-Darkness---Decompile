/* fn_800FF578: fdlibm __ieee754_log (MSL e_log.c). */

#define __HI(x) *(int *)&x
#define __LO(x) *(1 + (int *)&x)

extern int lbl_8064CC50;           /* errno */
extern double lbl_8064CC60;        /* zero */
extern const double lbl_8064FAE8; /* -two54 */
extern const double lbl_8064FAF0; /* two54 */
extern const double lbl_8064FAF8; /* 1.0 */
extern const double lbl_8064FB00; /* ln2_hi */
extern const double lbl_8064FB08; /* ln2_lo */
extern const double lbl_8064FB10; /* 0.5 */
extern const double lbl_8064FB18; /* 1/3 */
extern const double lbl_8064FB20; /* 2.0 */
extern const double lbl_8064FB28; /* Lg1 */
extern const double lbl_8064FB30; /* Lg3 */
extern const double lbl_8064FB38; /* Lg5 */
extern const double lbl_8064FB40; /* Lg7 */
extern const double lbl_8064FB48; /* Lg2 */
extern const double lbl_8064FB50; /* Lg4 */
extern const double lbl_8064FB58; /* Lg6 */

#define zero lbl_8064CC60
#define two54 lbl_8064FAF0
#define ln2_hi lbl_8064FB00
#define ln2_lo lbl_8064FB08
#define Lg1 lbl_8064FB28
#define Lg2 lbl_8064FB48
#define Lg3 lbl_8064FB30
#define Lg4 lbl_8064FB50
#define Lg5 lbl_8064FB38
#define Lg6 lbl_8064FB58
#define Lg7 lbl_8064FB40

double fn_800FF578(double x) {
    double hfsq, f, s, z, R, w, t1, t2, dk;
    int k, hx, i, j;
    unsigned int lx;

    hx = __HI(x);
    lx = __LO(x);
    k = 0;
    if (hx < 0x00100000) {
        if (((hx & 0x7fffffff) | lx) == 0) {
            return lbl_8064FAE8 / zero;
        }
        if (hx < 0) {
            lbl_8064CC50 = 33;
            return (x - x) / zero;
        }
        k -= 54;
        x *= two54;
        hx = __HI(x);
    }
    if (hx >= 0x7ff00000) {
        return x + x;
    }
    k += (hx >> 20) - 1023;
    hx &= 0x000fffff;
    i = (hx + 0x95f64) & 0x100000;
    __HI(x) = hx | (i ^ 0x3ff00000);
    k += (i >> 20);
    f = x - lbl_8064FAF8;
    if ((0x000fffff & (2 + hx)) < 3) {
        if (f == zero) {
            if (k == 0) {
                return zero;
            } else {
                dk = (double)k;
                return ln2_hi * dk + ln2_lo * dk;
            }
        }
        R = (lbl_8064FB10 - lbl_8064FB18 * f) * (f * f);
        if (k == 0) {
            return f - R;
        } else {
            dk = (double)k;
            return ln2_hi * dk - ((R - ln2_lo * dk) - f);
        }
    }
    s = f / (lbl_8064FB20 + f);
    dk = (double)k;
    z = s * s;
    i = hx - 0x6147a;
    w = z * z;
    j = 0x6b851 - hx;
    t1 = w * (Lg2 + w * (Lg4 + Lg6 * w));
    t2 = z * (Lg1 + w * (Lg3 + w * (Lg5 + Lg7 * w)));
    i |= j;
    R = t2 + t1;
    if (i > 0) {
        hfsq = 0.5 * f * f;
        if (k == 0) {
            return f - (hfsq - s * (hfsq + R));
        } else {
            return ln2_hi * dk - ((hfsq - (s * (hfsq + R) + ln2_lo * dk)) - f);
        }
    } else {
        if (k == 0) {
            return f - s * (f - R);
        } else {
            return ln2_hi * dk - ((s * (f - R) - ln2_lo * dk) - f);
        }
    }
}
