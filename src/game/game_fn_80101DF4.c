typedef union DoubleBits {
    double value;
    struct {
        unsigned long high;
        unsigned long low;
    } words;
} DoubleBits;

double modf(double value, double *integral)
{
    DoubleBits bits;
    DoubleBits *integer;
    unsigned long high;
    unsigned long low;
    unsigned long mask;
    int exponent;

    bits.value = value;
    integer = (DoubleBits *)integral;
    high = bits.words.high;
    low = bits.words.low;
    exponent = ((high >> 20) & 0x7FF) - 0x3FF;
    if (exponent < 20) {
        if (exponent < 0) {
            integer->words.high = high & 0x80000000;
            integer->words.low = 0;
            return value;
        }
        mask = 0xFFFFF >> exponent;
        if (((high & mask) | low) == 0) {
            bits.words.high = high & 0x80000000;
            bits.words.low = 0;
            *integral = value;
            return bits.value;
        }
        integer->words.high = high & ~mask;
        integer->words.low = 0;
        return value - *integral;
    }
    if (exponent > 51) {
        bits.words.high = high & 0x80000000;
        bits.words.low = 0;
        *integral = value;
        return bits.value;
    }
    mask = 0xFFFFFFFF >> (exponent - 20);
    if ((low & mask) == 0) {
        bits.words.high = high & 0x80000000;
        bits.words.low = 0;
        *integral = value;
        return bits.value;
    }
    integer->words.high = high;
    integer->words.low = low & ~mask;
    return value - *integral;
}
