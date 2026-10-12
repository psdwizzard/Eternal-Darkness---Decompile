/* Round toward negative infinity using the IEEE-754 representation. */
extern const double lbl_8064FE08;
extern const double lbl_8064FE10;

double fn_80101A5C(double x)
{
    int high;
    unsigned int low;
    int exponent;
    unsigned int mask, rounded;

    high = ((int *)&x)[0];
    low = ((unsigned int *)&x)[1];
    exponent = ((high >> 20) & 0x7ff) - 0x3ff;
    if (exponent < 20) {
        if (exponent < 0) {
            if (lbl_8064FE08 + x > lbl_8064FE10) {
                if (high >= 0) {
                    high = low = 0;
                } else if (((high & 0x7fffffff) | low) != 0) {
                    high = 0xbff00000;
                    low = 0;
                }
            }
        } else {
            mask = 0x000fffff >> exponent;
            if (((high & mask) | low) == 0) {
                return x;
            }
            if (lbl_8064FE08 + x > lbl_8064FE10) {
                if (high < 0) {
                    high += 0x00100000 >> exponent;
                }
                high &= ~mask;
                low = 0;
            }
        }
    } else if (exponent > 51) {
        if (exponent == 1024) {
            return x + x;
        }
        return x;
    } else {
        mask = 0xffffffffU >> (exponent - 20);
        if ((low & mask) == 0) {
            return x;
        }
        if (lbl_8064FE08 + x > lbl_8064FE10) {
            if (high < 0) {
                if (exponent == 20) {
                    high += 1;
                } else {
                    rounded = low + (1U << (52 - exponent));
                    if (rounded < low) {
                        high += 1;
                    }
                    low = rounded;
                }
            }
            low &= ~mask;
        }
    }
    ((int *)&x)[0] = high;
    ((unsigned int *)&x)[1] = low;
    return x;
}
