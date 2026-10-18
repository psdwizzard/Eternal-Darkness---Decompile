/* mdct_butterfly_first: first-stage MDCT butterfly (libvorbis mdct_butterfly_first). */

void mdct_butterfly_first(float *T, float *x, int points) {
    float *x1 = x + points - 8;
    float *x2 = x + (points >> 1) - 8;
    float r0;
    float r1;

    do {
        r0 = x1[6] - x2[6];
        r1 = x1[7] - x2[7];
        x1[6] += x2[6];
        x1[7] += x2[7];
        x2[6] = r1 * T[1] + r0 * T[0];
        x2[7] = r1 * T[0] - r0 * T[1];

        r0 = x1[4] - x2[4];
        r1 = x1[5] - x2[5];
        x1[4] += x2[4];
        x1[5] += x2[5];
        x2[4] = r1 * T[5] + r0 * T[4];
        x2[5] = r1 * T[4] - r0 * T[5];

        r0 = x1[2] - x2[2];
        r1 = x1[3] - x2[3];
        x1[2] += x2[2];
        x1[3] += x2[3];
        x2[2] = r1 * T[9] + r0 * T[8];
        x2[3] = r1 * T[8] - r0 * T[9];

        r0 = x1[0] - x2[0];
        r1 = x1[1] - x2[1];
        x1[0] += x2[0];
        x1[1] += x2[1];
        x2[0] = r1 * T[13] + r0 * T[12];
        x2[1] = r1 * T[12] - r0 * T[13];

        x1 -= 8;
        x2 -= 8;
        T += 16;
    } while (x2 >= x);
}
