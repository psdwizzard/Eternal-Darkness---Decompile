typedef union DoubleBits {
    double value;
    struct {
        unsigned long high;
        unsigned long low;
    } words;
} DoubleBits;

extern const double lbl_8064FDF0; /* huge */
extern const double lbl_8064FDF8; /* zero */

/* Round upward to an integral value, retaining the sign of zero. */
double ceil(double value)
{
    DoubleBits bits;
    int high;
    unsigned int low;
    int exponent;
    unsigned int mask;
    unsigned int rounded;

    bits.value = value;
    high = bits.words.high;
    low = bits.words.low;
    exponent = ((high >> 20) & 0x7FF) - 0x3FF;
    if (exponent < 20) {
        if (exponent < 0) {
            if (lbl_8064FDF0 + value > lbl_8064FDF8) {
                if (high < 0) {
                    high = 0x80000000;
                    low = 0;
                } else if ((high | low) != 0) {
                    high = 0x3FF00000;
                    low = 0;
                }
            }
        } else {
            mask = 0xFFFFF >> exponent;
            if (((high & mask) | low) == 0)
                return value;
            if (lbl_8064FDF0 + value > lbl_8064FDF8) {
                if (high > 0)
                    high += 0x100000 >> exponent;
                high &= ~mask;
                low = 0;
            }
        }
    } else if (exponent > 51) {
        if (exponent == 0x400)
            return value + value;
        return value;
    } else {
        mask = 0xFFFFFFFF >> (exponent - 20);
        if ((low & mask) == 0)
            return value;
        if (lbl_8064FDF0 + value > lbl_8064FDF8) {
            if (high > 0) {
                if (exponent == 20)
                    high += 1;
                else {
                    rounded = low + (1 << (52 - exponent));
                    if (rounded < low)
                        high += 1;
                    low = rounded;
                }
            }
            low &= ~mask;
        }
    }
    bits.words.high = high;
    bits.words.low = low;
    return bits.value;
}
