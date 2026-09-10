typedef unsigned char u8;

typedef struct Request {
    int kind;
    int state;
    int result;
    u8 value;
} Request;

extern char lbl_80251020[];
extern void fn_8017B344(int, int);
extern void fn_8017B3C8(int);
extern void fn_8017B35C(int);
extern void fn_8017BA54(void);
extern void fn_8017BA60(char*, int);

void fn_8017C8E0(Request* request)
{
    switch (request->result) {
    case 0:
        fn_8017B344(request->value, 1);
        fn_8017B3C8(request->value);
        fn_8017B35C(request->value);
        fn_8017BA54();
        request->state = 2;
        break;
    case -1:
        break;
    default:
        fn_8017BA60(lbl_80251020, request->result);
        request->state = 2;
        break;
    }
}
