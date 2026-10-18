typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;

typedef struct Request {
    int kind;
    int state;
    int result;
    u8 value;
    u8 pad_0D[0x23];
    int unk_30;
    int unk_34;
    u64 time;
    u16 attempts;
    u16 pad_42;
    int unk_44;
} Request;

typedef struct GlobalState {
    u8 pad_00[0x28];
    int states[2];
} GlobalState;

extern GlobalState lbl_8064A580;
extern u64 OSGetTime(void);
extern int fn_8017B47C(int, int*, int*);
extern int CARDCheck(int);
extern int fn_8017BD78(Request*);
extern void fn_8017C810(Request*);

int fn_8017B0C8(int value)
{
    Request request;
    int primary_value;
    int primary_level;

    request.kind = 3;
    request.state = 0;
    request.value = value;
    request.unk_30 = 0;
    request.time = OSGetTime();
    request.attempts = 0;
    request.unk_44 = 0;

    do {
        if (fn_8017B47C(request.value, &primary_value, &primary_level) == 0) {
            if (lbl_8064A580.states[request.value] != 0) {
                request.result = CARDCheck(request.value);
            } else {
                request.result = -3;
            }
        } else {
            request.result = -3;
        }
        request.attempts++;
        if (request.result == 0) {
            break;
        }
    } while (request.attempts < fn_8017BD78(&request));

    request.state = 1;
    fn_8017C810(&request);
    return request.result;
}
