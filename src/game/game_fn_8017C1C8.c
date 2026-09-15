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
extern char lbl_80250FC4[];
extern int fn_8017B294(u8);
extern int fn_80220B4C(u8);
extern void fn_8017BA60(char*, int);
extern void fn_8017B344(u8, int);
extern void fn_8017AF78(void);

void fn_8017C1C8(Request* request)
{
    /* Preserve the second value-index read after clearing its status. */
    u8* statuses = lbl_8064A580.statuses;

    if (statuses[request->value] != 0) {
        fn_8017B294(request->value);
    }
    if (lbl_8064A580.states[request->value] != 0) {
        request->result = fn_80220B4C(request->value);
        if (request->result != -1) {
            fn_8017BA60(lbl_80250FC4, request->result);
            request->state = 2;
            fn_8017B344(request->value, 0);
            statuses[request->value] = 0;
            lbl_8064A580.values[((volatile Request*)request)->value] = 0;
            lbl_8064A580.callback = 0;
            fn_8017AF78();
        }
    } else {
        request->state = 2;
        request->result = 0;
    }
}
