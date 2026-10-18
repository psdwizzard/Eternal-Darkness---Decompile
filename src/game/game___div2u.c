/* __div2u (0x800F5DE0, 236 bytes): MSL runtime unsigned 64-bit division.
 * The retail routine is hand-written assembly that threads the carry bit
 * through adde/subfe chains; this is a C restatement of the same
 * shift-subtract algorithm working on 32-bit halves. */

typedef unsigned long u32;
typedef unsigned long long u64;

u64 __div2u(u64 dividend, u64 divisor) {
    register u32 a_hi = dividend >> 32;
    register u32 a_lo = dividend;
    register u32 b_hi = divisor >> 32;
    register u32 b_lo = divisor;
    u64 difference;
    register u32 trial_lo;
    register u32 r_lo;
    int dividend_lz;
    register int shift;
    register int count;
    register int total;
    register u32 r_hi;

    dividend_lz = __cntlzw(a_hi);
    count = __cntlzw(a_lo);
    if ((int)a_hi == 0) {
        dividend_lz = count + 32;
    }
    count = __cntlzw(b_hi);
    total = __cntlzw(b_lo);
    if ((int)b_hi == 0) {
        count = total + 32;
    }
    total = 64 - dividend_lz;
    if (dividend_lz <= count) {
        count = 64 - (count + 1);
        shift = dividend_lz + count;
        count = total - count;
        /* ASM: mtctr initializes CTR; a C loop uses a subtraction that
         * overwrites the quotient bit carried in XER. */
        asm { mtctr count }

        /* remainder = a >> count */
        r_hi = count - 32;
        if (count >= 32) {
            r_lo = a_hi >> r_hi;
            r_hi = 0;
        } else {
            /* ASM: srw anchors the low-half shift before its cross-word
             * complement; C schedules the independent subtraction first. */
            asm { srw r_lo, a_lo, count }
            r_hi = 32 - count;
            r_hi = a_hi << r_hi;
            r_lo |= r_hi;
            r_hi = a_hi >> count;
        }
        /* quotient bits = a << shift */
        /* ASM: cmpwi/subic/blt retain the carry-producing subtraction
         * and its comparison; C selects addi for the shift offset. */
        asm {
            cmpwi shift, 32
            subic count, shift, 32
            blt small_shift
        }
        {
            a_hi = a_lo << count;
            a_lo = 0;
            goto shifted;
        }
        small_shift: {
            /* ASM: slw preserves the high-half shift before the complement
             * calculation, which C otherwise schedules ahead of it. */
            asm { slw a_hi, a_hi, shift }
            count = 32 - shift;
            count = a_lo >> count;
            a_hi |= count;
            /* ASM: slw completes the low half after the cross-word merge;
             * C schedules it before the merge because they are independent. */
            asm { slw a_lo, a_lo, shift }
        }

        shifted:
        total = -1;
        /* ASM: addic clears XER carry; C has no carry-bit lvalue. */
        asm { addic r_hi, r_hi, 0 }
        divide_bit: {
            /* ASM: adde shifts the combined dividend/remainder through
             * XER carry, which C cannot preserve as an implicit input
             * between loop iterations. */
            asm {
                adde a_lo, a_lo, a_lo
                adde a_hi, a_hi, a_hi
                adde r_lo, r_lo, r_lo
                adde r_hi, r_hi, r_hi
            }
            difference = (((u64)r_hi << 32) | r_lo) -
                         (((u64)b_hi << 32) | b_lo);
            /* Split the trial remainder; its signed high word detects borrow. */
            trial_lo = (u32)difference;
            count = difference >> 32;
            if (count >= 0) {
                r_lo = trial_lo;
                r_hi = count;
                /* ASM: addic sets XER carry to append a quotient bit. */
                asm { addic trial_lo, total, 1 }
            }
        }
        /* ASM: bdnz decrements CTR without overwriting the quotient carry. */
        asm { bdnz divide_bit }

        /* ASM: adde appends the last quotient bit from XER carry. */
        asm {
            adde a_lo, a_lo, a_lo
            adde a_hi, a_hi, a_hi
        }
        return ((u64)a_hi << 32) | a_lo;
    }
    return 0;
}
