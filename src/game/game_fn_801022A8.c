extern int __ieee754_rem_pio2(double x, double *y);
extern double __kernel_tan(double x, double y, int iy);
extern const double lbl_8064FE50;

double tan(double x)
{
    double y[2];
    int n;
    int ix;

    ix = *(unsigned int *)&x & 0x7fffffff;
    if (ix <= 0x3fe921fb) {
        return __kernel_tan(x, lbl_8064FE50, 1);
    }
    if (ix >= 0x7ff00000) {
        return x - x;
    }
    n = __ieee754_rem_pio2(x, y);
    return __kernel_tan(y[0], y[1], 1 - ((n & 1) << 1));
}
