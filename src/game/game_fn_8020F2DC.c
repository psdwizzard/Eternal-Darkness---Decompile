typedef struct OSThread OSThread;

/* Return the current thread from the OS low-memory globals. */
OSThread *fn_8020F2DC(void) {
    return *(OSThread **)0x800000E4;
}
