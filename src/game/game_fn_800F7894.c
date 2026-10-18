typedef unsigned char u8;

typedef struct decimal {
    signed char sign;
    char unused;
    short exp;
    struct { u8 length; u8 text[36]; u8 unused; } sig;
} decimal;

typedef struct decform {
    char style;
    char unused;
    short digits;
} decform;

#define SIGDIGLEN 36

extern void __num2dec_internal(decimal *d, double x);

static int __must_round(const decimal *d, int digits)
{
    u8 const *i = d->sig.text + digits;

    if (*i > 5) {
        return 1;
    }
    if (*i < 5) {
        return -1;
    }
    {
        u8 const *e = d->sig.text + d->sig.length;
        for (i++; i < e; i++) {
            if (*i != 0) {
                return 1;
            }
        }
    }
    if (d->sig.text[digits - 1] & 1) {
        return 1;
    }
    return -1;
}

static void __dorounddecup(decimal *d, int digits)
{
    u8 *b = d->sig.text;
    u8 *i = b + digits - 1;

    while (1) {
        if (*i < 9) {
            (*i)++;
            break;
        }
        if (i == b) {
            *i = 1;
            d->exp++;
            break;
        }
        *i-- = 0;
    }
}

static void __rounddec(decimal *d, int digits)
{
    if (digits > 0 && digits < d->sig.length) {
        int unkBool = __must_round(d, digits);
        d->sig.length = digits;
        if (unkBool >= 0) {
            __dorounddecup(d, digits);
        }
    }
}

void __num2dec(const decform *f, decimal *d, double x)
{
    short digits = f->digits;
    int i;

    __num2dec_internal(d, x);
    if (d->sig.text[0] > 9) {
        return;
    }
    if (digits > SIGDIGLEN) {
        digits = SIGDIGLEN;
    }
    __rounddec(d, digits);
    while (d->sig.length < digits) {
        d->sig.text[d->sig.length++] = 0;
    }
    d->exp -= d->sig.length - 1;
    for (i = 0; i < d->sig.length; i++) {
        d->sig.text[i] += '0';
    }
}
