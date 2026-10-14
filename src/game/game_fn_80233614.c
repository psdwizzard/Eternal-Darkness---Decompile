extern void *fn_8022F780(int size);
extern void *memcpy(void *destination, const void *source, unsigned long size);

/* Allocate and copy the fixed-size configuration. */
void *fn_80233614(register const void *source) {
    register void *savedPointer;
    register void *copy;

    /* ASM: or (mr) copies the source pointer; C selects addi with zero. */
    asm { or savedPointer, source, source }
    copy = fn_8022F780(0xCD0);
    {
        register const void *copySource;
        /* ASM: or (mr) moves the call arguments and reuses the saved pointer
         * register; C selects addi with zero and separate saved registers. */
        asm {
            or copySource, savedPointer, savedPointer
            or savedPointer, copy, copy
        }
        memcpy(copy, copySource, 0xCD0);
    }
    return savedPointer;
}
