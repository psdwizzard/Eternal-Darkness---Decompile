typedef unsigned char u8;
typedef unsigned long long u64;

typedef struct GlobalState {
    u8 pad_00[0x28];
    int states[2];
} GlobalState;

extern GlobalState lbl_8064A580;
extern char lbl_80250F24[];

extern int CARDGetSerialNo(int, u64*);
extern void fn_8017BA60(char*, int);

u64 fn_8017B35C(int index)
{
    u64 result = 0;
    int value;

    if (lbl_8064A580.states[index] != 0) {
        value = CARDGetSerialNo(index, &result);
        if (value != 0) {
            fn_8017BA60(lbl_80250F24, value);
        }
    }

    return result;
}
