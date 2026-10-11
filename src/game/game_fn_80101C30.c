typedef union DoubleBits {
    double value;
    struct {
        unsigned long high;
        unsigned long low;
    } words;
} DoubleBits;

extern const double lbl_8064FE20;
extern const double lbl_8064FE28;
extern const double lbl_8064FE30;
extern const double lbl_8064FE38;
extern const double lbl_8064FE40;
extern double fn_80101960(double magnitude, double sign);

static inline int classify(double value)
{
    int *words = (int *)&value;
    switch (words[0] & 0x7FF00000) {
    case 0x7FF00000:
        if ((words[0] & 0xFFFFF) || words[1])
            return 1;
        return 2;
    case 0:
        if ((words[0] & 0xFFFFF) || words[1])
            return 5;
        return 3;
    default:
        return 4;
    }
}

double fn_80101C30(double value, int n)
{
    DoubleBits *bits = (DoubleBits *)&value;
    int exponent;
    unsigned long high;
    unsigned long low;

    if (classify(value) <= 2 || lbl_8064FE20 == value)
        return value;

    high = bits->words.high;
    low = bits->words.low;
    exponent = (high >> 20) & 0x7FF;
    if (exponent == 0) {
        if ((low | (high & 0x7FFFFFFF)) == 0)
            return value;
        bits->value *= lbl_8064FE28;
        high = bits->words.high;
        exponent = ((high >> 20) & 0x7FF) - 54;
        if (n < -50000)
            return lbl_8064FE30 * bits->value;
    }
    if (exponent == 0x7FF)
        return bits->value + bits->value;
    exponent += n;
    if (exponent > 0x7FE)
        return lbl_8064FE38 * fn_80101960(lbl_8064FE38, bits->value);
    if (exponent > 0) {
        bits->words.high = (high & 0x800FFFFF) | (exponent << 20);
        return bits->value;
    }
    if (exponent <= -54) {
        if (n > 50000)
            return lbl_8064FE38 * fn_80101960(lbl_8064FE38, bits->value);
        return lbl_8064FE30 * fn_80101960(lbl_8064FE30, bits->value);
    }
    exponent += 54;
    bits->words.high = (high & 0x800FFFFF) | (exponent << 20);
    return lbl_8064FE40 * bits->value;
}
