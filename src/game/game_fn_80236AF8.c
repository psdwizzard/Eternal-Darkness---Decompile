typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;

typedef struct StreamBuffer {
    s32 handle;   /* 0x00 */
    u8* data;     /* 0x04 */
    s32 state;    /* 0x08 */
    s32 side;     /* 0x0C */
    s32 pos;      /* 0x10 */
    u8 pad14[4];  /* 0x14 */
    u8 flag18;    /* 0x18 */
    u8 flag19;    /* 0x19 */
    u8 pad1A;     /* 0x1A */
    u8 pan;       /* 0x1B */
} StreamBuffer;

typedef struct StreamRequest {
    s32 index;    /* 0x00 */
    s32 size;     /* 0x04 */
    s32 side;     /* 0x08 */
    s32 handle;   /* 0x0C */
    u8* data;     /* 0x10 */
    void (*callback)(u32, u32); /* 0x14 */
    s32 arg;      /* 0x18 */
} StreamRequest;

typedef struct StreamWork {
    u8 pad0[0x4498];
    StreamRequest requests[2]; /* 0x4498 */
    u8 pad44D0[0x6908 - 0x44D0];
    u8 queue[0x20];            /* 0x6908 */
    StreamBuffer buffers[2];   /* 0x6928 */
} StreamWork;

extern void fn_801ADCF8(void);
extern void fn_80217324(void);
extern int fn_8020D318(void*, void**, int);
extern int fn_8020D250(void*, void*, int);
extern void* memset(void*, int, unsigned long);
extern void DCFlushRange(void*, u32);
extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int);
extern u32 fn_801BA2A4(u8, u32, u32, u32, u8, u8, u8, u8, u8, u8, u32, void (*)(void), u32, short*);
extern s32 fn_80236DC4(s32, u32, s32, s32, u32);
extern void fn_80237EAC(u32, u32);

extern StreamWork lbl_80643C20;
extern s32 lbl_8064D294;
extern s32 lbl_8064DC78;

u8* fn_80236AF8(register u8* buffer, register s32 arg) {
    StreamWork* work = &lbl_80643C20;
    StreamBuffer* buf;
    StreamBuffer* stream;
    StreamRequest* req;
    s32 i, j;
    int level;

    /* ASM: or (mr) preserves the incoming argument copies; MWCC emits addi with zero for C copies. */
    asm {
        or buffer, buffer, buffer
        or arg, arg, arg
    }
    fn_801ADCF8();
    fn_80217324();
    while (fn_8020D318(work->queue, 0, 0) != 0) {
    }

    buf = work->buffers;
    for (i = 0; i < 2; i++) {
        buf->data = buffer;
        buffer += 0x8000;
        buf->side = 0;
        buf->pos = 0;
        buf->flag19 = 0;
        buf->flag18 = 0;
        buf->state = 1;
        memset(buf->data, 0, 0x8000);
        DCFlushRange(buf->data, 0x8000);
        buf++;
    }

    level = OSDisableInterrupts();
    if (lbl_8064D294 == 0) {
        work->buffers[0].pan = 0x40;
        work->buffers[1].pan = 0x40;
    } else {
        work->buffers[0].pan = 0;
        work->buffers[1].pan = 0x7F;
    }
    {
        register u32 zero, rateHigh, rate, flags, callbackAddress;
        register void (*callback)(void);
        zero = 0;
        /* ASM: lis and addi rematerialize this call's constants; C hoists them across both calls into saved registers. */
        asm {
            lis callbackAddress, fn_80236DC4@ha
            lis rateHigh, 1
            addi rate, rateHigh, -21436
            lis flags, 3
            addi callback, callbackAddress, fn_80236DC4@l
        }
        work->buffers[0].handle = fn_801BA2A4(0xFF, (u32)work->buffers[0].data, 0x4000, rate, 0,
                                          work->buffers[0].pan, 0, 0, zero, zero, flags,
                                          callback, zero, (short*)zero);
    }
    {
        register u32 zero, rateHigh, rate, flags, callbackAddress;
        register void (*callback)(void);
        zero = 0;
        /* ASM: lis and addi rematerialize this call's constants; C hoists them across both calls into saved registers. */
        asm {
            lis callbackAddress, fn_80236DC4@ha
            lis rateHigh, 1
            addi rate, rateHigh, -21436
            lis flags, 3
            addi callback, callbackAddress, fn_80236DC4@l
        }
        work->buffers[1].handle = fn_801BA2A4(0xFF, (u32)work->buffers[1].data, 0x4000, rate, 0,
                                          work->buffers[1].pan, 0, 0, zero, zero, flags,
                                          callback, 1, (short*)zero);
    }
    OSRestoreInterrupts(level);
    lbl_8064DC78 = 4000;

    req = work->requests;
    stream = work->buffers;
    for (j = 0; j < 2; j++) {
        req->index = j;
        req->size = 0x2000;
        req->arg = arg;
        req->data = stream->data;
        req->side = stream->side;
        req->handle = stream->handle;
        req->callback = fn_80237EAC;
        fn_8020D250(work->queue, req, 1);
        req++;
        stream->side ^= 1;
        stream->flag19 = 0;
        stream->flag18 = 0;
        stream++;
    }
    return buffer;
}
