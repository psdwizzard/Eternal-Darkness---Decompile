typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Message {
    u32 pad0;
    int type;
    u32 pad8;
    u32 remaining;
    u8* data;
    void* reply_queue;
} Message;

typedef struct ReadState {
    u8 pad0[0x2050];
    int mode;
    u8* data;
    u32 remaining;
    void* reply_queue;
    void* input_queue;
    u8 pad2064[0x14];
    Message* message;
    int progress;
} ReadState;

#pragma use_lmw_stmw on

extern int fn_8020D318(void*, Message**, int);
extern void fn_8020D250(void*, Message*, int);
extern void fn_80158850(Message*);
extern void* memcpy(void*, const void*, u32);
extern void DCFlushRange(void*, u32);

static inline int TransferAmount(int length, u32 remaining)
{
    if (remaining < length) {
        return remaining;
    }
    return length;
}

int fn_8015CFFC(void* destination, int length, ReadState* state)
{
    register void* output = destination;
    u32 copied = 0;
    int amount;
    Message* message;
    int result;

    if (state->mode == 1) {
        amount = fn_8020D318(state->input_queue, &message, 0);

        if (state->message != 0) {
            fn_80158850(state->message);
            state->message = 0;
        }
        if (amount) {
            if (message->type == 2) {
                fn_80158850(message);
                result = 1;
                goto done;
            }
            if (state->reply_queue != 0) {
                fn_8020D250(state->reply_queue, message, 1);
            }
        }
        result = 1;
        goto done;
    }

    do {
        if (state->remaining == 0) {
            fn_8020D318(state->input_queue, &message, 1);
            ((volatile ReadState*)state)->message = message;
            if (state->message->type == 2 || state->mode == 1) {
                state->mode = 1;
                result = 1;
                goto done;
            }
            state->remaining = state->message->remaining;
            state->data = state->message->data;
            state->reply_queue = state->message->reply_queue;
        }

        amount = TransferAmount(length, state->remaining);
        memcpy(state->data, (u8*)output + copied, amount);
        DCFlushRange(state->data, amount);
        if (state->progress == 0) {
            state->progress = *(u32*)state->data + 4;
        }
        length -= amount;
        copied += amount;
        state->data += amount;
        state->remaining -= amount;
        state->progress -= amount;

        if (state->remaining == 0) {
            fn_8020D250(state->reply_queue, state->message, 1);
            state->message = 0;
        }
    } while (length != 0);
    result = 0;
done:
    return result;
}
