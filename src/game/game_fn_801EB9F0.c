typedef unsigned char u8;
typedef unsigned int u32;

typedef struct ConfigValue {
    u32 value;
} ConfigValue;

typedef struct ConfigTable {
    u8 pad[0xC];
    ConfigValue value;
} ConfigTable;

typedef struct State {
    u8 pad0[0x14];
    u32 field14;
    u32 field18;
    u32 field1C;
    u8 pad20[0xC];
    u32 field2C;
} State;

extern ConfigTable lbl_802FC5BC;
extern u32 lbl_8064D658;
extern u32 lbl_8064D65C;
extern u32 lbl_8064D660;
extern u32 lbl_8064D664;

extern void fn_801EF3D0(void);
extern void fn_801ECBBC(ConfigValue*);

void fn_801EB9F0(State* state)
{
    ConfigValue value;

    if (state != 0) {
        fn_801EF3D0();
        value = lbl_802FC5BC.value;
        fn_801ECBBC(&value);
        lbl_8064D664 = state->field2C;
        lbl_8064D660 = state->field1C;
        lbl_8064D65C = state->field14;
        lbl_8064D658 = state->field18;
    }
}
