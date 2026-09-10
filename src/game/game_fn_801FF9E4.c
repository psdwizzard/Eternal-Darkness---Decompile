typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Command {
    u8 kind;
    u8 count;
    u16 first;
} Command;

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
extern void fn_801ECD74(void*);
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
    int bank = lbl_8064D7D8 ^ 1;
    Command* command = lbl_8064D848[bank];
    u8* indices = lbl_8064D850[bank];
    u8* records = lbl_8064D820[bank];
    u8* colors = lbl_8064D840[bank];
    u8* vertices = lbl_8064D838[bank];
    u16* display = (u16*)lbl_8064D828[bank];
    u8* state = lbl_8064D830[bank];
    int enabled = 1;
    int i;

    if (*(int*)(lbl_8030F540 + 0x1C8) == -2) {
        return;
    }
    fn_801ECC4C();
    fn_801ED468(0x1B);
    fn_80226D28(0);
    fn_801ECEC8(1, 3, 0);
    fn_80225F4C(9, state, 6);
    fn_80225F4C(11, records, 4);
    fn_80225F4C(13, records, 8);
    DCFlushRange(lbl_8064D858[bank], 0x86470);
    fn_801ECF50(3);

    for (i = 0; i < lbl_8064D7F0[bank]; i++, command++, indices++) {
        u8* record = records + command->kind * 0x74;
        int end = command->first + command->count;
        int j;
        u32 packed;

        if (record[0x59] != 0 && record[0x59] != (signed char)lbl_8030F540[0x1E0]) {
            continue;
        }
        if (*indices == 0) {
            continue;
        }
        asm {
            li r0, 0xB
            mtctr r0
        delay:
            bdnz delay
        }
        if (record[0x58] == 1) {
            switch ((signed char)lbl_8030F540[0x1E0]) {
            case 1: packed = lbl_80651550; break;
            case 2: packed = lbl_80651554; break;
            case 3: packed = lbl_80651558; break;
            }
        } else {
            packed = 0xFFFFFF00;
        }
        ((u8*)&packed)[3] = *indices > 0xFD ? 0xFF : *indices;
        if (((signed char)colors[i >> 3] & (1 << (i & 7))) != 0) {
            if (!enabled) fn_801ECEC8(1, 3, 0);
            enabled = 1;
        } else {
            if (enabled) fn_801ECEC8(0, 3, 0);
            enabled = 0;
        }
        fn_801ECEC8(1, 3, 0);
        fn_801EDA7C(0, 0, 0xABF, record);
        fn_801ECD74(&packed);
        fn_80226AB4(0x98, 6, command->count);
        for (j = command->first; j < end; j++) {
            fn_801FFCFC(display[j * 2]);
            fn_801FFCF0(display[j * 2 + 1]);
            fn_801FFCE4(display[j * 2 + 1]);
        }
        fn_801FFCE0();
        vertices = vertices;
    }
    fn_801ECEC8(1, 3, 1);
    fn_80226D28(1);
}
