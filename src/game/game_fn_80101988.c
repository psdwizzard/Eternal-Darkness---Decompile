/* Cosine, with argument reduction into a quadrant and kernel evaluation. */
extern int __ieee754_rem_pio2(double x, double *y);
extern double __kernel_cos(double x, double y);
extern double __kernel_sin(double x, double y, int tail);
extern const double lbl_8064FE00;

double cos(double x)
{
    double y[2];
    int quadrant;
    int magnitude;

    magnitude = *(unsigned int *)&x & 0x7fffffff;
    if (magnitude <= 0x3fe921fb) {
        return __kernel_cos(x, lbl_8064FE00);
    }
    if (magnitude >= 0x7ff00000) {
        return x - x;
    }
    quadrant = __ieee754_rem_pio2(x, y);
    switch (quadrant & 3) {
    case 0:
        return __kernel_cos(y[0], y[1]);
    case 1:
        return -__kernel_sin(y[0], y[1], 1);
    case 2:
        return -__kernel_cos(y[0], y[1]);
    default:
        return __kernel_sin(y[0], y[1], 1);
    }
}
