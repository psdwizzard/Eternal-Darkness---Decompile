typedef unsigned char u8;

typedef struct decimal {
    signed char sign;
    char unused;
    short exp;
    struct { u8 length; u8 text[36]; u8 unused; } sig;
} decimal;

extern const double lbl_8064F930;
extern double frexp(double value, int *exponent);
extern double ldexp(double value, int n);
extern double modf(double value, double *integral);
extern unsigned long long fn_800F6318(double value);
extern unsigned int __count_trailing_zerol(unsigned int value);
extern void __two_exp(decimal *out, short exponent);
extern void __ull2dec(decimal *out, unsigned long long value);
extern void __timesdec(decimal *out, const decimal *left, const decimal *right);

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

static inline int count_trailing_zero(double value)
{
    unsigned long *words = (unsigned long *)&value;
    if (words[1] != 0)
        return __count_trailing_zerol(words[1]);
    return 32 + __count_trailing_zerol(words[0] | 0x00100000);
}

void __num2dec_internal(decimal *d, double x)
{
    signed char sign = (signed char)((*(unsigned long *)&x >> 31) != 0);

    if (lbl_8064F930 == x) {
        d->sign = sign;
        d->exp = 0;
        d->sig.length = 1;
        d->sig.text[0] = 0;
        return;
    }

    if (classify(x) <= 2) {
        d->sign = sign;
        d->exp = 0;
        d->sig.length = 1;
        d->sig.text[0] = (classify(x) == 1) ? 'N' : 'I';
        return;
    }

    if (sign)
        x = -x;

    {
        int exp;
        double frac = frexp(x, &exp);
        short num_bits = 53 - count_trailing_zero(frac);
        decimal int_d;
        decimal pow2_d;
        double integral;

        __two_exp(&pow2_d, exp - num_bits);
        modf(ldexp(frac, num_bits), &integral);
        __ull2dec(&int_d, fn_800F6318(integral));
        __timesdec(d, &int_d, &pow2_d);
        d->sign = sign;
    }
}
