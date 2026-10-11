typedef struct EventRequest {
    unsigned char pad_00[8];
    int status;
    unsigned char value;
} EventRequest;

extern int lbl_8064CA58;
extern int lbl_8064CA5C;
extern int fn_800B6908(void);
extern void fn_800B25AC(void);
extern int fn_800B1944(void);
extern void fn_800BBCD4(int);
extern void fn_800B5E90(int, int);
extern void fn_800B5DDC(int);
extern unsigned long long fn_8017B440(int);
extern void fn_800B2548(int, int);
extern void fn_800B66F8(int);
extern void fn_800B669C(int, int);
extern void fn_800B6718(int);
extern void fn_800B5D94(int);

void fn_800B587C(EventRequest *request)
{
    int mode;
    unsigned long long id;

    fn_800B6908();
    fn_800B25AC();
    mode = fn_800B1944();

    switch (mode) {
    case 0:
        if (request->status == 0) {
            fn_800BBCD4(request->value);
        } else {
            fn_800B5E90(request->value, request->status);
        }
        break;
    case 1:
        if (request->status == 0) {
            if (fn_800B6908() == 1) {
                fn_800B5DDC(request->value);
            } else if ((lbl_8064CA58 | lbl_8064CA5C) != 0) {
                id = fn_8017B440(request->value);
                if (id != (((unsigned long long)(unsigned int)lbl_8064CA58 << 32) |
                           (unsigned int)lbl_8064CA5C)) {
                    fn_800B2548(0x24, request->value);
                    break;
                }
            }
            fn_800BBCD4(request->value);
        } else if (fn_800B6908() == 0) {
            fn_800B5E90(request->value, request->status);
        } else {
            fn_800B5D94(request->value);
        }
        break;
    case 2:
        switch (request->status) {
        case -13: fn_800B66F8(request->value); break;
        case -12: fn_800B2548(8, request->value); break;
        case -11: fn_800B669C(request->value, 0); break;
        case -10: fn_800B2548(9, request->value); break;
        default: fn_800B2548(0x29, request->value); break;
        }
        break;
    case 3:
        switch (request->status) {
        case -13: fn_800B6718(request->value); break;
        case -12: fn_800B2548(0x59, request->value); break;
        case -11: fn_800B2548(8, request->value); break;
        case -10: fn_800B2548(9, request->value); break;
        default: fn_800B2548(0x29, request->value); break;
        }
        break;
    }
}
