/* fn_800F5ECC: __div2i, the MSL runtime helper for signed 64-bit division.
 * The retail routine is hand-written assembly that relies on carry-chained
 * adde/subfe shifts; this is a C rendering of the same shift-subtract
 * algorithm. */

typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;

s64 fn_800F5ECC(s64 dividend, s64 divisor) {
    u32 sign_a;
    u32 sign_b;
    u32 ah, al, bh, bl;
    u32 rh, rl;
    int za, zb;
    int count;
    int shift;
    u32 bit;
    u32 th, tl;

    ah = (u32)((u64)dividend >> 32);
    al = (u32)dividend;
    sign_a = ah & 0x80000000;
    if (sign_a != 0) {
        dividend = -dividend;
        ah = (u32)((u64)dividend >> 32);
        al = (u32)dividend;
    }
    bh = (u32)((u64)divisor >> 32);
    bl = (u32)divisor;
    sign_b = bh & 0x80000000;
    if (sign_b != 0) {
        divisor = -divisor;
        bh = (u32)((u64)divisor >> 32);
        bl = (u32)divisor;
    }

    za = __cntlzw(ah);
    if ((s32)ah == 0) {
        za = __cntlzw(al) + 32;
    }
    zb = __cntlzw(bh);
    if ((s32)bh == 0) {
        zb = __cntlzw(bl) + 32;
    }
    if (za > zb) {
        return 0;
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

    bit = 0;
    do {
        rh = (rh << 1) | (rl >> 31);
        rl = (rl << 1) | (ah >> 31);
        ah = (ah << 1) | (al >> 31);
        al = (al << 1) | bit;
        tl = rl - bl;
        th = rh - bh - (rl < bl);
        bit = 0;
        if ((s32)th >= 0) {
            rl = tl;
            rh = th;
            bit = 1;
        }
    } while (--count != 0);
    ah = (ah << 1) | (al >> 31);
    al = (al << 1) | bit;

    dividend = ((s64)ah << 32) | al;
    if (sign_a ^ sign_b) {
        dividend = -dividend;
    }
    return dividend;
}
