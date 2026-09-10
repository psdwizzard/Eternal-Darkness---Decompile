typedef unsigned char u8;
typedef unsigned int u32;

typedef union EndianTest {
    u8 bytes[4];
    u32 word;
} EndianTest;

extern int gTRKBigEndian;
extern u8 *gTRKInputPendingPtr;

extern void usr_put_initialize(void);
extern int TRKInitializeEventQueue(void);
extern int TRKInitializeMessageBuffers(void);
extern int TRKInitializeDispatcher(void);
extern int TRKInitializeIntDrivenUART(u32, int, int, u8 **);
extern void TRKTargetSetInputPendingPtr(u8 *);
extern int TRKInitializeSerialHandler(void);
extern int TRKInitializeTarget(void);

static inline int TRKInitializeEndian(void)
{
    EndianTest endian_test;
    int err = 0;

    gTRKBigEndian = 1;
    endian_test.bytes[0] = 0x12;
    endian_test.bytes[1] = 0x34;
    endian_test.bytes[2] = 0x56;
    endian_test.bytes[3] = 0x78;

    if (endian_test.word == 0x12345678) {
        gTRKBigEndian = 1;
    } else if (endian_test.word == 0x78563412) {
        gTRKBigEndian = 0;
    } else {
        err = 1;
    }
    return err;
}

int TRKInitializeNub(void)
{
    int err;
    int uart_err;

    err = TRKInitializeEndian();

    if (err == 0)
        usr_put_initialize();
    if (err == 0)
        err = TRKInitializeEventQueue();
    if (err == 0)
        err = TRKInitializeMessageBuffers();
    if (err == 0)
        err = TRKInitializeDispatcher();
    if (err == 0) {
        uart_err = TRKInitializeIntDrivenUART(0xE100, 1, 0,
                                              &gTRKInputPendingPtr);
        TRKTargetSetInputPendingPtr(gTRKInputPendingPtr);
        if (uart_err != 0)
            err = uart_err;
    }
    if (err == 0)
        err = TRKInitializeSerialHandler();
    if (err == 0)
        err = TRKInitializeTarget();

    return err;
}
