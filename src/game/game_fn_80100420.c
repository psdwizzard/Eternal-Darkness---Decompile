typedef unsigned int u32;

extern const double lbl_8064FCD0;
extern const double lbl_8064FCD8;
extern const double lbl_8064FCE0;
extern const double lbl_8064FCE8;
extern const double lbl_8064FCF0;
extern const double lbl_8064FCF8;
extern const double lbl_8064FD00;
extern const double lbl_8064FD08;
extern const double lbl_8064FD10;

double __kernel_cos(double x, double y)
{
    double a, hz, z, r, qx;
    int ix;

    ix = *(u32 *)&x & 0x7fffffff;
    if (ix < 0x3e400000) {
        if ((int)x == 0) {
            return lbl_8064FCD0;
        }
    }
    z = x * x;
    r = z * (lbl_8064FCD8 + z * (lbl_8064FCE0 + z *
        (lbl_8064FCE8 + z * (lbl_8064FCF0 + z *
        (lbl_8064FCF8 + lbl_8064FD00 * z)))));
    if (ix < 0x3fd33333) {
        return lbl_8064FCD0 - (lbl_8064FD08 * z - (z * r - x * y));
    }
    if (ix > 0x3fe90000) {
        qx = lbl_8064FD10;
    } else {
        ((u32 *)&qx)[0] = ix - 0x00200000;
        ((u32 *)&qx)[1] = 0;
    }
    hz = lbl_8064FD08 * z - qx;
    a = lbl_8064FCD0 - qx;
    return a - (hz - (z * r - x * y));
}
