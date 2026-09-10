typedef unsigned char u8;

typedef struct Request {
    int kind;
    int state;
    int result;
    u8 value;
} Request;

extern char lbl_8025100C[];
extern void fn_8017B344(int, int);
extern void fn_8017B3C8(int);
extern void fn_8017BA60(char*, int);

void fn_8017C810(Request* request)
{
    switch (request->result) {
    case 0:
        fn_8017B344(request->value, 1);
        fn_8017B3C8(request->value);
        request->state = 2;
        break;
    case -6:
        fn_8017B344(request->value, 2);
        fn_8017B3C8(request->value);
        request->state = 2;
        break;
    case -13:
        fn_8017B344(request->value, 3);
        fn_8017B3C8(request->value);
        request->state = 2;
        break;
    case -1:
        break;
    default:
        fn_8017BA60(lbl_8025100C, request->result);
        request->state = 2;
        break;
    }
}
