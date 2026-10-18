typedef union DoubleBits {
    double value;
    struct {
        unsigned long high;
        unsigned long low;
    } words;
} DoubleBits;

extern const volatile double TWO52[2];

/* Round to an integer in the current floating-point rounding mode. */
double rint(double value)
{
    DoubleBits rounded;
    DoubleBits bits;
    int high;
    int exponent;
    int sign;
    unsigned int mask;
    unsigned int low;
    double bias;

    bits.value = value;
    high = bits.words.high;
    low = bits.words.low;
    sign = (high >> 31) & 1;
    exponent = ((high >> 20) & 0x7FF) - 0x3FF;
    if (exponent < 20) {
        if (exponent < 0) {
            if (((high & 0x7FFFFFFF) | low) == 0)
                return value;
            low |= high & 0xFFFFF;
            high &= ~0x1FFFF;
            high |= ((low | -low) >> 12) & 0x80000;
            bits.words.high = high;
            bias = TWO52[sign];
            rounded.value = (bits.value + bias) - bias;
            rounded.words.high = (rounded.words.high & 0x7FFFFFFF) | (sign << 31);
            return rounded.value;
        }
        mask = 0xFFFFF >> exponent;
        if (((high & mask) | low) == 0)
            return value;
        mask >>= 1;
        if (((high & mask) | low) != 0) {
            if (exponent == 19)
                low = 0x40000000;
            else
                high = (high & ~mask) | (0x20000 >> exponent);
        }
    } else if (exponent > 51) {
        if (exponent == 0x400)
            return value + value;
        return value;
    } else {
        mask = 0xFFFFFFFF >> (exponent - 20);
        if ((low & mask) == 0)
            return value;
        mask >>= 1;
        if ((low & mask) != 0)
            low = (low & ~mask) | (0x40000000 >> (exponent - 20));
    }
    bits.words.high = high;
    bits.words.low = low;
    bias = TWO52[sign];
    return (bits.value + bias) - bias;
}
