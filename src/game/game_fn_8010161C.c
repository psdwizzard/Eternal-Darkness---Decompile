/* fdlibm atan with argument reduction and an odd polynomial. */

#define __HI(x) *(int *)&x
#define __LO(x) *(1 + (int *)&x)

extern const volatile double atanhi[19];
extern const double lbl_8064FDC8; /* huge */
extern const double lbl_8064FDD0; /* one */
extern const double lbl_8064FDD8; /* 1.5 */
extern const double lbl_8064FDE0; /* 2.4375 */
extern const double lbl_8064FDE8; /* one */

double atan(double x) {
    double w, s1, s2, z, ax;
    int ix, hx, id;
    const double *aT = (const double *)atanhi;

    hx = __HI(x);
    ix = hx & 0x7fffffff;
    if (ix >= 0x44100000) {
        if (ix > 0x7ff00000 || (ix == 0x7ff00000 && __LO(x) != 0))
            return x + x;
        if (hx > 0)
            return aT[3] + aT[7];
        return -aT[3] - aT[7];
    }
    if (ix < 0x3fdc0000) {
        if (ix < 0x3e200000) {
            if (lbl_8064FDC8 + x > lbl_8064FDD0)
                return x;
        }
        id = -1;
    } else {
        ax = __fabs(x);
        x = ax;
        if (ix < 0x3ff30000) {
            if (ix < 0x3fe60000) {
                id = 0;
                x = (lbl_8064FDD8 * x - lbl_8064FDD0) / (lbl_8064FDD8 + x);
            } else {
                id = 1;
                x = (x - lbl_8064FDD0) / (lbl_8064FDD0 + x);
            }
        } else {
            if (ix < 0x40038000) {
                id = 2;
                x = (x - lbl_8064FDE0) / (lbl_8064FDE0 * x + lbl_8064FDD0);
            } else {
                id = 3;
                x = lbl_8064FDE8 / x;
            }
        }
    }
    z = x * x;
    w = z * z;
    s1 = z * (aT[8] + w * (aT[10] + w * (aT[12] + w * (aT[14] + w * (aT[16] + w * aT[18])))));
    s2 = w * (aT[9] + w * (aT[11] + w * (aT[13] + w * (aT[15] + w * aT[17]))));
    if (id < 0)
        return x - x * (s1 + s2);
    {
        const double *p = aT + id;
        double lo = p[4];
        double hi = p[0];
        z = hi - ((x * (s1 + s2) - lo) - x);
    }
    if (hx < 0)
        return -z;
    return z;
}
