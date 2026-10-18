typedef unsigned char u8;
typedef unsigned int u32;
typedef signed short s16;

#define SIGDIGLEN 36

/* MSL decimal (ansi_fp.h) */
typedef struct decimal {
    u8 sign;
    u8 unk1;
    s16 exp;
    struct {
        u8 length;
        u8 text[SIGDIGLEN];
    } sig;
} decimal;

/* MSL __timesdec: result = x * y in decimal digits, rounded half-even */
void __timesdec(decimal *result, const decimal *x, const decimal *y)
{
    u32 accumulator = 0;
    u8 mantissa[SIGDIGLEN * 2];
    int i = x->sig.length + y->sig.length - 1;
    u8 *ip = mantissa + i + 1;
    u8 *ep = ip;

    result->sign = 0;

    for (; i > 0; i--) {
        int k = y->sig.length - 1;
        int j = i - k - 1;
        int l;
        int t;
        const u8 *jp;
        const u8 *kp;

        if (j < 0) {
            j = 0;
            k = i - 1;
        }

        jp = x->sig.text + j;
        kp = y->sig.text + k;
        l = k + 1;
        t = x->sig.length - j;

        if (l > t)
            l = t;

        for (; l > 0; l--, jp++, kp--)
            accumulator += *jp * *kp;

        *--ip = (u8)(accumulator % 10);
        accumulator /= 10;
    }

    result->exp = (s16)(x->exp + y->exp);

    if (accumulator) {
        *--ip = (u8)accumulator;
        result->exp++;
    }

    for (i = 0; i < SIGDIGLEN && ip < ep; i++, ip++)
        result->sig.text[i] = *ip;
    result->sig.length = (u8)i;

    if (ip < ep && *ip >= 5) {
        if (*ip == 5) {
            u8 *jp = ip + 1;

            for (; jp < ep; jp++) {
                if (*jp != 0)
                    goto round;
            }
            if ((*(ip - 1) & 1) == 0)
                return;
        }
    round: {
            u8 *text = result->sig.text;

            ip = text + result->sig.length - 1;
            for (;;) {
                if (*ip < 9) {
                    ++*ip;
                    return;
                }
                if (ip == text) {
                    *ip = 1;
                    result->exp++;
                    return;
                }
                *ip-- = 0;
            }
        }
    }
}
