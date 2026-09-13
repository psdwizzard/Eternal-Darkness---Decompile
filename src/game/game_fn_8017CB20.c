typedef unsigned int u32;
typedef unsigned char u8;
typedef struct Request { int kind; int state; int result; u8 value; } Request;
typedef struct SlotData { char pad_00[0x68]; u32 value; } SlotData;
typedef struct GlobalState { int base; int total; char pad_08[9]; u8 available; } GlobalState;
extern SlotData lbl_8064A6F0[];
extern GlobalState lbl_8064A580;
extern char lbl_802510B8[];
extern void fn_8017BA60(char*, int);

void fn_8017CB20(Request* request)
{
    if (request->result != -1) {
        if (request->result == 0) {
            u32 value = lbl_8064A6F0[request->value].value;
            if (value == 0) {
                lbl_8064A580.available = 0;
            } else {
                lbl_8064A580.total = lbl_8064A580.base + value;
                lbl_8064A580.available = 1;
            }
            request->state = 2;
        } else {
            fn_8017BA60(lbl_802510B8, request->result);
            request->state = 2;
        }
    }
}
