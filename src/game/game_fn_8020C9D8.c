typedef struct OSContext OSContext;
typedef void (*OSInterruptHandler)(short interrupt, OSContext *context);

extern OSInterruptHandler *InterruptHandlerTable_8064D938;

OSInterruptHandler fn_8020C9D8(short interrupt) {
    return InterruptHandlerTable_8064D938[interrupt];
}
