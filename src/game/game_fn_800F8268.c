typedef unsigned char u8;

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

/* Compare decimal magnitudes, allowing trailing zero digits. */
int __equals_dec(const decimal *a, const decimal *b)
{
    int b_length, a_length, i, common;

    if (a->sig.text[0] == 0)
        return b->sig.text[0] == 0;
    if (b->sig.text[0] == 0)
        return a->sig.text[0] == 0;

    if (a->exp == b->exp) {
        a_length = a->sig.length;
        b_length = b->sig.length;
        common = a_length;
        if (a_length > b_length)
            common = b_length;

        for (i = 0; i < common; ++i) {
            if (a->sig.text[i] != b->sig.text[i])
                return 0;
        }
        if (common == a_length) {
            for (; i < b_length; ++i) {
                if (b->sig.text[i] != 0)
                    return 0;
            }
        } else {
            for (; i < a_length; ++i) {
                if (a->sig.text[i] != 0)
                    return 0;
            }
        }
        return 1;
    }
    return 0;
}
