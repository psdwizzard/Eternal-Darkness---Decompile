typedef struct OSContext OSContext;
typedef void (*OSInterruptHandler)(short interrupt, OSContext *context);

extern OSInterruptHandler *InterruptHandlerTable_8064D938;

OSInterruptHandler __OSSetInterruptHandler(short interrupt, OSInterruptHandler handler) {
    OSInterruptHandler previous;

    previous = InterruptHandlerTable_8064D938[interrupt];
    InterruptHandlerTable_8064D938[interrupt] = handler;
    return previous;
}
