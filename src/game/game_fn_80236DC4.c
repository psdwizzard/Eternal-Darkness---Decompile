typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

typedef struct StreamRequest {
    s32 type;
    s32 size;
    s32 half;
    s32 handle;
    void* buffer;
    void (*callback)();
    s32 field18;
} StreamRequest;

typedef struct Stream {
    s32 handle;
    u8* buffer;
    volatile u32 flags;
    s32 half;
    s32 lastHalf;
    volatile s32 delay;
    volatile u8 curVolume;
    volatile u8 volume;
    volatile u8 newVolume;
    u8 pan;
} Stream;

typedef struct StreamQueue {
    u8 pad0[0x1C];
    s32 usedCount;
} StreamQueue;

typedef struct StreamPool {
    u8 pad0[0x4498];
    StreamRequest requests[0x130];
    u8 thread[0x330];
    StreamQueue queue;
    Stream streams[2];
} StreamPool;

extern StreamPool lbl_80643C20;
extern s32 lbl_8064DC58;
extern s32 lbl_8064DC5C;
extern s32 lbl_8064DC6C;

extern void fn_801BB3A0(s32);
extern void fn_801BAF90(s32);
extern s32 fn_801A9B94(u8, s32);
extern void fn_801BA94C(s32, s32, u8, s32, s32, s32);
extern void fn_801B9E7C(s32, s32, s32, s32, s32);
extern void fn_8020D250(void*, void*, s32);
extern void fn_802101F4(void*, s32);
extern void* memset(void*, int, u32);
extern void DCFlushRange(void*, u32);
extern void fn_80237EAC();

s32 fn_80236DC4(s32 arg0, u32 pos, s32 arg2, s32 arg3, u32 index) {
    StreamPool* pool;
    s32 half;
    s32 prevHalf;
    StreamRequest* req;
    Stream* stream;
    StreamQueue* queue;

    pool = &lbl_80643C20;
    stream = pool->streams;
    stream += index;
    req = pool->requests;
    req += index;
    half = pos >= 0x2000;
    prevHalf = stream->half;

    if (stream->flags & 2) {
        fn_801BB3A0(stream->handle);
        fn_801BAF90(stream->handle);
        stream->flags = 0;
        return 0;
    }

    if (index == 0) {
        if (!(stream->flags & 0x10)) {
            lbl_8064DC58 = pos - (half << 13);
            if (stream->lastHalf != half) {
                lbl_8064DC5C += 0x2000;
                stream->lastHalf = half;
            }
        } else if (stream->lastHalf != half) {
            stream->lastHalf = half;
        }
    }

    if (stream->flags & 4) {
        if (stream->volume != 100) {
            if (stream->flags & 0x80) {
                stream->volume = stream->volume + 20 < 100 ? stream->volume + 20 : 100;
            } else {
                stream->volume = stream->volume + 50 < 100 ? stream->volume + 50 : 100;
            }
        } else {
            stream->flags &= ~0x84;
        }
    } else if ((stream->flags & 8) || (stream->flags & 0x10) || (stream->flags & 0x20)) {
        if (stream->volume != 0) {
            stream->volume = stream->volume - 20 < 0 ? 0 : stream->volume - 20;
        } else if (!(stream->flags & 0x10) && !(stream->flags & 0x20)) {
            req->type = 2;
            req->size = 0;
            req->buffer = 0;
            fn_8020D250(&pool->queue, req, 1);
            stream->flags |= 2;
        }
    }

    {
        Stream* streams = pool->streams;
        streams[1].volume = streams[0].volume;
    }
    stream->newVolume = stream->volume;
    if (stream->curVolume != stream->newVolume) {
        fn_801BA94C(stream->handle, fn_801A9B94(stream->newVolume, 2), stream->pan, 0, 0, 0);
    }
    stream->curVolume = stream->newVolume;

    if (half != prevHalf) {
        if (stream->flags & 0x20) {
            stream->flags |= 0x10;
            stream->flags &= ~0x20;
        }
        if (stream->flags & 0x40) {
            if (stream->delay > 0) {
                stream->delay--;
            } else {
                Stream* streams = pool->streams;
                stream->flags &= ~0x70;
                streams->flags |= 0x84;
            }
        } else {
            stream->delay = 0;
        }

        if (!(stream->flags & 2)) {
            queue = &pool->queue;
            req->buffer = stream->buffer + (stream->half << 14);
            if (queue->usedCount >= 4) {
                lbl_8064DC58 = 0;
                lbl_8064DC5C -= 0x1000;
                memset(req->buffer, 0, 0x4000);
                DCFlushRange(req->buffer, 0x4000);
                fn_801B9E7C(stream->handle, stream->half << 13, 0x2000, 0, 0);
                fn_802101F4(pool->thread, 8);
            } else if (stream->flags == 0 || (stream->flags & 0x10)) {
                if (!(stream->flags & 0x10)) {
                    stream->flags |= 2;
                }
                memset(req->buffer, 0, 0x4000);
                DCFlushRange(req->buffer, 0x4000);
                fn_801B9E7C(stream->handle, stream->half << 13, 0x2000, 0, 0);
            } else {
                req->type = index;
                req->size = 0x2000;
                req->half = stream->half;
                req->handle = stream->handle;
                req->field18 = 0;
                req->callback = fn_80237EAC;
                memset(req->buffer, 0, 0x4000);
                DCFlushRange(req->buffer, 0x4000);
                if (queue->usedCount > 1) {
                    fn_802101F4(pool->thread, 8);
                } else {
                    fn_802101F4(pool->thread, lbl_8064DC6C);
                }
                fn_8020D250(&pool->queue, req, 1);
            }
            stream->half ^= 1;
        }
    }
    return 0;
}
