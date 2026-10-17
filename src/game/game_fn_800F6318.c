/* fn_800F6318: convert a double to a signed 64-bit integer, truncating
 * toward zero and saturating on overflow. */

typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;

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
    hi = u.w[0];
    lo = u.w[1];
    exp = (hi >> 20) & 0x7FF;
    if ((u32)exp < 0x3FF) {
        hi = 0;
        lo = 0;
        goto done;
    }
    /* ASM: mr preserves the original sign word across significand shifts.
     * C otherwise reloads this value from the spilled double. */
    asm { mr sign, hi }
    hi = __rlwinm(hi, 0, 12, 31);
    /* ASM: oris restores the implicit leading significand bit in place;
     * C uses a separate register to load and OR this constant. */
    asm { oris hi, hi, 0x10 }
    /* ASM: subi keeps exponent adjustment separate from the comparison;
     * C combines it into a carry-setting subic. instruction. */
    asm { subi exp, exp, 0x433 }
    if (exp < 0) {
        exp = -exp;
        /* ASM: subfic/subic form the cross-word shift counts in the
         * runtime scratch registers; C does not retain these registers
         * or the carry-setting subtraction. */
        asm {
            subfic r8, exp, 0x20
            subic r9, exp, 0x20
        }
        lo >>= exp;
        /* ASM: slw/or/srw/or merge the cross-word and over-word bits.
         * C cannot retain the runtime scratch-register allocation. */
        asm {
            slw r10, hi, r8
            or lo, lo, r10
            srw r10, hi, r9
            or lo, lo, r10
        }
        hi >>= exp;
    } else {
        if (exp > 10) {
            if (sign &= 0x80000000) {
                hi = 0x80000000;
                lo = 0;
                goto done;
            }
            hi = 0x7FFF0000;
            /* ASM: ori completes the positive saturation word; C loads
             * 0x7fffffff with lis/subi instead of lis/ori. */
            asm { ori hi, hi, 0xFFFF }
            lo = 0xFFFFFFFF;
            goto done;
        }
        /* ASM: subfic/subic form the cross-word shift counts in the
         * runtime scratch registers; C does not retain these registers
         * or the carry-setting subtraction. */
        asm {
            subfic r8, exp, 0x20
            subic r9, exp, 0x20
        }
        hi <<= exp;
        /* ASM: srw/or/slw/or merge the cross-word and over-word bits.
         * C cannot retain the runtime scratch-register allocation. */
        asm {
            srw r10, lo, r8
            or hi, hi, r10
            slw r10, lo, r9
            or hi, hi, r10
        }
        lo <<= exp;
    }
    if (sign &= 0x80000000) {
        return -(((u64)hi << 32) | lo);
    }
done:
    return ((u64)hi << 32) | lo;
}
