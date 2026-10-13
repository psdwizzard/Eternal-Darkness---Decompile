/* __div2u (0x800F5DE0, 236 bytes): MSL runtime unsigned 64-bit division.
 * The retail routine is hand-written assembly that threads the carry bit
 * through adde/subfe chains; this is a C restatement of the same
 * shift-subtract algorithm working on 32-bit halves. */

typedef unsigned long u32;
typedef unsigned long long u64;

u64 __div2u(u32 a_hi, u32 a_lo, u32 b_hi, u32 b_lo) {
    int a_lz;
    int b_lz;
    int count;
    int tmp;
    int total;
    int sh;
    u32 r_hi;
    u32 r_lo;
    u32 bit;
    u32 d_hi;
    u32 d_lo;

    a_lz = __cntlzw(a_hi);
    tmp = __cntlzw(a_lo);
    if ((int)a_hi == 0) {
        a_lz = tmp + 32;
    }
    b_lz = __cntlzw(b_hi);
    tmp = __cntlzw(b_lo);
    if ((int)b_hi == 0) {
        b_lz = tmp + 32;
    }
    total = 64 - a_lz;
    if (a_lz <= b_lz) {
        b_lz = 64 - (b_lz + 1);
        a_lz += b_lz;
        count = total - b_lz;

        /* remainder = a >> count */
        sh = count - 32;
        if (count >= 32) {
            r_lo = a_hi >> sh;
            r_hi = 0;
        } else {
            r_lo = (a_lo >> count) | (a_hi << (32 - count));
            r_hi = a_hi >> count;
        }
        /* quotient bits = a << a_lz */
        sh = a_lz - 32;
        if (a_lz >= 32) {
            a_hi = a_lo << sh;
            a_lo = 0;
        } else {
            a_hi = (a_hi << a_lz) | (a_lo >> (32 - a_lz));
            a_lo = a_lo << a_lz;
        }

        bit = 0;
        do {
            r_hi = (r_hi << 1) | (r_lo >> 31);
            r_lo = (r_lo << 1) | (a_hi >> 31);
            a_hi = (a_hi << 1) | (a_lo >> 31);
            a_lo = (a_lo << 1) | bit;
            d_lo = r_lo - b_lo;
            d_hi = r_hi - b_hi - (r_lo < b_lo);
            bit = 0;
            if ((int)d_hi >= 0) {
                r_lo = d_lo;
                r_hi = d_hi;
                bit = 1;
            }
        } while (--count != 0);

        a_hi = (a_hi << 1) | (a_lo >> 31);
        a_lo = (a_lo << 1) | bit;
        return ((u64)a_hi << 32) | a_lo;
    }
    return 0;
}
