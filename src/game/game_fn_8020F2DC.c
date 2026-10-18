typedef struct OSThread OSThread;

/* Return the current thread from the OS low-memory globals. */
OSThread *OSGetCurrentThread(void) {
    return *(OSThread **)0x800000E4;
}
