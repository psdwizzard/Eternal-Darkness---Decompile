typedef unsigned char u8;

typedef struct EventRequest {
    u8 pad_00[8];
    int status;
    u8 value;
} EventRequest;

typedef struct SaveSlot {
    u8 pad_00[0x20];
    int index;
    u8 rest[0x1B8 - 0x24];
} SaveSlot;

extern SaveSlot lbl_80320738;
extern SaveSlot lbl_80320978;
extern int lbl_8064CA60;
extern int lbl_8064CA6C;

extern void fn_800B25AC(void);
extern void fn_800B2548(int, int);
extern void fn_800B6960(int, int);
extern void fn_800B6A48(int);

void fn_800B5BD0(EventRequest *request)
{
    int index;

    fn_800B25AC();
    lbl_8064CA60 = 20;
    switch (request->status) {
    case 0:
        lbl_80320738 = lbl_80320978;
        index = lbl_80320738.index;
        fn_800B6960(index, 1);
        fn_800B6A48(index);
        if (lbl_8064CA6C != 0) {
            fn_800B2548(3, request->value);
        } else {
            fn_800B2548(1, request->value);
        }
        break;
    case -11:
        fn_800B2548(15, request->value);
        break;
    case -3:
        fn_800B2548(0x52, request->value);
        break;
    case -4:
        fn_800B2548(0x54, request->value);
        break;
    case -10:
        fn_800B2548(0x53, request->value);
        break;
    case -14:
        fn_800B2548(0x55, request->value);
        break;
    default:
        fn_800B2548(0x51, request->value);
        break;
    }
}
