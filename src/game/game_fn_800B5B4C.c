typedef unsigned char u8;

typedef struct EventRequest {
    u8 pad_00[8];
    int status;
    u8 value;
} EventRequest;

extern int lbl_8064C6BC[2];
extern int lbl_8064CA60;

extern void fn_800B25AC(void);
extern int fn_800B1944(void);
extern void fn_800B6840(int);
extern void fn_800B669C(int, int);
extern void fn_800B61B8(int, int);

void fn_800B5B4C(EventRequest *request)
{
    fn_800B25AC();
    if (request->status == 0) {
        if (fn_800B1944() != 2) {
            fn_800B6840(request->value);
        } else {
            lbl_8064C6BC[request->value] = 2;
            fn_800B669C(request->value, 0);
        }
    } else {
        fn_800B61B8(request->value, request->status);
    }
    lbl_8064CA60 = 20;
}
