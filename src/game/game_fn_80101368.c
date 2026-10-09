typedef unsigned int u32;
typedef int s32;

extern const double lbl_8064FD58;
extern const double lbl_8064FD60;
extern const double lbl_8064FD68;
extern const double lbl_8064FD70;
extern const double lbl_8064FD78;
extern const double lbl_8064FD80;
extern const double lbl_8064FD88;

double fn_80101368(double x, double y, int tail)
{
    double z;
    double r;
    double w;
    s32 ix;

    ix = *(u32 *)&x & 0x7fffffff;
    if (ix < 0x3e400000 && (int)x == 0) {
        return x;
    }

    z = x * x;
    w = z * x;
    r = lbl_8064FD78 * z + lbl_8064FD70;
    r = z * r + lbl_8064FD68;
    r = z * r + lbl_8064FD60;
    r = z * r + lbl_8064FD58;

    if (tail == 0) {
        return x + w * (z * r + lbl_8064FD80);
    }
    return x - (z * (lbl_8064FD88 * y - w * r) - y - lbl_8064FD80 * w);
}
