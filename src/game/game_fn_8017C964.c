typedef unsigned char u8;

typedef struct Request {
    int kind;
    int state;
    int result;
    u8 value;
} Request;

typedef struct SlotInfo {
    int field_00;
    int field_04;
    char pad_08[12];
} SlotInfo;

typedef struct SlotData {
    char data[108];
} SlotData;

typedef struct GlobalState {
    char pad_00[0x40];
    u8 flags[2];
} GlobalState;

extern GlobalState lbl_8064A580;
extern SlotInfo lbl_8064A6C8[];
extern SlotData lbl_8064A6F0[];
extern char lbl_8025104C[];
extern int fn_802226E4(u8, int, SlotData*);
extern void fn_8017BA60(char*, int);

void fn_8017C964(Request* request)
{
    if (request->result != -1) {
        if (request->result == 0) {
            request->result = fn_802226E4(request->value,
                                         lbl_8064A6C8[request->value].field_04,
                                         &lbl_8064A6F0[request->value]);
            if (request->result == 0) {
                lbl_8064A580.flags[request->value] = 1;
            }
        } else {
            fn_8017BA60(lbl_8025104C, request->result);
        }
        request->state = 2;
    }
}
