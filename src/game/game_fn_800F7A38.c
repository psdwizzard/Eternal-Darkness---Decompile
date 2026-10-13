typedef unsigned char u8;

typedef struct decimal {
    signed char sign;
    char unused;
    short exp;
    struct { u8 length; u8 text[36]; u8 unused; } sig;
} decimal;

extern const double lbl_8064F930;
extern double fn_80101BA4(double value, int *exponent);
extern double fn_80101C30(double value, int n);
extern double fn_80101DF4(double value, double *integral);
extern unsigned long long fn_800F6318(double value);
extern unsigned int fn_800F8B3C(unsigned int value);
extern void fn_800F8374(decimal *out, short exponent);
extern void fn_800F8A2C(decimal *out, unsigned long long value);
extern void fn_800F87A0(decimal *out, const decimal *left, const decimal *right);

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
        return fn_800F8B3C(words[1]);
    return 32 + fn_800F8B3C(words[0] | 0x00100000);
}

void fn_800F7A38(decimal *d, double x)
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
        double frac = fn_80101BA4(x, &exp);
        short num_bits = 53 - count_trailing_zero(frac);
        decimal int_d;
        decimal pow2_d;
        double integral;

        fn_800F8374(&pow2_d, exp - num_bits);
        fn_80101DF4(fn_80101C30(frac, num_bits), &integral);
        fn_800F8A2C(&int_d, fn_800F6318(integral));
        fn_800F87A0(d, &int_d, &pow2_d);
        d->sign = sign;
    }
}
