/* Sixteen-point MDCT butterfly, followed by two eight-point butterflies. */

extern const float lbl_80651844;

void mdct_butterfly_8(float *data);

void mdct_butterfly_16(register float *p) {
    register float *saved;
    float r = lbl_80651844;

    /* ASM: mr keeps the working pointer in r3 and a separate saved pointer
     * across the calls. MWCC coalesces an ordinary C copy into one register. */
    asm { mr saved, p }

    {
        float im;
        float re;
        re = p[0] - p[8];
        im = p[1] - p[9];
        p[8] += p[0];
        p[9] = p[9] + p[1];
        p[0] = r * (im + re);
        p[1] = r * (im - re);
    }

    {
        float im;
        float re;
        im = p[3] - p[11];
        re = p[10] - p[2];
        p[10] += p[2];
        p[11] = p[11] + p[3];
        p[2] = im;
        p[3] = re;
    }

    {
        float re;
        float im;
        re = p[12] - p[4];
        im = p[13] - p[5];
        p[12] += p[4];
        p[13] = p[13] + p[5];
        p[4] = r * (re - im);
        p[5] = r * (re + im);
    }

    {
        float re;
        float im;
        re = p[14] - p[6];
        im = p[15] - p[7];
        p[14] += p[6];
        p[15] = p[15] + p[7];
        p[6] = re;
        p[7] = im;
    }

    mdct_butterfly_8(p);
    mdct_butterfly_8(saved + 8);
}
