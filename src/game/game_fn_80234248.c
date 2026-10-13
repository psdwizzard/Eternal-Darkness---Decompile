/* Eight-point MDCT butterfly. */
void fn_80234248(float *x)
{
    float r0 = x[6] + x[2];
    float r1 = x[6] - x[2];
    float r2 = x[4] + x[0];
    float r3 = x[4] - x[0];

    x[6] = r0 + r2;
    x[4] = r0 - r2;

    r0 = x[5] - x[1];
    r2 = x[7] - x[3];
    x[0] = r1 + r0;
    x[2] = r1 - r0;

    r0 = x[5] + x[1];
    r1 = x[7] + x[3];
    x[3] = r2 + r3;
    x[1] = r2 - r3;
    x[7] = r1 + r0;
    x[5] = r1 - r0;
}
