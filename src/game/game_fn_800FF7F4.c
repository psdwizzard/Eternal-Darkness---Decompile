/* __ieee754_pow: fdlibm __ieee754_pow (MSL e_pow.c). */

#define __HI(x) *(int *)&x
#define __LO(x) *(1 + (int *)&x)

extern double ldexp(double x, int n); /* scalbn */

extern int errno;     /* errno */
extern int __float_nan[];   /* __float_nan */
extern int __float_huge[];   /* __float_huge */

#define NAN (*(float *)__float_nan)
#define INFINITY (*(float *)__float_huge)

typedef struct PowTable {
    double bp[2];
    double dp_h[2];
    double dp_l[2];
} PowTable;

extern const PowTable lbl_80239EF0;

extern const double lbl_8064FB68; /* one */
extern const double lbl_8064FB70; /* zero */
extern const double lbl_8064FB78; /* 0.5 */
extern const double lbl_8064FB80; /* 3.0 */
extern const double lbl_8064FB88; /* huge*huge */
extern const double lbl_8064FB90; /* 1/3 */
extern const double lbl_8064FB98; /* 0.25 */
extern const double lbl_8064FBA0; /* ivln2_h */
extern const double lbl_8064FBA8; /* ivln2_l */
extern const double lbl_8064FBB0; /* ivln2 */
extern const double lbl_8064FBB8; /* two53 */
extern const double lbl_8064FBC0; /* L1 */
extern const double lbl_8064FBC8; /* L2 */
extern const double lbl_8064FBD0; /* L3 */
extern const double lbl_8064FBD8; /* L4 */
extern const double lbl_8064FBE0; /* L5 */
extern const double lbl_8064FBE8; /* L6 */
extern const double lbl_8064FBF0; /* cp_h */
extern const double lbl_8064FBF8; /* cp_l */
extern const double lbl_8064FC00; /* cp */
extern const double lbl_8064FC08; /* -one */
extern const double lbl_8064FC10; /* huge */
extern const double lbl_8064FC18; /* ovt */
extern const double lbl_8064FC20; /* tiny */
extern const double lbl_8064FC28; /* lg2_h */
extern const double lbl_8064FC30; /* lg2 */
extern const double lbl_8064FC38; /* lg2_l */
extern const double lbl_8064FC40; /* P1 */
extern const double lbl_8064FC48; /* P2 */
extern const double lbl_8064FC50; /* P3 */
extern const double lbl_8064FC58; /* P4 */
extern const double lbl_8064FC60; /* P5 */
extern const double lbl_8064FC68; /* two */

#define bp (tbl->bp)
#define dp_h (tbl->dp_h)
#define dp_l (tbl->dp_l)
#define one lbl_8064FB68
#define zero lbl_8064FB70
#define two53 lbl_8064FBB8
#define huge lbl_8064FC10
#define tiny lbl_8064FC20
#define L1 lbl_8064FBC0
#define L2 lbl_8064FBC8
#define L3 lbl_8064FBD0
#define L4 lbl_8064FBD8
#define L5 lbl_8064FBE0
#define L6 lbl_8064FBE8
#define P1 lbl_8064FC40
#define P2 lbl_8064FC48
#define P3 lbl_8064FC50
#define P4 lbl_8064FC58
#define P5 lbl_8064FC60
#define lg2 lbl_8064FC30
#define lg2_h lbl_8064FC28
#define lg2_l lbl_8064FC38
#define ovt lbl_8064FC18
#define cp lbl_8064FC00
#define cp_h lbl_8064FBF0
#define cp_l lbl_8064FBF8
#define ivln2 lbl_8064FBB0
#define ivln2_h lbl_8064FBA0
#define ivln2_l lbl_8064FBA8

/* MSL math.h inline sqrt */
static inline double sqrt_inline(double x) {
    if (x > 0.0) {
        double guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        return x * guess;
    } else if (x == 0.0) {
        return 0.0;
    } else if (x) {
        return NAN;
    }
    return INFINITY;
}

double __ieee754_pow(double x, double y) {
    double z, ax, z_h, z_l, p_h, p_l;
    double y1, t1, t2, r, s, t, u, v, w;
    int i, j, k, n, yisint;
    int hx, hy, ix, iy;
    unsigned lx, ly;
    const PowTable *tbl = &lbl_80239EF0;

    hx = __HI(x);
    lx = __LO(x);
    hy = __HI(y);
    ly = __LO(y);
    ix = hx & 0x7fffffff;
    iy = hy & 0x7fffffff;

    if ((iy | ly) == 0) {
        return one;
    }

    if (ix > 0x7ff00000 || ((ix == 0x7ff00000) && (lx != 0)) ||
        iy > 0x7ff00000 || ((iy == 0x7ff00000) && (ly != 0))) {
        return x + y;
    }

    yisint = 0;
    if (hx < 0) {
        if (iy >= 0x43400000) {
            yisint = 2;
        } else if (iy >= 0x3ff00000) {
            k = (iy >> 20) - 0x3ff;
            if (k > 20) {
                j = ly >> (52 - k);
                if ((j << (52 - k)) == ly) {
                    yisint = 2 - (j & 1);
                }
            } else if (ly == 0) {
                j = iy >> (20 - k);
                if ((j << (20 - k)) == iy) {
                    yisint = 2 - (j & 1);
                }
            }
        }
    }

    if (ly == 0) {
        if (iy == 0x7ff00000) {
            if (((ix - 0x3ff00000) | lx) == 0) {
                return y - y;
            } else if (ix >= 0x3ff00000) {
                return (hy >= 0) ? y : zero;
            } else {
                return (hy < 0) ? -y : zero;
            }
        }
        if (iy == 0x3ff00000) {
            if (hy < 0) {
                return one / x;
            } else {
                return x;
            }
        }
        if (hy == 0x40000000) {
            return x * x;
        }
        if (hy == 0x3fe00000) {
            if (hx >= 0) {
                return sqrt_inline(x);
            }
        }
    }

    u = __fabs(x);
    ax = u;
    if (lx == 0) {
        if (ix == 0x7ff00000 || ix == 0 || ix == 0x3ff00000) {
            z = u;
            if (hy < 0) {
                z = one / z;
            }
            if (hx < 0) {
                if (((ix - 0x3ff00000) | yisint) == 0) {
                    z = (z - z) / (z - z);
                } else if (yisint == 1) {
                    z = -z;
                }
            }
            return z;
        }
    }

    n = (hx >> 31) + 1;

    if ((n | yisint) == 0) {
        errno = 33;
        return NAN;
    }

    if (iy > 0x41e00000) {
        if (iy > 0x43f00000) {
            if (ix <= 0x3fefffff) {
                return (hy < 0) ? lbl_8064FB88 : zero;
            }
            if (ix >= 0x3ff00000) {
                return (hy > 0) ? lbl_8064FB88 : zero;
            }
        }
        if (ix < 0x3fefffff) {
            return (hy < 0) ? lbl_8064FB88 : zero;
        }
        if (ix > 0x3ff00000) {
            return (hy > 0) ? lbl_8064FB88 : zero;
        }
        t = x - one;
        w = (t * t) * (lbl_8064FB78 - t * (lbl_8064FB90 - lbl_8064FB98 * t));
        u = ivln2_h * t;
        v = ivln2_l * t - ivln2 * w;
        t1 = u + v;
        __LO(t1) = 0;
        t2 = v - (t1 - u);
    } else {
        double ss, s2, s_h, s_l, t_h, t_l;
        int m = 0;
        if (ix < 0x00100000) {
            ax *= two53;
            m -= 53;
            ix = __HI(ax);
        }
        m += ((ix) >> 20) - 0x3ff;
        j = ix & 0x000fffff;
        ix = j | 0x3ff00000;
        if (j <= 0x3988E) {
            k = 0;
        } else if (j < 0xBB67A) {
            k = 1;
        } else {
            k = 0;
            m += 1;
            ix -= 0x00100000;
        }
        __HI(ax) = ix;

        u = ax - bp[k];
        v = one / (ax + bp[k]);
        ss = u * v;
        s_h = ss;
        __LO(s_h) = 0;
        t_h = zero;
        __HI(t_h) = ((ix >> 1) | 0x20000000) + 0x00080000 + (k << 18);
        t_l = ax - (t_h - bp[k]);
        s_l = v * ((u - s_h * t_h) - s_h * t_l);
        s2 = ss * ss;
        r = s2 * s2 * (L1 + s2 * (L2 + s2 * (L3 + s2 * (L4 + s2 * (L5 + L6 * s2)))));
        r += s_l * (s_h + ss);
        s2 = s_h * s_h;
        t_h = 3.0 + s2 + r;
        __LO(t_h) = 0;
        t_l = r - ((t_h - 3.0) - s2);
        u = s_h * t_h;
        v = s_l * t_h + t_l * ss;
        p_h = u + v;
        __LO(p_h) = 0;
        p_l = v - (p_h - u);
        z_h = cp_h * p_h;
        z_l = cp_l * p_h + cp * p_l + dp_l[k];
        t = (double)m;
        t1 = (((z_h + z_l) + dp_h[k]) + t);
        __LO(t1) = 0;
        t2 = z_l - (((t1 - t) - dp_h[k]) - z_h);
    }

    s = one;
    if ((n | (yisint - 1)) == 0) {
        s = lbl_8064FC08;
    }

    y1 = y;
    __LO(y1) = 0;
    p_l = (y - y1) * t1 + y * t2;
    p_h = y1 * t1;
    z = p_l + p_h;
    j = __HI(z);
    i = __LO(z);
    if (j >= 0x40900000) {
        if (((j - 0x40900000) | i) != 0) {
            return huge * (huge * s);
        } else {
            if (ovt + p_l > z - p_h) {
                return huge * (huge * s);
            }
        }
    } else if ((j & 0x7fffffff) >= 0x4090cc00) {
        if (((j - 0xc090cc00) | i) != 0) {
            return tiny * (tiny * s);
        } else {
            if (p_l <= z - p_h) {
                return tiny * (tiny * s);
            }
        }
    }
    i = j & 0x7fffffff;
    k = (i >> 20) - 0x3ff;
    n = 0;
    if (i > 0x3fe00000) {
        n = j + (0x00100000 >> (k + 1));
        k = ((n & 0x7fffffff) >> 20) - 0x3ff;
        t = zero;
        __HI(t) = (n & ~(0x000fffff >> k));
        n = ((n & 0x000fffff) | 0x00100000) >> (20 - k);
        if (j < 0) {
            n = -n;
        }
        p_h -= t;
    }
    t = p_l + p_h;
    __LO(t) = 0;
    u = lg2_h * t;
    v = (p_l - (t - p_h)) * lg2 + lg2_l * t;
    z = u + v;
    w = v - (z - u);
    t = z * z;
    t1 = z - t * (P1 + t * (P2 + t * (P3 + t * (P4 + P5 * t))));
    r = (z * t1) / (t1 - lbl_8064FC68) - (w + z * w);
    z = one - (r - z);
    j = __HI(z);
    j += (n << 20);
    if ((j >> 20) <= 0) {
        z = ldexp(z, n);
    } else {
        __HI(z) += (n << 20);
    }
    return s * z;
}
