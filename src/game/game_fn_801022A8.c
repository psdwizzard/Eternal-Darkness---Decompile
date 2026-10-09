extern int fn_80100080(double x, double *y);
extern double fn_80101408(double x, double y, int iy);
extern const double lbl_8064FE50;

double fn_801022A8(double x)
{
    double y[2];
    int n;
    int ix;

    ix = *(unsigned int *)&x & 0x7fffffff;
    if (ix <= 0x3fe921fb) {
        return fn_80101408(x, lbl_8064FE50, 1);
    }
    if (ix >= 0x7ff00000) {
        return x - x;
    }
    n = fn_80100080(x, y);
    return fn_80101408(y[0], y[1], 1 - ((n & 1) << 1));
}
