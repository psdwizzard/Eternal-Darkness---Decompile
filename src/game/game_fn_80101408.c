typedef signed int s32;
typedef unsigned int u32;

extern const volatile double lbl_8023A0F8[13];
extern const double lbl_8064FD90;
extern const double lbl_8064FD98;
extern const double lbl_8064FDA0;
extern const double lbl_8064FDA8;
extern const double lbl_8064FDB0;
extern const double lbl_8064FDB8;

double fn_80101408(s32 arg0, double farg0, double farg1) {
    double sp18;
    double sp10;
    double sp8;
    double temp_f0;
    double temp_f13;
    double temp_f1;
    double temp_f31;
    double temp_f4;
    double temp_f6;
    double temp_f7;
    double var_f2;
    s32 temp_r6;
    s32 temp_r7;
    u32 unkspC;

    var_f2 = farg1;
    sp8 = farg0;
    temp_r7 = ((u32 *)&sp8)[0];
    temp_r6 = temp_r7 & 0x7fffffff;
    if ((temp_r6 < 0x3e300000) && ((s32)farg0 == 0)) {
        unkspC = ((u32 *)&sp8)[1];
        if (((arg0 + 1) | (temp_r6 | unkspC)) == 0)
            return lbl_8064FD90 / __fabs(farg0);
        if (arg0 == 1)
            return farg0;
        return lbl_8064FD98 / farg0;
    }
    if (temp_r6 >= 0x3fe59428) {
        if (temp_r7 < 0) {
            var_f2 = -var_f2;
            sp8 = -sp8;
        }
        temp_f0 = lbl_8064FDA8 - var_f2;
        var_f2 = lbl_8064FDB0;
        temp_f1 = lbl_8064FDA0 - sp8;
        sp18 = temp_f1;
        sp8 = temp_f1 + temp_f0;
    }
    temp_f13 = sp8 * sp8;
    temp_f31 = temp_f13 * temp_f13;
    temp_f1 = temp_f13 * sp8;
    sp18 = temp_f13;
    temp_f7 = temp_f31 * lbl_8023A0F8[12] + lbl_8023A0F8[10];
    temp_f7 = temp_f31 * temp_f7 + lbl_8023A0F8[8];
    temp_f7 = temp_f31 * temp_f7 + lbl_8023A0F8[6];
    temp_f7 = temp_f31 * temp_f7 + lbl_8023A0F8[4];
    temp_f4 = temp_f31 * temp_f7 + lbl_8023A0F8[2];
    temp_f4 = temp_f13 * temp_f4;
    temp_f7 = temp_f31 * lbl_8023A0F8[11] + lbl_8023A0F8[9];
    temp_f7 = temp_f31 * temp_f7 + lbl_8023A0F8[7];
    temp_f7 = temp_f31 * temp_f7 + lbl_8023A0F8[5];
    temp_f7 = temp_f31 * temp_f7 + lbl_8023A0F8[3];
    temp_f7 = temp_f31 * temp_f7 + lbl_8023A0F8[1];
    temp_f4 = temp_f7 + temp_f4;
    temp_f4 = temp_f1 * temp_f4 + var_f2;
    temp_f6 = temp_f13 * temp_f4 + var_f2;
    temp_f6 = lbl_8023A0F8[0] * temp_f1 + temp_f6;
    temp_f1 = sp8 + temp_f6;
    if (temp_r6 >= 0x3fe59428) {
        double temp;
        temp = (double)arg0;
        return (double)(1 - ((temp_r7 >> 30) & 2)) * -((lbl_8064FDB8 * (sp8 - (((temp_f1 * temp_f1) / (temp_f1 + temp)) - temp_f6))) - temp);
    }
    if (arg0 == 1)
        return temp_f1;
    sp18 = temp_f1;
    temp_f4 = lbl_8064FD98 / temp_f1;
    sp10 = temp_f4;
    ((u32 *)&sp18)[1] = 0;
    ((u32 *)&sp10)[1] = 0;
    temp_f0 = sp18 - sp8;
    temp_f0 = temp_f6 - temp_f0;
    temp_f1 = (sp10 * sp18) + lbl_8064FD90;
    temp_f0 = sp10 * temp_f0 + temp_f1;
    return temp_f4 * temp_f0 + sp10;
}
