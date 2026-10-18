typedef void (*AIDMACallback)(void);

extern void *__CallbackStack; /* Audio DMA callback stack. */
extern void *__OldStack; /* Interrupted stack pointer. */

/* Run the DMA callback on its dedicated stack. */
void __AICallbackStackSwitch(register AIDMACallback callback)
{
    /* ASM: mr, lis, addi, stw, lis, addi, lwz, subi capture the callback
     * before saving and replacing r1. C cannot express a stack switch
     * with the callback capture ordered inside it. */
    asm {
        mr callback, r3
        lis r5, __OldStack@ha
        addi r5, r5, __OldStack@l
        stw r1, 0(r5)
        lis r5, __CallbackStack@ha
        addi r5, r5, __CallbackStack@l
        lwz r1, 0(r5)
        subi r1, r1, 8
    }

    callback();

    /* ASM: mr marks r31 as used so the interrupted stack frame preserves it.
     * C cannot request preservation of a particular nonvolatile register.
     * The compiler removes the self-move after constructing the frame. */
    asm { mr r31, r31 }

    /* ASM: lis, addi, lwz restore r1 after the callback.
     * C cannot restore the active stack pointer. */
    asm {
        lis r5, __OldStack@ha
        addi r5, r5, __OldStack@l
        lwz r1, 0(r5)
    }
}
