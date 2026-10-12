typedef union DoubleBits {
    double value;
    struct {
        unsigned long high;
        unsigned long low;
    } words;
} DoubleBits;

/* Advance value by one representable double toward direction. */
double fn_80101EF0(double value, double direction)
{
    DoubleBits *x = (DoubleBits *)&value;
    DoubleBits *y = (DoubleBits *)&direction;
    int hx, hy, ix, iy;
    unsigned long lx, ly;

    hx = x->words.high;
    lx = x->words.low;
    hy = y->words.high;
    ly = y->words.low;
    ix = hx & 0x7FFFFFFF;
    iy = hy & 0x7FFFFFFF;
    if ((ix >= 0x7FF00000 && ((ix - 0x7FF00000) | lx) != 0) ||
        (iy >= 0x7FF00000 && ((iy - 0x7FF00000) | ly) != 0))
        return value + direction;
    if (value == direction)
        return value;
    if ((ix | lx) == 0) {
        x->words.high = hy & 0x80000000;
        x->words.low = 1;
        direction = value * value;
        if (direction == value)
            return direction;
        return value;
    }
    if (hx >= 0) {
        if (hx > hy || (hx == hy && lx > ly)) {
            if (lx == 0)
                hx -= 1;
            lx -= 1;
        } else {
            lx += 1;
            if (lx == 0)
                hx += 1;
        }
    } else {
        if (hy >= 0 || hx > hy || (hx == hy && lx > ly)) {
            if (lx == 0)
                hx -= 1;
            lx -= 1;
        } else {
            lx += 1;
            if (lx == 0)
                hx += 1;
        }
    }
    hy = hx & 0x7FF00000;
    if (hy >= 0x7FF00000)
        return value + value;
    if (hy < 0x00100000) {
        direction = value * value;
        if (direction != value) {
            y->words.high = hx;
            y->words.low = lx;
            return direction;
        }
    }
    x->words.high = hx;
    x->words.low = lx;
    return value;
}
