typedef int s32;

typedef struct Entry Entry;
struct Entry {
    s32 unk0;
    s32 unk4;
    s32 value;
};

typedef struct State State;
struct State {
    unsigned char pad0[0xC];
    s32 index;
};

extern s32 lbl_8064D18C;
extern State lbl_803003C8;
extern Entry lbl_8023BA64[];
extern s32 fn_80201AE4(void);
extern s32 fn_801E1ED4(s32);
extern s32 fn_80201ADC(void);
extern s32 fn_80201EB8(s32);
extern s32 fn_801E2004(s32);
extern s32 fn_80048628(void);

s32 fn_801E1E38(void)
{
    s32 result;
    s32 current = fn_80201AE4();
    result = 0;

    if (fn_801E1ED4(current) != 0 &&
        lbl_8064D18C == fn_80201EB8(fn_80201ADC()) &&
        lbl_8023BA64[lbl_803003C8.index].value == fn_801E2004(current) &&
        fn_80048628() == 0) {
        result = 1;
    }
    return result;
}
