typedef struct OSContext OSContext;

/* Return the current OS context stored in low memory. */
OSContext *fn_8020BF90(void) {
    return *(OSContext *volatile *)0x800000D4;
}
