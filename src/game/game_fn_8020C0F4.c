typedef unsigned int u32;

/* OSGetStackPointer: return the current stack frame for stack traversal. */
u32 *OSGetStackPointer(void)
{
    register u32 *stackPointer;

    /* ASM: mr reads the ABI stack pointer in r1, which C cannot access. */
    asm { mr stackPointer, r1 }
    return stackPointer;
}
