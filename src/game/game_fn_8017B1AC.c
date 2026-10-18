typedef unsigned char u8;

typedef struct GlobalState {
    u8 pad_00[0x28];
    int states[2];
    u8 pad_30[0x10];
    u8 active[2];
} GlobalState;

typedef struct SmallConfig {
    int unk_00;
    int unk_04;
    u8 pad_08[0xC];
} SmallConfig;

typedef struct LargeConfig {
    u8 data[0x6C];
} LargeConfig;

extern GlobalState lbl_8064A580;
extern SmallConfig lbl_8064A6C8[];
extern LargeConfig lbl_8064A6F0[];
extern char lbl_80250EEC[];
extern char lbl_80250F0C[];

extern int CARDOpen(int, void*, SmallConfig*);
extern int CARDGetStatus(int, int, LargeConfig*);
extern void fn_8017BA60(char*, int);

int fn_8017B1AC(int value, void* data)
{
    int result;

    if (lbl_8064A580.states[value] == 1) {
        result = CARDOpen(value, data, &lbl_8064A6C8[value]);
        if (result == 0) {
            result = CARDGetStatus(value, lbl_8064A6C8[value].unk_04,
                                 &lbl_8064A6F0[value]);
            if (result == 0) {
                lbl_8064A580.active[value] = 1;
            } else {
                fn_8017BA60(lbl_80250EEC, result);
            }
        } else {
            fn_8017BA60(lbl_80250F0C, result);
        }
    } else {
        result = -3;
    }
    return result;
}
