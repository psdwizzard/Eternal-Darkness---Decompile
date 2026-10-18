typedef float Mtx[3][4];

extern float fn_80048C2C(float angle);
extern float fn_80048C50(float angle);
extern void fn_802112D8(Mtx m, unsigned int axis, float sine, float cosine);

/* Build an affine rotation about the selected axis from an angle in radians. */
void fn_80211268(register Mtx m, register unsigned int axis, register float angle)
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
    sine = fn_80048C2C(argument);
    cosine = fn_80048C50(radians);
    fn_802112D8(matrix, selectedAxis, sine, cosine);
    /* The return block leaves the function; the loop suppresses a second
     * compiler-generated epilogue. */
    for (;;) {
        /* ASM: lwz, lfd, mtlr, addi and blr restore the caller's state in
         * retail order; C schedules mtlr after the stack adjustment. */
        asm {
            lwz r0, 0x2c(r1)
            lfd radians, 0x20(r1)
            lwz selectedAxis, 0x1c(r1)
            mtlr r0
            lwz matrix, 0x18(r1)
            addi r1, r1, 0x28
            blr
        }
    }
}
