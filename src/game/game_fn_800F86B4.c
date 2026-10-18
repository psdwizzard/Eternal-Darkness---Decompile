/* __str2dec (0x800F86B4, 236 bytes): build a decimal record from a digit
 * string, rounding half-to-even on the first truncated digit. */

typedef struct Decimal {
    signed char sign;
    short exp;
    struct {
        unsigned char length;
        unsigned char text[36];
    } sig;
} Decimal;

void __str2dec(Decimal *d, const signed char *s, short exp) {
    int i;
    const signed char *p;
    unsigned char *digit;
    unsigned char *first;

    d->exp = exp;
    d->sign = 0;
    i = 0;
    while (i < 36 && *s != 0) {
        d->sig.text[i++] = *s++ - '0';
    }
    d->sig.length = i;

    if (*s == 0) {
        return;
    }
    if (*s < 5) {
        return;
    }

    for (p = s + 1; *p != 0; p++) {
        if (*p != '0') {
            goto round_up;
        }
    }
    if ((d->sig.text[i - 1] & 1) == 0) {
        return;
    }

round_up:
    first = d->sig.text;
    digit = first + (short)(d->sig.length - 1);
    for (;;) {
        if (*digit < 9) {
            (*digit)++;
            return;
        }
        if (digit == first) {
            *digit = 1;
            d->exp++;
            return;
        }
        *digit-- = 0;
    }
}
