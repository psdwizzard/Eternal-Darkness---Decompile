typedef float Mtx[3][4];

extern float sinf(float angle);
extern float cosf(float angle);
extern void PSMTXRotTrig(Mtx m, unsigned int axis, float sine, float cosine);

/* Build an affine rotation about the selected axis from an angle in radians. */
void PSMTXRotRad(register Mtx m, register unsigned int axis, register float angle)
{
    register unsigned int selectedAxis;
    register float (*matrix)[4];
    register float radians;
    register float argument;
    float sine;
    float cosine;

    /* ASM: fmr and mr retain the retail register copies; C folds these
     * copies and selects addi for the integer argument moves. */
    asm {
        fmr radians, angle
        mr matrix, m
        mr selectedAxis, axis
        fmr argument, radians
    }
    sine = sinf(argument);
    cosine = cosf(radians);
    PSMTXRotTrig(matrix, selectedAxis, sine, cosine);
}
