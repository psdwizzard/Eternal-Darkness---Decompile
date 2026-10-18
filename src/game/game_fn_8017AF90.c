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

extern void* fn_8017AF64(void);
extern u64 OSGetTime(void);
extern int fn_8017B47C(int, int*, int*);
extern int CARDMount(int, void*, void*);
extern int fn_8017BD78(Request*);
extern void fn_8017C724(Request*);
extern void fn_8017BA64(unsigned int);

int fn_8017AF90(int value)
{
    void* handle;
    Request request;
    int primary_value;
    int primary_level;

    handle = fn_8017AF64();
    request.kind = 1;
    request.state = 0;
    request.value = value;
    request.unk_30 = 0;
    request.time = OSGetTime();
    request.attempts = 0;
    request.unk_44 = 0;

    do {
        if (fn_8017B47C(request.value, &primary_value, &primary_level) == 0) {
            request.result = CARDMount(request.value, handle, fn_8017BA64);
        } else {
            request.result = -3;
        }
        request.attempts++;
        if (request.result == 0) {
            break;
        }
    } while (request.attempts < fn_8017BD78(&request));

    request.state = 1;
    fn_8017C724(&request);
    return request.result;
}
