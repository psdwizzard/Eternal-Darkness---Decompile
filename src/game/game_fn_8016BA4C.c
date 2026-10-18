extern int tolower(int);
extern int isspace(int);
extern int isdigit(int);
extern const double lbl_8023A900[17];

#pragma use_lmw_stmw on
#pragma opt_lifetimes off
double strtod(signed char* text, signed char** end)
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

    while (isspace(*text)) {
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

    while (isdigit(digit = *text)) {
        value = 10.0 * value + (digit - '0');
        text++;
    }

    if (*text == '.') {
        scale = lbl_8023A900;
        limit = lbl_8023A900 + 17;
        factor = *scale;

        text++;
        while (isdigit(digit = *text) && scale < limit) {
            value = factor * (digit - '0') + value;
            factor = *++scale;
            text++;
        }
    }

    while (isdigit(*text)) {
        text++;
    }

    if (tolower(*text) == 'e') {
        text++;
        exponent_char = *text;
        exponent_sign = 1;
        if (!isdigit(exponent_char)) {
            if (exponent_char == '-') {
                exponent_sign = -1;
            }
            text++;
        }

        exponent = 0;
        while (isdigit(exponent_char = *text)) {
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
