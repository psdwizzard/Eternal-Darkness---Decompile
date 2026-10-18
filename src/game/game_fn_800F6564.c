/* Saved context shared with fn_800F6460 (setjmp).
 * This remains an incomplete longjmp implementation: restoring LR, CR,
 * r1/r2, r13-r31 and f14-f31 (including their paired-single lanes) requires
 * architecture-specific code beyond this unit's permitted assembly budget.
 * Only the floating-point status and return-value normalization are below.
 */
typedef struct SavedContext {
    unsigned int lr;
    unsigned int cr;
    unsigned int sp;
    unsigned int r2;
    unsigned int reserved;
    unsigned int gpr[19];
    struct {
        double scalar;
        double paired;
    } fpr[18];
    double fpscr;
} SavedContext;

int fn_800F6564(const SavedContext* context, int value) {
    register double status = context->fpscr;
    int nonzero = value != 0;

    /* ASM: mtfsf restores every FPSCR field from the saved bit pattern;
     * standard C cannot assign the processor's floating-point status. */
    asm { mtfsf 255, status }
    if (!nonzero) {
        value = 1;
    }
    return value;
}
