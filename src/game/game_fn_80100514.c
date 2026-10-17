/* fn_80100514: fdlibm __kernel_rem_pio2 (MSL k_rem_pio2.c).
 * Reduces x (given as 24-bit chunks) modulo pi/2 to high precision. */

extern double fn_80101A5C(double x);        /* floor */
extern double fn_80101C30(double x, int n); /* scalbn */

extern const int lbl_8023A0A8[];    /* init_jk */
extern const double lbl_8023A0B8[]; /* PIo2 */
extern const double lbl_8064FD18; /* 0.0 */
extern const double lbl_8064FD20; /* 2^-24 */
extern const double lbl_8064FD28; /* 2^24 */
extern const double lbl_8064FD30; /* 8.0 */
extern const double lbl_8064FD38; /* 0.125 */
extern const double lbl_8064FD40; /* 0.5 */
extern const double lbl_8064FD48; /* 1.0 */

static const double two24 = 1.67772160000000000000e+07;
static const double twon24 = 5.96046447753906250000e-08;

#define init_jk lbl_8023A0A8
#define PIo2 lbl_8023A0B8
#define one lbl_8064FD48
/* Preserve the separate shared-zero loads at these initialization sites. */
#define READ_ZERO() (*(volatile const double *)&lbl_8064FD18)

int fn_80100514(double *x, double *y, int e0, int nx, int prec, const int *ipio2)
{
    int jz, jx, jv, jp, jk, carry, n, iq[20], i, j, k, m, q0, ih;
    register double testZero;
    double inverseChunk, z, fw, f[20], fq[20], q[20];

    /* initialize jk */
    jk = init_jk[prec];
    jp = jk;

    /* determine jx,jv,q0, note that 3>q0 */
    jx = nx - 1;
    jv = (e0 - 3) / 24;
    if (jv < 0) jv = 0;
    q0 = e0 - 24 * (jv + 1);

    /* set up f[0] to f[jx+jk] where f[jx+jk] = ipio2[jv+jk] */
    j = jv - jx;
    m = jx + jk;
    for (i = 0; i <= m; i++, j++)
        f[i] = (j < 0) ? READ_ZERO() : (double)ipio2[j];

    /* compute q[0],q[1],...q[jk] */
    for (i = 0; i <= jk; i++) {
        for (j = 0, fw = READ_ZERO(); j <= jx; j++)
            fw += x[j] * f[jx + i - j];
        q[i] = fw;
    }

    inverseChunk = lbl_8064FD20;
    jz = jk;
recompute:
    /* distill q[] into iq[] reversingly */
    for (i = 0, j = jz, z = q[jz]; j > 0; i++, j--) {
        fw = (double)((int)(inverseChunk * z));
        iq[i] = (int)(z - two24 * fw);
        z = q[j - 1] + fw;
    }

    /* compute n */
    z = fn_80101C30(z, q0);            /* actual value of z */
    z -= lbl_8064FD30 * fn_80101A5C(lbl_8064FD38 * z); /* trim off integer >= 8 */
    n = (int)z;
    z -= (double)n;
    ih = 0;
    if (q0 > 0) { /* need iq[jz-1] to determine n */
        i = (iq[jz - 1] >> (24 - q0));
        n += i;
        iq[jz - 1] -= i << (24 - q0);
        ih = iq[jz - 1] >> (23 - q0);
    } else if (q0 == 0) {
        ih = iq[jz - 1] >> 23;
    } else if (z >= lbl_8064FD40) {
        ih = 2;
    }

    if (ih > 0) { /* q > 0.5 */
        n += 1;
        carry = 0;
        for (i = 0; i < jz; i++) { /* compute 1-q */
            j = iq[i];
            if (carry == 0) {
                if (j != 0) {
                    carry = 1;
                    iq[i] = 0x1000000 - j;
                }
            } else {
                iq[i] = 0xffffff - j;
            }
        }
        if (q0 > 0) { /* rare case: chance is 1 in 12 */
            switch (q0) {
            case 1:
                iq[jz - 1] &= 0x7fffff;
                break;
            case 2:
                iq[jz - 1] &= 0x3fffff;
                break;
            }
        }
        if (ih == 2) {
            z = one - z;
            if (carry != 0) z -= fn_80101C30(one, q0);
        }
    }

    /* check if recomputation is needed */
    if (lbl_8064FD18 == z) {
        j = 0;
        for (i = jz - 1; i >= jk; i--) j |= iq[i];
        if (j == 0) { /* need recomputation */
            for (k = 1; iq[jk - k] == 0; k++)
                ; /* k = no. of terms needed */

            for (i = jz + 1; i <= jz + k; i++) { /* add q[jz+1] to q[jz+k] */
                f[jx + i] = (double)ipio2[jv + i];
                for (j = 0, fw = READ_ZERO(); j <= jx; j++)
                    fw += x[j] * f[jx + i - j];
                q[i] = fw;
            }
            jz += k;
            goto recompute;
        }
    }

    /* chop off zero terms */
    testZero = READ_ZERO();
    if (testZero == z) {
        jz -= 1;
        q0 -= 24;
        while (iq[jz] == 0) {
            jz--;
            q0 -= 24;
        }
    } else { /* break z into 24-bit if necessary */
        z = fn_80101C30(z, -q0);
        if (z >= lbl_8064FD28) {
            fw = (double)((int)(lbl_8064FD20 * z));
            iq[jz] = (int)(z - lbl_8064FD28 * fw);
            jz += 1;
            q0 += 24;
            iq[jz] = (int)fw;
        } else {
            iq[jz] = (int)z;
        }
    }

    /* convert integer "bit" chunk to floating-point value */
    fw = fn_80101C30(one, q0);
    for (i = jz; i >= 0; i--) {
        q[i] = fw * (double)iq[i];
        fw *= twon24;
    }

    /* compute PIo2[0,...,jp]*q[jz,...,0] */
    for (i = jz; i >= 0; i--) {
        for (fw = READ_ZERO(), k = 0; k <= jp && k <= jz - i; k++)
            fw += PIo2[k] * q[i + k];
        fq[jz - i] = fw;
    }

    /* compress fq[] into y[] */
    switch (prec) {
    case 0:
        fw = lbl_8064FD18;
        for (i = jz; i >= 0; i--) fw += fq[i];
        y[0] = (ih == 0) ? fw : -fw;
        break;
    case 1:
    case 2:
        fw = lbl_8064FD18;
        for (i = jz; i >= 0; i--) fw += fq[i];
        y[0] = (ih == 0) ? fw : -fw;
        fw = fq[0] - fw;
        for (i = 1; i <= jz; i++) fw += fq[i];
        y[1] = (ih == 0) ? fw : -fw;
        break;
    case 3: /* painful */
        for (i = jz; i > 0; i--) {
            fw = fq[i - 1] + fq[i];
            fq[i] += fq[i - 1] - fw;
            fq[i - 1] = fw;
        }
        for (i = jz; i > 1; i--) {
            fw = fq[i - 1] + fq[i];
            fq[i] += fq[i - 1] - fw;
            fq[i - 1] = fw;
        }
        for (fw = lbl_8064FD18, i = jz; i >= 2; i--) fw += fq[i];
        if (ih == 0) {
            y[0] = fq[0];
            y[1] = fq[1];
            y[2] = fw;
        } else {
            y[0] = -fq[0];
            y[1] = -fq[1];
            y[2] = -fw;
        }
    }
    return n & 7;
}
