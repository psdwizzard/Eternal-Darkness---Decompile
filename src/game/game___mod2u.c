/* __mod2u (0x800F6004, 228 bytes): MSL runtime unsigned 64-bit remainder.
 * The retail routine is hand-written assembly that threads the carry bit
 * through adde/subfe chains; this is a C restatement of the same
 * shift-subtract algorithm working on 32-bit halves. The four parameters
 * expose the runtime ABI: dividend in r3:r4 and divisor in r5:r6. */

typedef unsigned long u32;
typedef unsigned long long u64;

u64 __mod2u(register u32 a_hi, register u32 a_lo,
            register u32 b_hi, register u32 b_lo) {
    u64 difference;
    register u32 r_lo;
    register int a_lz;
    register int count;
    register int total;
    register u32 r_hi;

    a_lz = __cntlzw(a_hi);
    count = __cntlzw(a_lo);
    if ((int)a_hi == 0) {
        a_lz = count + 32;
    }
    count = __cntlzw(b_hi);
    total = __cntlzw(b_lo);
    if ((int)b_hi == 0) {
        count = total + 32;
    }
    total = 64 - a_lz;
    if (a_lz <= count) {
        count = 64 - (count + 1);
        a_lz += count;
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
        /* quotient bits = a << a_lz */
        /* ASM: cmpwi/subic/blt retain the carry-producing subtraction
         * and its comparison; C selects addi for the shift offset. */
        asm {
            cmpwi a_lz, 32
            subic count, a_lz, 32
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
            asm { slw a_hi, a_hi, a_lz }
            count = 32 - a_lz;
            count = a_lo >> count;
            a_hi |= count;
            /* ASM: slw completes the low half after the cross-word merge;
             * C schedules it before the merge because they are independent. */
            asm { slw a_lo, a_lo, a_lz }
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
            /* The normalization temporaries now hold the trial remainder. */
            a_lz = (u32)difference;
            count = difference >> 32;
            if (count >= 0) {
                r_lo = a_lz;
                r_hi = count;
                /* ASM: addic sets XER carry to append a quotient bit. */
                asm { addic a_lz, total, 1 }
            }
        }
        /* ASM: bdnz decrements CTR without overwriting the quotient carry. */
        asm { bdnz divide_bit }

        a_lo = r_lo;
        a_hi = r_hi;
        /* ASM: blr keeps the computed-remainder return separate from the
         * unchanged-dividend return; C merges these two return sites. */
        asm { blr }
    }
    return ((u64)a_hi << 32) | a_lo;
}
