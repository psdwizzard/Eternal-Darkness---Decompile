typedef unsigned int u32;

extern int __ieee754_rem_pio2(double x, double *y);
extern double __kernel_cos(double x, double y);
extern double __kernel_sin(double x, double y, int tail);
extern const double lbl_8064FE48;

double sin(double x)
{
    double y[2];
    int n;
    int ix;

    ix = *(u32 *)&x & 0x7fffffff;
    if (ix <= 0x3fe921fb) {
        return __kernel_sin(x, lbl_8064FE48, 0);
    }
    if (ix >= 0x7ff00000) {
        return x - x;
    }
    n = __ieee754_rem_pio2(x, y);
    switch (n & 3) {
    case 0:
        return __kernel_sin(y[0], y[1], 1);
    case 1:
        return __kernel_cos(y[0], y[1]);
    case 2:
        return -__kernel_sin(y[0], y[1], 1);
    default:
        return -__kernel_cos(y[0], y[1]);
    }
}
