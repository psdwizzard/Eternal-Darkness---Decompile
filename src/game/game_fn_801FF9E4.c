typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Command {
    u8 kind;
    u8 count;
    u16 first;
} Command;

typedef struct Color {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
} Color;

extern u8 lbl_8030F540[];
extern int lbl_8064D7D8;
extern int lbl_8064D7F0[2];
extern u8* lbl_8064D820[2];
extern u8* lbl_8064D828[2];
extern u8* lbl_8064D830[2];
extern u8* lbl_8064D838[2];
extern u8* lbl_8064D840[2];
extern Command* lbl_8064D848[2];
extern u8* lbl_8064D850[2];
extern void* lbl_8064D858[2];
extern u32 lbl_80651550;
extern u32 lbl_80651554;
extern u32 lbl_80651558;

extern void fn_801ECC4C(void);
extern void fn_801ECD74(Color);
extern void fn_801ECEC8(int, int, int);
extern void fn_801ECF50(int);
extern void fn_801ED468(int);
extern void fn_801EDA7C(int, int, int, void*);
extern void fn_801FFCE0(void);
extern void fn_801FFCE4(u16);
extern void fn_801FFCF0(u16);
extern void fn_801FFCFC(u16);
extern void fn_80225F4C(int, void*, int);
extern void fn_80226AB4(int, int, int);
extern void fn_80226D28(int);
extern void DCFlushRange(void*, u32);

void fn_801FF9E4(void)
{
    Command* current;
    int i;
    Command* command;
    u16* display;
    u8* records;
    u8* colors;
    int enabled;
    int first;
    int end;
    int offset;
    u8* record;
    int delay;
    Color packed;
    u8* index;
    u8* buffer9;
    u8* buffer11;
    u8* indices;
    int bank;

    bank = lbl_8064D7D8 ^ 1;
    command = lbl_8064D848[bank];
    display = (u16*)lbl_8064D828[bank];
    buffer9 = lbl_8064D850[bank];
    buffer11 = lbl_8064D830[bank];
    records = lbl_8064D820[bank];
    colors = lbl_8064D840[bank];
    indices = lbl_8064D838[bank];
    enabled = 1;

    if (*(int*)(lbl_8030F540 + 0x1C8) == -2) {
        return;
    }
    fn_801ECC4C();
    fn_801ED468(0x1B);
    fn_80226D28(0);
    fn_801ECEC8(1, 3, 0);
    fn_80225F4C(9, buffer9, 6);
    fn_80225F4C(11, buffer11, 4);
    fn_80225F4C(13, buffer11, 8);
    DCFlushRange(lbl_8064D858[lbl_8064D7D8 ^ 1], 0x86470);
    fn_801ECF50(3);

    current = command;
    index = indices;
    for (i = 0; i < lbl_8064D7F0[lbl_8064D7D8 ^ 1]; current++, i++, index++) {
        offset = current->kind * 0x74;
        first = current->first;
        end = first + current->count;
        record = records + offset;

        if (record[0x59] != 0 && record[0x59] != (signed char)lbl_8030F540[0x1E0]) {
            continue;
        }
        if (*index == 0) {
            continue;
        }
        for (delay = 11; delay != 0; delay--) {
        }
        if (record[0x58] == 1) {
            switch ((signed char)lbl_8030F540[0x1E0]) {
            case 1: *(u32*)&packed = lbl_80651550; break;
            case 2: *(u32*)&packed = lbl_80651554; break;
            case 3: *(u32*)&packed = lbl_80651558; break;
            }
        } else {
            packed.red = 0xFF;
            packed.green = 0xFF;
            packed.blue = 0xFF;
        }
        packed.alpha = *index;
        if (packed.alpha > 0xFD) {
            packed.alpha = 0xFF;
        }
        if (((signed char)colors[i >> 3] & (1 << (i & 7))) != 0) {
            if (enabled != 1) {
                fn_801ECEC8(1, 3, 0);
                enabled = 1;
            }
        } else {
            if (enabled) {
                fn_801ECEC8(0, 3, 0);
                enabled = 0;
            }
        }
        fn_801ECEC8(1, 3, 0);
        fn_801EDA7C(0, 0, 0xABF, record);
        fn_801ECD74(packed);
        fn_80226AB4(0x98, 6, current->count);
        for (; first < end; first++) {
            fn_801FFCFC(display[first * 2]);
            fn_801FFCF0(display[first * 2 + 1]);
            fn_801FFCE4(display[first * 2 + 1]);
        }
        fn_801FFCE0();
    }
    fn_801ECEC8(1, 3, 1);
    fn_80226D28(1);
}
