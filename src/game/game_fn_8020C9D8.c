typedef struct OSContext OSContext;
typedef void (*OSInterruptHandler)(short interrupt, OSContext *context);

extern OSInterruptHandler *InterruptHandlerTable_8064D938;

OSInterruptHandler __OSGetInterruptHandler(short interrupt) {
    return InterruptHandlerTable_8064D938[interrupt];
}
