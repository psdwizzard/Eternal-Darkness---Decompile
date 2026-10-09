typedef union DoubleBits {
    double value;
    struct {
        unsigned long high;
        unsigned long low;
    } words;
} DoubleBits;

extern const double lbl_8064FE18;

double fn_80101BA4(double value, int *exponent)
{
    DoubleBits bits;
    int high;
    int magnitude;
    int low;

    bits.value = value;
    high = bits.words.high;
    magnitude = high & 0x7FFFFFFF;
    low = bits.words.low;
    *exponent = 0;
    if (magnitude >= 0x7FF00000 || (magnitude | low) == 0) {
        return bits.value;
    }
    if (magnitude < 0x00100000) {
        bits.value *= lbl_8064FE18;
        high = bits.words.high;
        magnitude = high & 0x7FFFFFFF;
        *exponent = -54;
    }
    *exponent += (magnitude >> 20) - 0x3FE;
    bits.words.high = (high & 0x800FFFFF) | 0x3FE00000;
    return bits.value;
}
