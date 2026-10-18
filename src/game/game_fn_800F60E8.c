/* Signed 64-bit remainder. The four ABI words are two 64-bit operands. */
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;

s64 __mod2i(register u32 ah, register u32 al, register u32 bh, register u32 bl) {
    register u32 rh, rl;
    register u32 tl, th;
    int za, zb;
    int zal, zbl;
    register int count;
    int shift;
    register u32 minus_one, carry_out;
    /* ASM: cmpwi/bge retain the original sign in CR7 across the C loop. */
    asm {
        cmpwi cr7, ah, 0
        bge cr7, dividend_ready
    }
    {
        u64 magnitude = -(((u64)(u32)ah << 32) | al);
        ah = (u32)(magnitude >> 32);
        al = (u32)magnitude;
    }
dividend_ready:
    ;
    if ((s32)bh < 0) {
        u64 magnitude = -(((u64)(u32)bh << 32) | bl);
        bh = (u32)(magnitude >> 32);
        bl = (u32)magnitude;
    }

    za = __cntlzw(ah);
    zal = __cntlzw(al);
    if ((s32)ah == 0) {
        za = zal + 32;
    }
    zb = __cntlzw(bh);
    zbl = __cntlzw(bl);
    if ((s32)bh == 0) {
        zb = zbl + 32;
    }
    if (za <= zb) {
        int right_shift = 64 - ++zb;
        shift = za + right_shift;
        count = 64 - shift;
        /* ASM: mtctr keeps the loop count outside the carry flag. */
        asm { mtctr count }

        {
            int over = count - 32;
            if (count >= 32) {
                rl = ah >> over;
                rh = 0;
            } else {
                int under;
                rl = al >> count;
                under = 32 - count;
                rl |= ah << under;
                rh = ah >> count;
            }
        }
        {
            int over = shift - 32;
            if (shift >= 32) {
                ah = al << over;
                al = 0;
            } else {
                ah = (ah << shift) | (al >> (32 - shift));
                al <<= shift;
            }
        }

        minus_one = -1;
        /* ASM: addic seeds the carry for the first division step. */
        asm { addic rh, rh, 0 }
division_step:
        {
            /* ASM: adde and subfc/subfe preserve carry across all four words. */
            asm {
                adde al, al, al
                adde ah, ah, ah
                adde rl, rl, rl
                adde rh, rh, rh
                subfc tl, bl, rl
                subfe. th, bh, rh
            }
            /* ASM: blt uses the signed result from subfe. without changing CA. */
            asm { blt no_subtract }
            rl = tl;
            rh = th;
            /* ASM: addic sets the carry for the next quotient bit. */
            asm { addic carry_out, minus_one, 1 }
no_subtract:
            ;
        }
        /* ASM: bdnz repeats without changing the carry flag. */
        asm { bdnz division_step }
        al = rl;
        ah = rh;
    }
    /* ASM: bgelr/subfic/subfze reuse CR7 without materializing the saved sign. */
    asm {
        bgelr cr7
        subfic al, al, 0
        subfze ah, ah
    }
    return ((s64)ah << 32) | al;
}
