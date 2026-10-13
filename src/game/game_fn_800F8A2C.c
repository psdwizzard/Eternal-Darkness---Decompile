typedef unsigned char u8;

/* MSL-style decimal: sign, base-10 exponent, and up to 36 significant digits
 * (most significant first). Same layout as in game_fn_800F7A38.c. */
typedef struct decimal {
    signed char sign;
    char unused;
    short exp;
    struct { u8 length; u8 text[36]; u8 unused; } sig;
} decimal;

/* Convert an unsigned 64-bit integer to decimal form. */
void fn_800F8A2C(decimal *d, unsigned long long x)
{
    u8 *start;
    u8 *end;
    u8 t;

    d->sign = 0;

    if (x == 0) {
        d->exp = 0;
        d->sig.length = 1;
        d->sig.text[0] = 0;
        return;
    }

    /* Emit digits least significant first, then reverse them in place. */
    d->sig.length = 0;
    while (x != 0) {
        d->sig.text[d->sig.length++] = x % 10;
        x /= 10;
    }

    start = d->sig.text;
    end = d->sig.text + d->sig.length;
    while (start < --end) {
        t = *start;
        *start++ = *end;
        *end = t;
    }

    d->exp = d->sig.length - 1;
}
