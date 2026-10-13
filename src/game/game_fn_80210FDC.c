typedef float Mtx[3][4];

/* Concatenate two affine matrices: ab = a * b. The implicit fourth row of
 * each operand is (0, 0, 0, 1), so only a's last column adds translation. */
void fn_80210FDC(const Mtx a, const Mtx b, Mtx ab)
{
    int i;

    for (i = 0; i < 3; i++) {
        float a0 = a[i][0];
        float a1 = a[i][1];
        float a2 = a[i][2];
        float a3 = a[i][3];

        ab[i][0] = a0 * b[0][0] + a1 * b[1][0] + a2 * b[2][0];
        ab[i][1] = a0 * b[0][1] + a1 * b[1][1] + a2 * b[2][1];
        ab[i][2] = a0 * b[0][2] + a1 * b[1][2] + a2 * b[2][2];
        ab[i][3] = a0 * b[0][3] + a1 * b[1][3] + a2 * b[2][3] + a3;
    }
}
