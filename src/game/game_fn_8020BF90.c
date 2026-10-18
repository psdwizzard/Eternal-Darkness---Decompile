typedef struct OSContext OSContext;

/* Return the current OS context stored in low memory. */
OSContext *OSGetCurrentContext(void) {
    return *(OSContext *volatile *)0x800000D4;
}
