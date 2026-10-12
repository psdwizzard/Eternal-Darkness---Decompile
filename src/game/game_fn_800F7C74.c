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

/* Subtract two positive decimal significands, retaining up to 36 digits. */
void fn_800F7C74(decimal *result, const decimal *a, const decimal *b)
{
    int limit, shift, count, round;
    u8 *first, *p;
    const u8 *other_first, *other, *tail;
    u8 *borrow;
    const u8 *end;

    *result = *a;
    if (b->sig.text[0] == 0)
        return;

    limit = result->sig.length;
    if (limit < (int)b->sig.length)
        limit = b->sig.length;
    shift = result->exp - b->exp;
    limit += shift;
    if (limit > 36)
        limit = 36;
    while (result->sig.length < limit)
        result->sig.text[result->sig.length++] = 0;

    first = result->sig.text;
    p = first + limit;
    count = b->sig.length + shift;
    if (count < limit)
        p = first + count;
    other_first = b->sig.text;
    other = other_first + (p - first - shift);
    tail = other;
    while (p > first && other > other_first) {
        if (*--p < *--other) {
            borrow = p - 1;
            while (*borrow == 0)
                --borrow;
            while (borrow != p) {
                --*borrow;
                *++borrow += 10;
            }
        }
        *p -= *other;
    }

    count = tail - other_first;
    if (count < b->sig.length) {
        round = 0;
        if (*tail < 5)
            round = 1;
        else if (*tail == 5) {
            end = b->sig.text + b->sig.length;
            for (other = tail + 1; other < end; ++other) {
                if (*other != 0)
                    goto normalize;
            }
            count += shift;
            p = first + count - 1;
            if (*p & 1)
                round = 1;
        }
        if (round) {
            if (*p < 1) {
                borrow = p - 1;
                while (*borrow == 0)
                    --borrow;
                while (borrow != p) {
                    --*borrow;
                    *++borrow += 10;
                }
            }
            --*p;
        }
    }

normalize:
    p = first;
    while (*p == 0)
        ++p;
    if (p > first) {
        u8 removed = p - first;
        result->exp -= removed;
        end = first + result->sig.length;
        while (p < end)
            *first++ = *p++;
        result->sig.length -= removed;
    }
    first = result->sig.text;
    p = first + result->sig.length;
    while (p > first) {
        if (*--p != 0)
            break;
    }
    result->sig.length = p - first + 1;
}
