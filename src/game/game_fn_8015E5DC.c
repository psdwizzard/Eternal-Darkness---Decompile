typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct StreamState {
    volatile short handle;
    u8 pad2[0x4A];
    void* volatile manager;
} StreamState;

typedef struct GameState {
    u8 pad0[0x1D2];
    short field_1D2;
    u8 pad1D4[6];
    u8 index;
    u8 pad1DB;
    signed char flag;
} GameState;

typedef struct Entry {
    u8 pad0[0x20];
    short field_20;
    u8 pad22[6];
} Entry;

typedef struct ModeState {
    u8 pad0[0x8142];
    signed char field_8142;
    signed char field_8143;
} ModeState;

extern StreamState lbl_805BB1E0;
extern GameState lbl_8030F540;
extern Entry lbl_80241DE8[];
extern int lbl_8064D18C;

extern void fn_801F85A4(void);
extern void fn_801358B4(int);
extern void fn_801339FC(void*);
extern void fn_8015DD48(void);
extern void fn_80045A24(int, int);
extern void fn_801593AC(int);
extern void fn_801358C4(void);
extern void fn_801F5598(int);
extern void fn_801388F8(int);
extern void fn_80046B68(void);
extern void fn_80138860(int);
extern int fn_80054844(int, int);
extern ModeState* fn_8015C28C(int);
extern void fn_80046B0C(ModeState*);
extern u32 GXReadDrawSync(void);
extern void fn_8015C880(void);
extern void fn_80159440(int, int);

void fn_8015E5DC(int active, int value)
{
    fn_801F85A4();
    fn_801358B4(1);
    lbl_805BB1E0.handle = -1;
    if (lbl_805BB1E0.manager != 0)
        fn_801339FC(lbl_805BB1E0.manager);
    fn_8015DD48();
    fn_80045A24(0, 0);
    if (lbl_8064D18C == 0x4D || lbl_8064D18C == 0x10E)
        fn_801593AC(1);
    fn_801358C4();
    fn_801F5598(0);
    fn_801388F8(0);
    fn_80046B68();
    if (active) {
        fn_80138860(value);
        if (lbl_8030F540.flag &&
            lbl_80241DE8[lbl_8030F540.index].field_20 == -1 &&
            fn_80054844(0, 0) == 0) {
            lbl_8030F540.field_1D2 = 0;
        } else if (!lbl_8030F540.flag &&
                   lbl_80241DE8[lbl_8030F540.index].field_20 == -1) {
            fn_80159440(lbl_8064D18C, 0x44);
        } else {
            ModeState* state = fn_8015C28C(2);
            if (state->field_8143 && state->field_8142)
                fn_80046B0C(state);
        }
    } else {
        while ((u16)GXReadDrawSync() == 0xCACE) {}
        fn_8015C880();
        fn_80138860(0);
    }
    fn_801593AC(0);
}
