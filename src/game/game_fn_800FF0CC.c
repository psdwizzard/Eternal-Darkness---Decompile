/* fn_800FF0CC: fdlibm __ieee754_atan2 (MSL e_atan2.c). */

#define __HI(x) *(int *)&x
#define __LO(x) *(1 + (int *)&x)

extern const double lbl_8064FA18; /* pi + tiny */
extern const double lbl_8064FA20; /* -pi - tiny */
extern const double lbl_8064FA28; /* -pi_o_2 - tiny */
extern const double lbl_8064FA30; /* pi_o_2 + tiny */
extern const double lbl_8064FA38; /* pi_o_4 + tiny */
extern const double lbl_8064FA40; /* -pi_o_4 - tiny */
extern const double lbl_8064FA48; /* 3.0 * pi_o_4 + tiny */
extern const double lbl_8064FA50; /* -3.0 * pi_o_4 - tiny */
extern const double lbl_8064FA58; /* 0.0 */
extern const double lbl_8064FA60; /* -0.0 */
extern const double lbl_8064FA68; /* pi_lo */

#define pi lbl_8064FA18
#define pi_lo lbl_8064FA68

/* atan */
extern double fn_8010161C(double x);

double fn_800FF0CC(double y, double x) {
    double z;
    int k, m, hx, hy, ix, iy;
    unsigned int lx, ly;

    hx = __HI(x);
    ix = hx & 0x7fffffff;
    lx = __LO(x);
    hy = __HI(y);
    iy = hy & 0x7fffffff;
    ly = __LO(y);
    if (((ix | ((lx | -lx) >> 31)) > 0x7ff00000) ||
        ((iy | ((ly | -ly) >> 31)) > 0x7ff00000)) {
        return x + y;
    }
    if ((hx - 0x3ff00000 | lx) == 0) {
        return fn_8010161C(y);
    }
    m = ((hy >> 31) & 1) | ((hx >> 30) & 2);

    if ((iy | ly) == 0) {
        switch (m) {
        case 0:
        case 1:
            return y;
        case 2:
            return lbl_8064FA18;
        case 3:
            return lbl_8064FA20;
        }
    }
    if ((ix | lx) == 0) {
        return (hy < 0) ? lbl_8064FA28 : lbl_8064FA30;
    }

    if (ix == 0x7ff00000) {
        if (iy == 0x7ff00000) {
            switch (m) {
            case 0:
                return lbl_8064FA38;
            case 1:
                return lbl_8064FA40;
            case 2:
                return lbl_8064FA48;
            case 3:
                return lbl_8064FA50;
            }
        } else {
            switch (m) {
            case 0:
                return lbl_8064FA58;
            case 1:
                return lbl_8064FA60;
            case 2:
                return lbl_8064FA18;
            case 3:
                return lbl_8064FA20;
            }
        }
    }
    if (iy == 0x7ff00000) {
        return (hy < 0) ? lbl_8064FA28 : lbl_8064FA30;
    }

    k = (iy - ix) >> 20;
    if (k > 60) {
        z = lbl_8064FA30;
    } else if (hx < 0 && k < -60) {
        z = lbl_8064FA58;
    } else {
        z = fn_8010161C(__fabs(y / x));
    }
    switch (m) {
    case 0:
        return z;
    case 1:
        __HI(z) ^= 0x80000000;
        return z;
    case 2:
        return pi - (z - pi_lo);
    default:
        return (z - pi_lo) - pi;
    }
}
