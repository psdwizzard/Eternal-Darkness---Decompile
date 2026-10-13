extern double fn_801021D0(double x); /* sin */

extern float lbl_80651890;
extern float lbl_80651894;
extern float lbl_80651898;
extern float lbl_8065189C;
extern float lbl_806518A0;

float fn_8023633C(int disabled, int pos, int total, int fadeIn, int fadeOut) {
    float result = lbl_80651890;
    int quarter;
    int inStart;
    int outStart;
    float s;

    if (disabled != 0) {
        return result;
    }
    quarter = total / 4;
    inStart = quarter - fadeIn / 2;
    outStart = (total - quarter) - fadeOut / 2;

    if (pos >= inStart && pos < fadeIn + inStart) {
        s = fn_801021D0(lbl_80651894 * ((lbl_80651898 + (float)(pos - inStart)) / (float)fadeIn) * lbl_80651898);
        return fn_801021D0(s * s * lbl_8065189C);
    }
    if (pos >= outStart && pos < outStart + fadeOut) {
        s = fn_801021D0(lbl_80651894 * (((float)(fadeOut - (pos - outStart)) - lbl_80651898) / (float)fadeOut) * lbl_80651898);
        return fn_801021D0(s * s * lbl_8065189C);
    }
    if (pos >= inStart + fadeIn && pos < outStart) {
        result = lbl_806518A0;
    }
    return result;
}
