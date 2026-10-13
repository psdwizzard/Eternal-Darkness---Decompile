/* __mod2u: the MSL runtime helper for unsigned 64-bit modulo.
 * The retail routine is hand-written assembly that relies on carry-chained
 * adde/subfe shifts; this is a C rendering of the same shift-subtract
 * algorithm, returning the remainder. */

typedef int s32;
typedef unsigned int u32;
typedef unsigned long long u64;

u64 __mod2u(u64 dividend, u64 divisor) {
    u32 ah, al, bh, bl;
    u32 rh, rl;
    u32 th, tl;
    int za, zb;
    int count;
    int shift;

    ah = (u32)(dividend >> 32);
    al = (u32)dividend;
    bh = (u32)(divisor >> 32);
    bl = (u32)divisor;

    za = __cntlzw(ah);
    shift = __cntlzw(al);
    if ((s32)ah == 0) {
        za = shift + 32;
    }
    zb = __cntlzw(bh);
    shift = __cntlzw(bl);
    if ((s32)bh == 0) {
        zb = shift + 32;
    }
    count = 64 - za;
    if (za > zb) {
        return dividend;
    }

    shift = 64 - (zb + 1);
    za = za + shift;
    count = count - shift;
    shift = za;

    th = count - 32;
    if (count >= 32) {
        rl = ah >> th;
        rh = 0;
    } else {
        rl = (al >> count) | (ah << (32 - count));
        rh = ah >> count;
    }
    tl = shift - 32;
    if (shift >= 32) {
        ah = al << tl;
        al = 0;
    } else {
        ah = (ah << shift) | (al >> (32 - shift));
        al = al << shift;
    }

    do {
        rh = (rh << 1) | (rl >> 31);
        rl = (rl << 1) | (ah >> 31);
        ah = (ah << 1) | (al >> 31);
        al = al << 1;
        tl = rl - bl;
        th = rh - bh - (rl < bl);
        if ((s32)th >= 0) {
            rl = tl;
            rh = th;
        }
    } while (--count != 0);

    return ((u64)rh << 32) | rl;
}
