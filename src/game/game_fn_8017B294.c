typedef unsigned char u8;

typedef struct GlobalState {
    u8 pad_00[0x28];
    int states[2];
    u8 pad_30[0x10];
    u8 active[2];
} GlobalState;

typedef struct SmallConfig {
    u8 data[0x14];
} SmallConfig;

extern GlobalState lbl_8064A580;
extern SmallConfig lbl_8064A6C8[];
extern int fn_80221828(SmallConfig*);

#pragma opt_propagation off
int fn_8017B294(int value)
{
    int result = 0;
    u8 is_active;

    if (lbl_8064A580.states[value] == 1) {
        u8* active = (u8*)&lbl_8064A580 + value;
        is_active = active[0x40];
        active += 0x40;
        if (is_active != 0) {
            result = fn_80221828(&lbl_8064A6C8[value]);
            if (result == 0) {
                *active = 0;
            }
        }
    } else {
        result = -3;
    }
    return result;
}
#pragma opt_propagation reset
