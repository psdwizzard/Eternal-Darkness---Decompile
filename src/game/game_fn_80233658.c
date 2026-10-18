/* mdct_backward: inverse MDCT (libvorbis mdct_backward). */

typedef struct mdct_lookup {
    int n;
    int log2n;
    float *trig;
    int *bitrev;
    float scale;
} mdct_lookup;

void mdct_butterflies(mdct_lookup *init, float *x);  /* mdct_butterflies */
void mdct_bitreverse(mdct_lookup *init, float *x);  /* mdct_bitreverse */

void mdct_backward(mdct_lookup *init, float *in, float *out) {
    int n = init->n;
    int n2 = n >> 1;
    int n4 = n >> 2;

    /* rotate */
    float *T = init->trig + n4;
    float *iX = in + n2 - 7;
    float *oX = out + n2 + n4;

    do {
        oX[-4] = -iX[2] * T[3] - iX[0] * T[2];
        oX[-3] = iX[0] * T[3] - iX[2] * T[2];
        oX[-2] = -iX[6] * T[1] - iX[4] * T[0];
        oX[-1] = iX[4] * T[1] - iX[6] * T[0];
        iX -= 8;
        T += 4;
        oX -= 4;
    } while (iX >= in);

    T = init->trig + n4;
    iX = in + n2 - 8;
    oX = out + n2 + n4;

    do {
        T -= 4;
        oX[0] = iX[4] * T[3] + iX[6] * T[2];
        oX[1] = iX[4] * T[2] - iX[6] * T[3];
        oX[2] = iX[0] * T[1] + iX[2] * T[0];
        oX[3] = iX[0] * T[0] - T[1] * iX[2];
        iX -= 8;
        oX += 4;
    } while (iX >= in);

    mdct_butterflies(init, out + n2);
    mdct_bitreverse(init, out);

    /* rotate + window */
    {
        float *oX1 = out + n2 + n4;
        float *oX2 = out + n2 + n4;
        float *iX = out;
        T = init->trig + n2;

        do {
            oX1 -= 4;

            oX1[3] = iX[0] * T[1] - iX[1] * T[0];
            oX2[0] = -(iX[0] * T[0] + iX[1] * T[1]);

            oX1[2] = iX[2] * T[3] - iX[3] * T[2];
            oX2[1] = -(iX[2] * T[2] + iX[3] * T[3]);

            oX1[1] = iX[4] * T[5] - iX[5] * T[4];
            oX2[2] = -(iX[4] * T[4] + iX[5] * T[5]);

            oX1[0] = iX[6] * T[7] - iX[7] * T[6];
            oX2[3] = -(iX[6] * T[6] + iX[7] * T[7]);

            oX2 += 4;
            iX += 8;
            T += 8;
        } while (iX < oX1);

        iX = out + n2 + n4;
        oX1 = out + n4;
        oX2 = oX1;

        do {
            oX1 -= 4;
            iX -= 4;

            oX2[0] = -(oX1[3] = iX[3]);
            oX2[1] = -(oX1[2] = iX[2]);
            oX2[2] = -(oX1[1] = iX[1]);
            oX2[3] = -(oX1[0] = iX[0]);

            oX2 += 4;
        } while (oX2 < iX);

        iX = out + n2 + n4;
        oX1 = out + n2 + n4;
        oX2 = out + n2;
        do {
            oX1[-4] = iX[3];
            oX1[-3] = iX[2];
            oX1[-2] = iX[1];
            oX1[-1] = iX[0];
            iX += 4;
            oX1 -= 4;
        } while (oX1 > oX2);
    }
}
