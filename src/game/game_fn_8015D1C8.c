typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Message {
    u32 type;
    u32 pad4[2];
    void* owner;
    u32 value;
    void* reply_queue;
} Message;

typedef struct WorkerState {
    u8 pad0[0x34];
    void* owner;
    u8 pad38[4];
    u32 offset;
    u8 buffer[0x2000];
    void* transfer_owner;
    u32 pad2044;
    int active;
    u32 pad204C;
    int remaining;
    u32 message_value;
    u32 pad2058;
    void* notify_queue;
    u8 pad2060[8];
    void* input_queue;
    u8 pad206C[4];
    void* context;
    u8 pad2074[8];
    u32 progress;
    u32 transfer_size;
} WorkerState;

#pragma use_lmw_stmw on

extern int OSReceiveMessage(void*, Message**, int);
extern void OSSendMessage(void*, void*, int);
extern int DVDOpen(u32, WorkerState*);
extern void* fn_80145E3C(int);
extern int DVDReadAsyncPrio(WorkerState*, void*, u32, u32, void (*)(int, WorkerState*), int);
extern void fn_8015CDC0(int, WorkerState*);
extern int fn_80147DD4(void*, int (*)(void*, int, WorkerState*),
                      int (*)(void*, int, WorkerState*), WorkerState*, void*);
extern int fn_8015CE48(void*, int, WorkerState*);
extern int fn_8015CFFC(void*, int, WorkerState*);
extern void DVDClose(WorkerState*);
extern void fn_80155BB0(const char*, const char*, ...);
extern char lbl_8024F198[];
extern char lbl_8024F1B4[];

void fn_8015D1C8(WorkerState* state)
{
    Message* volatile received;
    Message* message;
    void* owner;
    void* context;

    state->active = 0;
    for (;;) {
        OSReceiveMessage(state->input_queue, (Message**)&received, 1);
        message = received;
        if (DVDOpen(message->type, state)) {
            owner = state->owner;
            fn_80145E3C(0);
            context = state->context;
            state->remaining = 0;
            state->active = 1;
            state->pad2044 = 0;
            state->offset = 0;
            state->transfer_owner = owner;
            state->message_value = message->value;
            state->pad2058 = 0;
            state->progress = 0;
            message->owner = owner;
            OSSendMessage(message->reply_queue, message, 1);
            state->transfer_size = 0x20;
            while (!DVDReadAsyncPrio(state, state->buffer, 0x20, 0,
                                 fn_8015CDC0, 2)) {
            }
            fn_80147DD4(owner, fn_8015CE48, fn_8015CFFC, state, context);
            if (state->remaining == 1) {
                OSSendMessage(state->notify_queue, (void*)0x2A, 1);
            }
            DVDClose(state);
        } else {
            fn_80155BB0(lbl_8024F198, lbl_8024F1B4, message->type);
        }
    }
}
