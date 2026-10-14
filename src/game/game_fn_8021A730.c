typedef void (*AIDMACallback)(void);

extern void *lbl_8064DAE0; /* Audio DMA callback stack. */
extern void *lbl_8064DAE4; /* Interrupted stack pointer. */

/* Run the DMA callback on its dedicated stack. */
void fn_8021A730(register AIDMACallback callback)
{
    /* ASM: mr, lis, addi, stw, lis, addi, lwz, subi capture the callback
     * before saving and replacing r1. C cannot express a stack switch
     * with the callback capture ordered inside it. */
    asm {
        mr callback, r3
        lis r5, lbl_8064DAE4@ha
        addi r5, r5, lbl_8064DAE4@l
        stw r1, 0(r5)
        lis r5, lbl_8064DAE0@ha
        addi r5, r5, lbl_8064DAE0@l
        lwz r1, 0(r5)
        subi r1, r1, 8
    }

    callback();

    /* ASM: lis, addi, lwz restore r1 after the callback.
     * C cannot restore the active stack pointer. */
    asm {
        lis r5, lbl_8064DAE4@ha
        addi r5, r5, lbl_8064DAE4@l
        lwz r1, 0(r5)
    }
}
