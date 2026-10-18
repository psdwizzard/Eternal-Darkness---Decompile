typedef unsigned char u8;
typedef unsigned long long u64;

typedef struct GlobalState {
    u8 pad_00[0x28];
    int states[2];
    u64 values[2];
    u8 statuses[4];
    void* callback;
} GlobalState;

typedef struct Request {
    int kind;
    int state;
    int result;
    u8 value;
} Request;

extern GlobalState lbl_8064A580;
extern int CARDCheckAsync(u8, int);

void fn_8017C2B0(Request* request)
{
    if (lbl_8064A580.states[request->value] != 0) {
        request->result = CARDCheckAsync(request->value, 0);
        if (request->result >= 0) {
            request->state = 1;
        }
    } else {
        request->state = 2;
        request->result = -3;
    }
}
