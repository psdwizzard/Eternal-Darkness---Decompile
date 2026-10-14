typedef unsigned short OSError;
typedef struct OSContext OSContext;
typedef void (*OSErrorHandler)(OSError error, OSContext* context, ...);

extern OSErrorHandler __OSErrorTable[];

OSErrorHandler OSSetErrorHandler(OSError error, OSErrorHandler handler) {
    OSErrorHandler previous = __OSErrorTable[error];

    __OSErrorTable[error] = handler;
    return previous;
}
