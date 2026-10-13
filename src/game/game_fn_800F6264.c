/* Convert a signed 64-bit integer through a rounded double significand. */
typedef unsigned int u32;
typedef unsigned long long u64;

float fn_800F6264(long long value)
{
    union { double d; u32 word[2]; } result;
    register u32 hi;
    register u32 lo;
    register u32 sign;
    register int count, low_count, mask;
    register u32 shifted;

    hi = (u32)((u64)value >> 32);
    /* ASM: clrrwi./beq keep sign extraction after the stack prologue and
     * branch on its CR result; C adds a separate comparison here. */
    asm {
        clrrwi. sign, hi, 31
        beq nonnegative
    }
    value = -(u64)value;
nonnegative:
    hi = (u32)((u64)value >> 32);
    lo = (u32)value;
    /* ASM: or./li/beq test both words and initialize the exponent in r6
     * without disturbing CR. C folds the accumulator into a later neg. */
    asm {
        or. count, hi, lo
        li r6, 0
        beq zero
    }
    {
        count = __cntlzw(hi);
        low_count = __cntlzw(lo);
        mask = (int)(((u32)count << 26) & 0xF8000000) >> 31;
        mask &= low_count;
        count += mask;
        low_count = 32 - count;
        /* ASM: subic computes the over-word shift in r9; C selects subi
         * instead of this carry-setting runtime instruction. */
        asm {
            subic r9, count, 32
        }
        hi <<= count;
        /* ASM: srw keeps the cross-word shift after the high-word shift;
         * C reschedules the shift-count calculation past subic. */
        asm {
            srw shifted, lo, low_count
        }
        hi |= shifted;
        /* ASM: slw reads the over-word count in r9 and uses PowerPC's
         * zero result for out-of-range counts, unlike a portable C shift. */
        asm {
            slw shifted, lo, r9
        }
        hi |= shifted;
        /* ASM: slw completes normalization after merging the high word;
         * C schedules this shift before the final merge. */
        asm { slw lo, lo, count }
        /* ASM: subf updates the exponent in r6; C folds zero minus the
         * count into neg and releases the accumulator register. */
        asm { subf r6, count, r6 }
        count = lo & 0x7FF;
        /* ASM: addi biases the exponent in r6, which C cannot directly
         * access without introducing a transfer to a compiler temporary. */
        asm { addi r6, r6, 0x43E }
        if (count >= 0x400 && (count > 0x400 || (lo & 0x800))) {
            /* ASM: addic/addze/addze propagate rounding carry through the
             * significand and exponent; C has no three-word carry operation. */
            asm {
                addic lo, lo, 0x800
                addze hi, hi
                addze r6, r6
            }
        }
        lo = __rlwinm(lo, 21, 0, 31);
        lo = (lo & 0x001FFFFF) | (hi << 21);
        hi = (hi >> 11) & 0xFFFFF;
        /* ASM: slwi/or merge r6 into the IEEE high word in place; C
         * shifts the exponent into a temporary before packing the words. */
        asm {
            slwi r6, r6, 20
            or hi, r6, hi
        }
        hi = sign | hi;
    }
zero:
    result.word[0] = hi;
    result.word[1] = lo;
    return (float)result.d;
}
