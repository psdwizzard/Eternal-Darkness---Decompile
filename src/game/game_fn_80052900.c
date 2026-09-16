typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;

typedef struct TransitionState {
    u8 pad00[0x1D0];
    s16 sound;
    s16 timer;
    u8 pad1D4[6];
    u8 type;
    u8 pad1DB;
    s8 option;
    u8 pad1DD[6];
    s8 delay;
    s8 active;
} TransitionState;

typedef struct TypeInfo {
    u8 pad00[4];
    s32 kind;
    u8 pad08[0xC];
    s32 sound;
    u8 pad18[6];
    s16 value1E;
    s16 action;
    s16 argument;
    u8 pad24[4];
} TypeInfo;

typedef struct RuntimeState {
    u8 pad00[0x1914];
    u8 busy;
} RuntimeState;

extern TransitionState lbl_8030F540;
extern TypeInfo lbl_80241DE8[];
extern RuntimeState lbl_803003C8;
extern void fn_800B9454(s32, s32);
extern void fn_8001D9FC(s32);
extern void* fn_800AD1D0(s32);
extern void fn_8004525C(void);
extern void fn_80045200(void*);
extern void fn_80025A78(s32);
extern void fn_8016B400(s32, s32, s32);
extern void fn_8001DA0C(void);
extern void fn_80052580(s32, s32, s32, s32, s32);
extern void fn_80052424(s32, s32, s32, s32);
extern s32 fn_80054844(s32, s32);
extern void fn_800E45F4(void);
extern void fn_801EFE84(s32);
extern void fn_800073DC(s32);

s32 fn_80052900(void)
{
    TypeInfo* info;
    if (lbl_8030F540.active != 0) {
    if (lbl_8030F540.option != 0) {
        fn_800B9454(0x20, 0);
        lbl_8030F540.timer = 0;
    }
    if (lbl_8030F540.option == 2) fn_8001D9FC(3);
    else fn_8001D9FC(2);
    if (lbl_8030F540.type == 0x91 || lbl_8030F540.type == 0xA8 || lbl_8030F540.type == 0xA7) {
        if (lbl_8030F540.option == 0) {
            void* object = fn_800AD1D0(0);
            fn_8004525C();
            fn_80045200(object);
        }
    }
    if (lbl_8030F540.option == 0 && lbl_8030F540.delay == 0) {
        info = lbl_80241DE8;
        info += lbl_8030F540.type;
        if (info->kind != 0x60 && info->kind != 0 && info->kind != 0x49 &&
            info->kind != 0x4A && info->kind != 0x4B && info->value1E != -1 &&
            lbl_803003C8.busy == 0) {
            fn_80025A78(1);
            return 1;
        }
    }
    if (lbl_8030F540.option == 0) {
        if (lbl_8030F540.sound != -1) {
            fn_8016B400(lbl_8030F540.sound, 0, 0);
            lbl_8030F540.sound = -1;
        } else if (lbl_8030F540.delay == 0) {
            info = lbl_80241DE8;
            info += lbl_8030F540.type;
            if (info->sound != -1) fn_8016B400(info->sound, 0, 0);
        }
    } else if (lbl_8030F540.delay == 0) {
        if (lbl_80241DE8[lbl_8030F540.type].action == 1) {
            s16 argument = lbl_80241DE8[lbl_8030F540.type].argument;
            fn_8001DA0C();
            fn_80052580(2, argument, 1, -1, 0);
        } else if (lbl_80241DE8[lbl_8030F540.type].action == 0) {
            fn_8001DA0C();
            fn_80052424(lbl_80241DE8[lbl_8030F540.type].argument, -1, 0, 0);
        } else if (fn_80054844(0, 1) == 0) {
            fn_800B9454(0x20, 0);
            lbl_8030F540.option = 0;
            lbl_8030F540.timer = 0;
        }
        fn_800E45F4();
    }
    fn_801EFE84(0);
    fn_800073DC(3);
    return 1;
    }
    return 0;
}
