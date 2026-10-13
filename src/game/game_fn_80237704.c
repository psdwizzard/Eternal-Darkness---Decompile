typedef unsigned int u32;
typedef signed int s32;
typedef signed short s16;

typedef void (*StreamCallback)(s32, s32);

typedef struct StreamChannel {
    s32 type;
    u32 count;
    s32 arg8;
    s32 argC;
    s16 *buffer;
    StreamCallback callback;
    void *message;
} StreamChannel;

typedef struct StreamWork {
    char pad0[0x44D0];
    StreamChannel right;
    StreamChannel left;
    char pad4508[0x6908 - 0x4508];
    char queue[1];
} StreamWork;

extern void fn_800F9FE4(const char *fmt, ...);
extern int fn_8020D318(void *queue, void *msg, int block);
extern void fn_8020D250(void *queue, void *msg, int block);
extern void DCFlushRange(void *addr, u32 size);

extern char lbl_8023B8EC[];
extern StreamWork lbl_80643C20;
extern s32 lbl_8064DC34;
extern s32 lbl_8064DC3C;
extern s32 lbl_8064DC4C;
extern s32 lbl_8064DC54;
extern s32 lbl_8064DC78;

s32 fn_80237704(s16 *src, s32 samples, s32 mode) {
    StreamWork *work = &lbl_80643C20;
    StreamChannel *left;
    StreamChannel *right;
    s16 *leftBuf;
    s16 *rightBuf;
    StreamChannel *msg;
    StreamChannel *m;
    s32 count;
    s32 remaining;
    s32 i;
    u32 avail;

    if (lbl_8064DC4C == 2) {
        fn_800F9FE4(lbl_8023B8EC);
        return 1;
    }

    left = &work->left;
    right = &work->right;
    remaining = samples + lbl_8064DC78;
    do {
        if (lbl_8064DC3C == 0) {
            left->buffer = 0;
            right->buffer = 0;
            while (left->buffer == 0 || right->buffer == 0) {
                if (fn_8020D318(work->queue, &msg, 0) == 0) {
                    fn_8020D318(work->queue, &msg, 1);
                }
                m = msg;
                switch (m->type) {
                case 0:
                    work->left = *m;
                    break;
                case 1:
                    work->right = *m;
                    break;
                case 2:
                    lbl_8064DC54 = 0;
                    if (++lbl_8064DC4C == 2) {
                        return 1;
                    }
                    break;
                }
                avail = m->count;
                if (avail < (u32)lbl_8064DC3C) {
                    avail = lbl_8064DC3C;
                }
                lbl_8064DC3C = avail;
            }
        }

        count = remaining;
        if (lbl_8064DC3C < remaining) {
            count = lbl_8064DC3C;
        }
        leftBuf = left->buffer;
        rightBuf = right->buffer;
        if (mode == 2) {
            for (i = 0; i < count; i++) {
                if (i < lbl_8064DC78) {
                    *leftBuf++ = 0;
                    *rightBuf++ = 0;
                } else {
                    *leftBuf++ = src[0];
                    *rightBuf++ = src[1];
                    src += 2;
                }
            }
            DCFlushRange(left->buffer, count * 2);
            DCFlushRange(right->buffer, count * 2);
        }
        remaining -= count;
        left->buffer = leftBuf;
        lbl_8064DC78 -= count;
        right->buffer = rightBuf;
        lbl_8064DC3C -= count;
        if (lbl_8064DC78 < 0) {
            lbl_8064DC78 = 0;
        }
        if (lbl_8064DC3C == 0) {
            if (right->callback != 0) {
                right->callback(right->argC, right->arg8);
            }
            if (left->callback != 0) {
                left->callback(left->argC, left->arg8);
            }
            if (left->message != 0) {
                fn_8020D250(left->message, 0, 1);
            }
            if (right->message != 0) {
                fn_8020D250(right->message, 0, 1);
            }
        }
        if (lbl_8064DC34 == 2) {
            lbl_8064DC34 = 1;
        }
    } while (remaining != 0);
    return 0;
}
