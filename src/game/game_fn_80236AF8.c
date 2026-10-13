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
    void (*callback)(void); /* 0x14 */
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
extern s32 fn_801BA2A4(int, void*, int, int, int, int, int, int, int, int, int, void (*)(void), int, int);
extern void fn_80236DC4(void);
extern void fn_80237EAC(void);

extern StreamWork lbl_80643C20;
extern s32 lbl_8064D294;
extern s32 lbl_8064DC78;

u8* fn_80236AF8(u8* buffer, s32 arg) {
    StreamWork* work = &lbl_80643C20;
    StreamBuffer* buf;
    StreamRequest* req;
    s32 i;
    int level;

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
    work->buffers[0].handle = fn_801BA2A4(0xFF, work->buffers[0].data, 0x4000, 44100, 0,
                                          work->buffers[0].pan, 0, 0, 0, 0, 0x30000,
                                          fn_80236DC4, 0, 0);
    work->buffers[1].handle = fn_801BA2A4(0xFF, work->buffers[1].data, 0x4000, 44100, 0,
                                          work->buffers[1].pan, 0, 0, 0, 0, 0x30000,
                                          fn_80236DC4, 1, 0);
    OSRestoreInterrupts(level);
    lbl_8064DC78 = 4000;

    req = work->requests;
    buf = work->buffers;
    for (i = 0; i < 2; i++) {
        req->index = i;
        req->size = 0x2000;
        req->data = buf->data;
        req->side = buf->side;
        req->handle = buf->handle;
        req->callback = fn_80237EAC;
        req->arg = arg;
        fn_8020D250(work->queue, req, 1);
        req++;
        buf->side ^= 1;
        buf->flag19 = 0;
        buf->flag18 = 0;
        buf++;
    }
    return buffer;
}
