/* fn_800F6318: convert a double to a signed 64-bit integer, truncating
 * toward zero and saturating on overflow. */

typedef unsigned int u32;
typedef long long s64;

s64 fn_800F6318(double x) {
    union {
        double d;
        u32 w[2];
    } u;
    register u32 hi;
    register u32 lo;
    register int exp;
    register u32 sign;

    u.d = x;
    sign = u.w[0];
    lo = u.w[1];
    exp = (sign >> 20) & 0x7FF;
    if ((u32)exp < 0x3FF) {
        return 0;
    }
    hi = (sign & 0xFFFFF) | 0x100000;
    exp -= 0x433;
    if (exp < 0) {
        exp = -exp;
        /* ASM: subfic/subic/srw/slw/or/srw/or/srw - inline 64-bit right
         * shift of hi:lo; C emits a call to __shr2u instead. */
        asm {
            subfic r8, exp, 0x20
            subic r9, exp, 0x20
            srw lo, lo, exp
            slw r10, hi, r8
            or lo, lo, r10
            srw r10, hi, r9
            or lo, lo, r10
            srw hi, hi, exp
        }
    } else {
        if (exp > 10) {
            if (sign & 0x80000000) {
                return 0x8000000000000000LL;
            }
            return 0x7FFFFFFFFFFFFFFFLL;
        }
        /* ASM: subfic/subic/slw/srw/or/slw/or/slw - inline 64-bit left
         * shift of hi:lo; C emits a call to __shl2i instead. */
        asm {
            subfic r8, exp, 0x20
            subic r9, exp, 0x20
            slw hi, hi, exp
            srw r10, lo, r8
            or hi, hi, r10
            slw r10, lo, r9
            or hi, hi, r10
            slw lo, lo, exp
        }
    }
    if (sign & 0x80000000) {
        return -(((s64)hi << 32) | lo);
    }
    return ((s64)hi << 32) | lo;
}
