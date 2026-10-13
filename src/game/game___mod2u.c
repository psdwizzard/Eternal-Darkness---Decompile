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
    if ((s32)ah == 0) {
        za = __cntlzw(al) + 32;
    }
    zb = __cntlzw(bh);
    if ((s32)bh == 0) {
        zb = __cntlzw(bl) + 32;
    }
    if (za > zb) {
        return dividend;
    }

    shift = 64 - (zb + 1);
    count = (64 - za) - shift;
    shift = za + shift;

    if (count >= 32) {
        rl = ah >> (count - 32);
        rh = 0;
    } else {
        rl = (al >> count) | (ah << (32 - count));
        rh = ah >> count;
    }
    if (shift >= 32) {
        ah = al << (shift - 32);
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
