typedef unsigned char u8;

typedef struct Request {
    int kind;
    int state;
    int result;
    u8 value;
} Request;

extern int CARDProbeEx(u8, int*, int*);
extern void* fn_8017AF64(void);
extern void fn_8017B7EC(int);
extern void fn_8017BA64(unsigned int);
extern int CARDMountAsync(u8, void*, void (*)(unsigned int), int);
extern int CARDGetXferredBytes(u8, int);
extern int lbl_8064D20C;
extern char lbl_80250FB0[];
extern void fn_8017BA60();
extern void fn_8017AF78(void);

void fn_8017C108(Request* request)
{
    int first;
    int second;
    void* registration;

    request->result = CARDProbeEx(request->value, &first, &second);
    if (request->result == 0) {
        registration = fn_8017AF64();
        fn_8017B7EC(second);
        request->result = CARDMountAsync(request->value, registration,
                                     fn_8017BA64, 0);
        if (request->result >= 0) {
            (&lbl_8064D20C)[request->value] =
                CARDGetXferredBytes(request->value, request->result);
            request->state = 1;
        } else {
            fn_8017BA60(lbl_80250FB0);
            fn_8017AF78();
        }
    }
}
