typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct State {
    s16 field0;
    u8 field2;
    u8 field3;
    u32 field4;
    u8 pad8[0xC];
    u32 field14;
    u32 field18;
    u32 field1C;
    u32 field20;
    u32 field24;
    u32 field28;
    u8 pad2C[0x14];
    u32 field40;
    u8 pad44[0x10];
} State;

extern volatile State lbl_805BB1E0;
extern u8 lbl_8030F540[];
extern u8 lbl_805E2600[];
extern u32 lbl_8064D5A8;
extern u32 lbl_8064D1A8;
extern u32 lbl_80650648;
extern int fn_800460EC(void);
extern void fn_80045A24(int, int);
extern void fn_801F3528(u32*);
extern void fn_8015DD48(void);
extern int fn_8020D318(void*, void**, int);
extern void fn_8015C020(int);
extern void fn_801333CC(void);
extern void fn_801358B4(int);

void fn_8015DD94(s16 value)
{
    void* message;

    lbl_8064D1A8 = lbl_8064D5A8;
    if (fn_800460EC() == 0) {
        int enabled = 0;
        if ((s8)lbl_8030F540[0x1DC] != 0) {
            enabled = 1;
        }
        fn_80045A24(1, enabled);
    }

    if (lbl_8030F540[0x1DA] != 0x53 &&
        lbl_8030F540[0x1DA] != 0x54 &&
        lbl_8030F540[0x1DA] != 0x55) {
        u32 local = lbl_80650648;
        fn_801F3528(&local);
    }

    fn_8015DD48();
    lbl_805BB1E0.field0 = value;
    lbl_805BB1E0.field14 = 0x00E72D60;
    lbl_805BB1E0.field20 = lbl_805BB1E0.field14;
    lbl_805BB1E0.field24 = 0;
    lbl_805BB1E0.field18 = 0x00DBCAA0;
    lbl_805BB1E0.field1C = 0;
    lbl_805BB1E0.field2 = 2;

    while (fn_8020D318(lbl_805E2600, &message, 0) != 0) {
    }
    lbl_805BB1E0.field3 = 1;
    fn_8015C020(0);
    fn_8020D318(lbl_805E2600, &message, 1);
    fn_801333CC();
    fn_801358B4(0);
}
