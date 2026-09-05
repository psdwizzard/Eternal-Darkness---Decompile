extern int fn_800F8CF0(int);
extern int fn_800F8D14(int);
extern int fn_800F8D2C(int);
extern const double lbl_8023A900[17];

#pragma use_lmw_stmw on
#pragma opt_lifetimes off
double fn_8016BA4C(signed char* text, signed char** end)
{
    int sign;
    double value;
    int exponent;
    const double* limit;
    int exponent_char;
    int digit;
    int exponent_sign;
    const double* scale;
    double factor;

    while (fn_800F8D14(*text)) {
        text++;
    }

    sign = 1;
    if (*text == '+') {
        text++;
    } else if (*text == '-') {
        sign = -1;
        text++;
    }

    value = 0.0;

    while (fn_800F8D2C(digit = *text)) {
        value = 10.0 * value + (digit - '0');
        text++;
    }

    if (*text == '.') {
        scale = lbl_8023A900;
        limit = lbl_8023A900 + 17;
        factor = *scale;

        text++;
        while (fn_800F8D2C(digit = *text) && scale < limit) {
            value = factor * (digit - '0') + value;
            factor = *++scale;
            text++;
        }
    }

    while (fn_800F8D2C(*text)) {
        text++;
    }

    if (fn_800F8CF0(*text) == 'e') {
        text++;
        exponent_char = *text;
        exponent_sign = 1;
        if (!fn_800F8D2C(exponent_char)) {
            if (exponent_char == '-') {
                exponent_sign = -1;
            }
            text++;
        }

        exponent = 0;
        while (fn_800F8D2C(exponent_char = *text)) {
            exponent = exponent_char + exponent * 10;
            exponent -= '0';
            text++;
        }
        if (exponent_sign == -1) {
            exponent = exponent - exponent * 2;
        }

        while (exponent < 0) {
            value /= 10.0;
            exponent++;
        }
        while (exponent > 0) {
            value = 10.0 * value;
            exponent--;
        }
    }

    if (end != 0) {
        *end = text;
    }
    return value * sign;
}
#pragma opt_lifetimes reset
#pragma use_lmw_stmw reset
