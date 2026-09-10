typedef unsigned char u8;
typedef struct Request { int kind; int state; int result; u8 value; } Request;
typedef struct SlotInfo { int field_00; int field_04; char pad_08[12]; } SlotInfo;
typedef struct SlotData { char data[108]; } SlotData;
extern SlotInfo lbl_8064A6C8[];
extern SlotData lbl_8064A6F0[];
extern char lbl_80251070[];
extern char lbl_8025108C[];
extern int fn_80222984(u8, int, SlotData*);
extern int fn_802226E4(u8, int, SlotData*);
extern void fn_8017BA60(char*, int);

void fn_8017CA0C(Request* request)
{
    switch (request->result) {
    case 0:
        request->result = fn_80222984(request->value,
                                     lbl_8064A6C8[request->value].field_04,
                                     &lbl_8064A6F0[request->value]);
        if (request->result == 0) {
            fn_802226E4(request->value,
                        lbl_8064A6C8[request->value].field_04,
                        &lbl_8064A6F0[request->value]);
            request->state = 2;
        } else {
            request->state = 2;
        }
        break;
    case -1:
        break;
    default:
        fn_8017BA60(lbl_80251070, request->result);
        request->state = 2;
        request->result = fn_80222984(request->value,
                                     lbl_8064A6C8[request->value].field_04,
                                     &lbl_8064A6F0[request->value]);
        fn_8017BA60(lbl_8025108C, request->result);
        break;
    }
}
