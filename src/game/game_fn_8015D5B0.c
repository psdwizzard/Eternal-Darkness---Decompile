typedef unsigned char u8;

typedef struct Request {
    int type;
    int active;
} Request;

typedef struct WorkerState {
    u8 pad0[0x2040];
    int remaining;
    u8 pad2044[4];
    int active;
    u8 pad204C[4];
    int pending;
    u8 pad2054[0xC];
    void* input_queue;
    u8 pad2064[0x18];
    int progress;
} WorkerState;

extern Request* fn_801587C4(void);
extern void OSSendMessage(void*, void*, int);
extern void fn_8015A1AC(WorkerState*);

void fn_8015D5B0(WorkerState* state)
{
    Request* request;

    if (state->active == 1) {
        if (state->remaining > 0 || state->progress > 0) {
            request = fn_801587C4();
            state->pending = 1;
            request->active = 2;
            OSSendMessage(state->input_queue, request, 1);
        }
        state->active = 0;
        fn_8015A1AC(state);
    }
}
