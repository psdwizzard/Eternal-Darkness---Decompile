typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TransferState {
    u8 pad0[0x3C];
    u32 offset;
    u8 buffers[2][0x1000];
    int remaining;
    int buffer_index;
    u8 pad2048[0x1C];
    void* completion_queue;
    u8 pad2068[0x18];
    int pending_size;
} TransferState;

extern int OSReceiveMessage(void*, u32*, int);
extern int DVDReadAsyncPrio(TransferState*, void*, u32, u32, void (*)(int, TransferState*), int);
extern void DCInvalidateRange(void*, u32);
extern void* memcpy(void*, const void*, u32);
extern int fn_8015A2E0(TransferState*);
extern void fn_8015CDF0(void);
extern void fn_8015CDC0(int, TransferState*);

int fn_8015CE48(void* destination, int length, TransferState* state)
{
    int message;
    int aligned;

    if (state->remaining > 0) {
        do {
            if (!OSReceiveMessage(state->completion_queue, (u32*)&message, 0)) {
                OSReceiveMessage(state->completion_queue, (u32*)&message, 1);
            }

            if (message != state->pending_size) {
                while (!DVDReadAsyncPrio(state, state->buffers[state->buffer_index],
                                     state->pending_size, state->offset,
                                     fn_8015CDC0, 2)) {
                }
            }
        } while (message != state->pending_size);

        DCInvalidateRange(state->buffers[state->buffer_index], (length + 31) & ~31);
    }

    if (fn_8015A2E0(state)) {
        fn_8015CDF0();
    }

    memcpy(destination, state->buffers[state->buffer_index], length);
    state->offset += length;
    state->remaining -= length;
    state->buffer_index ^= 1;

    aligned = 0x1000;
    if (state->remaining < 0x1000) {
        aligned = (state->remaining + 31) & ~31;
    }
    state->pending_size = 0;
    if (state->remaining > 0) {
        state->pending_size = aligned;
        while (!DVDReadAsyncPrio(state, state->buffers[state->buffer_index], aligned,
                             state->offset, fn_8015CDC0, 2)) {
        }
    }
    return 0;
}
