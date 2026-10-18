typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef struct decimal {
    signed char sign;
    char unused;
    short exp;
    struct {
        u8 length;
        u8 text[36];
        u8 unused;
    } sig;
} decimal;
typedef union double_bits {
    double d;
    u64 raw;
    struct { u32 high; int low; } words;
} double_bits;

extern u8 __ctype_map[];
extern u8 __lower_map[];
static inline int decimal_toupper(int c) {
    return c == -1 ? -1 : __lower_map[(u8)c];
}
extern double lbl_8024AA28[];
extern decimal lbl_80239D00;
extern u32 __float_huge[];
#define INFINITY_VALUE (*(float *)__float_huge)
extern u32 __double_max[];
#define MINIMUM_VALUE (*(double *)__double_max)
extern double lbl_8064F930, lbl_8064F938, lbl_8064F940;
extern double lbl_8064F948;
extern double lbl_8064F950;
extern double copysign(double, double);
extern double pow(double, double);
extern double ldexp(double, int);
extern double nextafter(double, double);
extern void __num2dec_internal(decimal *, double);
extern void __minus_dec(decimal *, const decimal *, const decimal *);
extern int __less_dec(const decimal *, const decimal *);
extern int __equals_dec(const decimal *, const decimal *);
extern void *__str2dec(void *, const void *, unsigned int);

#define CLASSIFY_DOUBLE(out, number) \
    switch ((int)((number).words.high & 0x7FF00000)) { \
    case 0x7FF00000: \
        if (((number).words.high & 0xFFFFF) || (number).words.low != 0) \
            (out) = 1; \
        else \
            (out) = 2; \
        break; \
    case 0: \
        if (((number).words.high & 0xFFFFF) || (number).words.low != 0) \
            (out) = 5; \
        else \
            (out) = 3; \
        break; \
    default: \
        (out) = 4; \
    }

/* Convert the scanner's decimal significand to an IEEE double. */
double __dec2num(const decimal *input)
{
    double_bits nan_bits, result, initial_class, upper_class, loop_class;
    double next, sign, sum;
    decimal dec, minimum, below, above, difference_a, difference_b;
    decimal above_negative, difference_c, difference_d;
    int exponent, count, i, code, any, low_half, classification;
    u8 digit;
    u8 *p, *end, *walker;
    unsigned int group;

    if (input->sig.length == 0) {
        if ((signed char)input->sign == 0) sign = lbl_8064F938;
        else sign = lbl_8064F940;
        return copysign(lbl_8064F930, sign);
    }

    switch (input->sig.text[0]) {
    case '0':
        if ((signed char)input->sign == 0) sign = lbl_8064F938;
        else sign = lbl_8064F940;
        return copysign(lbl_8064F930, sign);
    case 'I':
        if ((signed char)input->sign == 0) sign = lbl_8064F938;
        else sign = lbl_8064F940;
        return copysign(INFINITY_VALUE, sign);
    case 'N':
        nan_bits.raw = 0x7FF0000000000000ULL;
        if ((signed char)input->sign != 0)
            nan_bits.raw |= 0x8000000000000000ULL;
        if (input->sig.length == 1) {
            nan_bits.words.high |= 0x80000;
        } else {
            count = input->sig.length;
            p = (u8 *)&nan_bits.words.high + 1;
            any = 0;
            low_half = 1;
            if (count > 14)
                count = 14;
            for (i = 1; i < count; i++) {
                code = input->sig.text[i + 0];
                if (__ctype_map[code] & 0x10)
                    digit = code - '0';
                else
                    digit = decimal_toupper(code) - 'W';
                if (digit != 0)
                    any = 1;
                if (low_half)
                    *p++ |= digit;
                else
                    *p = digit << 4;
                low_half = low_half == 0;
            }
            if (!any)
                nan_bits.words.high |= 0x80000;
        }
        return nan_bits.d;
    }

    dec = *input;
    p = dec.sig.text;
    walker = p;
    end = p + dec.sig.length;
    while (walker < end) { *walker -= '0'; walker++; }
    p++;
    dec.exp += dec.sig.length - 1;
    exponent = dec.exp;
    initial_class.words.high = 0x43300000;
    initial_class.words.low = dec.sig.text[0];
    result.d = initial_class.d - lbl_8064F950;
    while (p < end) {
        i = end - p;
        group = 0;
        i %= 8;
        if (i == 0)
            i = 8;
        count = i;
        while (count > 0) {
            group = group * 10 + *p++;
            count--;
        }
        next = result.d * lbl_8024AA28[i - 1];
        initial_class.words.high = 0x43300000;
        initial_class.words.low = group;
        sum = next + (initial_class.d - lbl_8064F950);
        if (group == 0 || next != sum) {
            result.d = sum;
            exponent -= i;
        } else {
            break;
        }
    }
    if (exponent < 0)
        result.d /= pow(lbl_8064F948, (double)-exponent);
    else
        result.d *= pow(lbl_8064F948, (double)exponent);
    result.d = ldexp(result.d, exponent);
    initial_class.d = result.d;
    CLASSIFY_DOUBLE(classification, initial_class);
    if (classification == 2) {
        __str2dec(&minimum, &lbl_80239D00, 0x134);
        if (__less_dec(&minimum, &dec) != 0)
            goto finish;
        result.d = MINIMUM_VALUE;
    }
    __num2dec_internal(&below, result.d);
    if (__equals_dec(&below, &dec) != 0)
        goto finish;
    if (__less_dec(&below, &dec) != 0) {
        next = nextafter(result.d, INFINITY_VALUE);
        upper_class.d = next;
        CLASSIFY_DOUBLE(classification, upper_class);
        if (classification == 2) {
            result.d = next;
            goto finish;
        }
        __num2dec_internal(&above, next);
        while (__less_dec(&above, &dec) != 0) {
            below = above;
            result.d = next;
            next = nextafter(next, INFINITY_VALUE);
            loop_class.d = next;
            CLASSIFY_DOUBLE(classification, loop_class);
            if (classification == 2) {
                result.d = next;
                goto finish;
            }
            __num2dec_internal(&above, next);
        }
        __minus_dec(&difference_a, &dec, &below);
        __minus_dec(&difference_b, &above, &dec);
        if (__equals_dec(&difference_a, &difference_b)) {
            if ((*(u64 *)&result.d & 1ULL) != 0)
                result.d = next;
        } else if (__less_dec(&difference_a, &difference_b) == 0) {
            result.d = next;
        }
    } else {
        next = nextafter(result.d, -INFINITY_VALUE);
        __num2dec_internal(&above_negative, next);
        while (__less_dec(&dec, &above_negative) != 0) {
            below = above_negative;
            result.d = next;
            next = nextafter(next, -INFINITY_VALUE);
            __num2dec_internal(&above_negative, next);
        }
        __minus_dec(&difference_c, &dec, &above_negative);
        __minus_dec(&difference_d, &below, &dec);
        if (__equals_dec(&difference_c, &difference_d)) {
            if ((*(u64 *)&result.d & 1ULL) != 0)
                result.d = next;
        } else if (__less_dec(&difference_c, &difference_d) != 0) {
            result.d = next;
        }
    }
finish:
    if (dec.sign)
        result.d = -result.d;
    return result.d;
}

