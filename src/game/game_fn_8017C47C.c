typedef unsigned char u8;
typedef unsigned int u32;

typedef struct GlobalState {
    void* buffer;
    u8 pad_04[0x24];
    int states[2];
    u8 pad_30[0x10];
    u8 statuses[2];
} GlobalState;

typedef struct Request {
    int kind;
    int state;
    int result;
    u8 value;
} Request;

extern GlobalState lbl_8064A580;
extern u8 lbl_8064A6C8[];
extern u32 lbl_8064D20C;
extern char lbl_80250FD4[];
extern u32 fn_8017B8AC(void);
extern u32 fn_8017B95C(void);
extern void DCFlushRange(void*, u32);
extern int CARDWriteAsync(u8*, void*, u32, u32, int);
extern u32 CARDGetXferredBytes(u8, int);
extern void fn_8017BA60(char*);

void fn_8017C47C(Request* request)
{
    u32 transfer_size;

    if (lbl_8064A580.states[request->value] == 1) {
        if (lbl_8064A580.statuses[request->value] != 0) {
            DCFlushRange(lbl_8064A580.buffer, fn_8017B8AC());
            transfer_size = fn_8017B95C();
            request->result =
                CARDWriteAsync(&lbl_8064A6C8[request->value * 20],
                            lbl_8064A580.buffer, fn_8017B8AC(),
                            transfer_size, 0);
            if (request->result >= 0) {
                (&lbl_8064D20C)[request->value] =
                    CARDGetXferredBytes(request->value, request->result);
                request->state = 1;
            } else {
                fn_8017BA60(lbl_80250FD4);
            }
        }
    } else {
        request->state = 2;
        request->result = -3;
    }
}
