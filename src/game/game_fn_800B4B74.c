typedef struct EventRequest {
    unsigned char pad_00[8];
    int status;
    unsigned char value;
    unsigned char data[0x23];
    int size;
} EventRequest;

extern void fn_800B25AC(void);
extern int fn_800B1944(void);
extern void fn_800B2624(int, int, const char *, int, int);
extern void fn_800B587C(EventRequest *);
extern void fn_800B5E90(int, int);
extern int fn_800B6908(void);
extern void fn_800B5D94(int);
extern void fn_800B2548(int, int);
extern void fn_800B669C(int, int);
extern void fn_800B261C(void *);

void fn_800B4B74(EventRequest *request)
{
    fn_800B25AC();
    switch (fn_800B1944()) {
    case 0:
        if (request->status == 0 || request->status == -6) {
            fn_800B2624(3, request->value, (const char *)request->data,
                          request->size, (int)fn_800B587C);
        } else {
            fn_800B5E90(request->value, request->status);
        }
        break;
    case 1:
        if (request->status == 0 || request->status == -6) {
            fn_800B2624(3, request->value, (const char *)request->data,
                          request->size, (int)fn_800B587C);
        } else if (fn_800B6908() == 0) {
            fn_800B5E90(request->value, request->status);
        } else {
            fn_800B5D94(request->value);
        }
        break;
    case 2:
        switch (request->status) {
        case -6:
        case 0:
            fn_800B2624(3, request->value, (const char *)request->data,
                          request->size, (int)fn_800B587C);
            break;
        case -13:
            fn_800B2548(9, request->value);
            break;
        case -3:
        case -2:
            fn_800B669C(request->value, 0);
            break;
        default:
            fn_800B2548(0x29, request->value);
            break;
        }
        break;
    case 3:
        switch (request->status) {
        case -6:
        case 0:
            fn_800B261C((void *)1);
            fn_800B2624(3, request->value, (const char *)request->data,
                          request->size, (int)fn_800B587C);
            break;
        case -13:
            fn_800B2548(9, request->value);
            break;
        case -3:
        case -2:
            fn_800B2548(0x59, request->value);
            break;
        default:
            fn_800B2548(0x29, request->value);
            break;
        }
        break;
    }
}
