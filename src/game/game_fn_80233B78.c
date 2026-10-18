/* mdct_butterfly_generic: libvorbis-style mdct_butterfly_generic. */

void mdct_butterfly_generic(float *T, float *x, int points, int trigint) {
    float *x1;
    float *x2;
    float r0;
    float r1;

    x1 = x + points - 8;
    x2 = x + (points >> 1) - 8;

    do {
        r0 = x1[6] - x2[6];
        r1 = x1[7] - x2[7];
        x1[6] += x2[6];
        x1[7] += x2[7];
        x2[6] = r1 * T[1] + r0 * T[0];
        x2[7] = r1 * T[0] - r0 * T[1];
        T += trigint;

        r0 = x1[4] - x2[4];
        r1 = x1[5] - x2[5];
        x1[4] += x2[4];
        x1[5] += x2[5];
        x2[4] = r1 * T[1] + r0 * T[0];
        x2[5] = r1 * T[0] - r0 * T[1];
        T += trigint;

        r0 = x1[2] - x2[2];
        r1 = x1[3] - x2[3];
        x1[2] += x2[2];
        x1[3] += x2[3];
        x2[2] = r1 * T[1] + r0 * T[0];
        x2[3] = r1 * T[0] - r0 * T[1];
        T += trigint;

        r0 = x1[0] - x2[0];
        r1 = x1[1] - x2[1];
        x1[0] += x2[0];
        x1[1] += x2[1];
        x2[0] = r1 * T[1] + r0 * T[0];
        x2[1] = r1 * T[0] - r0 * T[1];
        T += trigint;

        x1 -= 8;
        x2 -= 8;
    } while (x2 >= x);
}
