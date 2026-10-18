/* __copy_longs_unaligned (0x800F9B0C, 196 bytes): MSL __copy_longs_unaligned.
 * Copies n bytes from src to dst when the two pointers have different
 * word alignment: align dst, then merge shifted source words.
 * As in MSL, src/dst themselves are walked through byte and word views
 * (MWCC accepts cast expressions as lvalues). */

#define cps ((unsigned char*)src)
#define cpd ((unsigned char*)dst)
#define lps ((unsigned long*)src)
#define lpd ((unsigned long*)dst)
#define deref_auto_inc(p) *++(p)

void __copy_longs_unaligned(void* dst, const void* src, unsigned long n) {
    unsigned long i, v1, v2;
    unsigned int src_offset, left_shift, right_shift;

    i = (-(unsigned long)dst) & 3;

    cps = ((unsigned char*)src) - 1;
    cpd = ((unsigned char*)dst) - 1;

    if (i) {
        n -= i;
        do {
            deref_auto_inc(cpd) = deref_auto_inc(cps);
        } while (--i);
    }

    src_offset = ((unsigned int)(cps + 1)) & 3;

    left_shift = src_offset << 3;
    right_shift = 32 - left_shift;

    cps -= src_offset;

    lps = ((unsigned long*)(cps + 1)) - 1;
    lpd = ((unsigned long*)(cpd + 1)) - 1;

    i = n >> 3;

    v1 = deref_auto_inc(lps);

    do {
        v2 = deref_auto_inc(lps);
        deref_auto_inc(lpd) = (v1 << left_shift) | (v2 >> right_shift);
        v1 = deref_auto_inc(lps);
        deref_auto_inc(lpd) = (v2 << left_shift) | (v1 >> right_shift);
    } while (--i);

    if (n & 4) {
        v2 = deref_auto_inc(lps);
        deref_auto_inc(lpd) = (v1 << left_shift) | (v2 >> right_shift);
    }

    cps = ((unsigned char*)(lps + 1)) - 1;
    cpd = ((unsigned char*)(lpd + 1)) - 1;

    n &= 3;

    if (n) {
        cps -= 4 - src_offset;
        do {
            deref_auto_inc(cpd) = deref_auto_inc(cps);
        } while (--n);
    }
}
