/* fn_800F5ECC: __div2i, the MSL runtime helper for signed 64-bit division.
 * The retail routine is hand-written assembly that relies on carry-chained
 * adde/subfe shifts. The normalization is C; small assembly blocks
 * preserve the carry chain and instruction ordering. */

typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;

s64 fn_800F5ECC(s64 numerator, s64 denominator) {
    register u32 ah, al, bh, bl;
    volatile struct { u32 a, b; } signs;
    s64 dividend;
    /* Reuse the normalization work words for the trial remainder. */
    register int tl;
    register u32 rh, rl;
    register int th, ones;

    ah = (u64)numerator >> 32;
    al = numerator;
    bh = (u64)denominator >> 32;
    bl = denominator;
    th = (u32)((s32)ah >> 31) << 31;
    if (th != 0) {
        u64 magnitude = -(((u64)ah << 32) | al);
        ah = magnitude >> 32;
        al = magnitude;
    }
    signs.a = th;
    ones = (u32)((s32)bh >> 31) << 31;
    if (ones != 0) {
        u64 magnitude = -(((u64)bh << 32) | bl);
        bh = magnitude >> 32;
        bl = magnitude;
    }
    signs.b = ones;

    /* Compare operand bit lengths before aligning the division window. */
    tl = __cntlzw(ah);
    th = __cntlzw(al);
    if ((s32)ah == 0) {
        tl = th + 32;
    }
    th = __cntlzw(bh);
    ones = __cntlzw(bl);
    if ((s32)bh == 0) {
        th = ones + 32;
    }
    ones = 64 - tl;
    if (tl <= th) {
        /* tl becomes the left shift, th the quotient iteration count. */
        th++;
        th = 64 - th;
        tl += th;
        th = ones - th;
        /* ASM: mtctr keeps the loop count from disturbing the carry chain. */
        asm { mtctr th }
        rh = th - 32;
        if (th >= 32) {
            rl = ah >> rh;
            rh = 0;
        } else {
            /* ASM: srw keeps the low-word shift ahead of the cross-word
             * count calculation, which C schedules before it. */
            asm { srw rl, al, th }
            rh = 32 - th;
            rh = ah << rh;
            rl |= rh;
            rh = ah >> th;
        }
        th = tl - 32;
        if (tl >= 32) {
            ah = al << th;
            al = 0;
        } else {
            /* ASM: slw keeps the high-word shift before the cross-word
             * count calculation, which C schedules ahead of it. */
            asm { slw ah, ah, tl }
            th = 32 - tl;
            th = al >> th;
            ah |= th;
            /* ASM: slw keeps the low word intact until the high word
             * has consumed its cross-word bits; C reorders this shift. */
            asm { slw al, al, tl }
        }

        ones = -1;
        /* ASM: addic clears the carry input to the four-word shift; C has
         * no way to initialize the processor carry flag explicitly. */
        asm { addic rh, rh, 0 }
division_step:
        {
            /* ASM: adde/subfc/subfe. shift the remainder and quotient through
             * carry, then subtract the divisor. C cannot retain this carry
             * chain between the two 64-bit quantities. */
            asm {
                adde al, al, al
                adde ah, ah, ah
                adde rl, rl, rl
                adde rh, rh, rh
                subfc tl, bl, rl
                subfe. th, bh, rh
            }
            if (th >= 0) {
                rl = tl;
                rh = th;
                /* ASM: addic sets carry to insert the next quotient bit;
                 * there is no C expression for writing XER carry. */
                asm { addic tl, ones, 1 }
            }
        }
        /* ASM: bdnz preserves the carry holding the next quotient bit. */
        asm { bdnz division_step }
        /* ASM: adde inserts the final quotient bit from XER carry, which
         * cannot be referenced by a C expression. */
        asm {
            adde al, al, al
            adde ah, ah, ah
        }

        dividend = (s64)(((u64)ah << 32) | al);
        th = signs.a;
        ones = signs.b;
        if (th ^ ones) {
            /* ASM: cmpwi retains the runtime helper's final sign condition
             * code; C removes this comparison because no branch uses it. */
            asm { cmpwi th, 0 }
            dividend = (s64)-(u64)dividend;
        }
        return dividend;
    }
    return 0;
}
