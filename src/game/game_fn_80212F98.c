typedef unsigned int u32;
typedef void (*DVDLowCallback)(u32 intType);

extern DVDLowCallback Callback_8064D9A0;

volatile u32 __DIRegs[16] : 0xCC006000;

/* Disable cover interrupts and detach the current DVD callback. */
DVDLowCallback DVDLowClearCallback(void) {
    DVDLowCallback callback;

    __DIRegs[1] = 0;
    callback = Callback_8064D9A0;
    Callback_8064D9A0 = 0;
    return callback;
}
