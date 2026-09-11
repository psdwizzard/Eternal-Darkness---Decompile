typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct TypeDescriptor {
    void* name;
    u8 pad04[4];
    s16 resource_index;
    s16 sound;
    s16 value0C;
    s16 action;
    s16 kind;
    s16 argument;
    s16 pad14;
    s16 pad16;
} TypeDescriptor;

typedef struct ObjectDescriptor {
    u8 pad00[0xC];
    s32 kind;
    u8 pad10[0x18];
} ObjectDescriptor;

typedef struct TransitionState {
    u8 pad00[0x1D0];
    s16 sound;
    s16 pending;
    u8 pad1D4[6];
    u8 type;
    u8 flag1DB;
    s8 option;
    u8 pad1DD[4];
    s8 mode;
    s8 restore;
    u8 pad1E3;
    s8 suppress;
} TransitionState;

typedef struct GameState {
    void* object;
    u8 pad04[4];
    s32 mode;
} GameState;

extern TransitionState lbl_8030F540;
extern TypeDescriptor lbl_802417D0[];
extern ObjectDescriptor lbl_80241DE8[];
extern void* lbl_8024E388[];
extern GameState lbl_803003C8;
extern void* lbl_8064C85C;
extern s32 lbl_8064D18C;
extern void* lbl_8064B71C;
extern u32 lbl_80651944;

extern void fn_80144680(void*);
extern void fn_80132D50(void);
extern void fn_8011B740(void);
extern void fn_801453FC(void);
extern void fn_801E7974(void*, s32);
extern void fn_80237C28(void);
extern void fn_80046B68(void);
extern void fn_8015C880(void);
extern void fn_80159440(s32, s32);
extern void* fn_80008724(void*);
extern void fn_801387EC(void*);
extern void fn_8001D9FC(s32);
extern void fn_80025A78(s32);
extern void fn_80045A24(s32, s32);
extern void fn_801F3528(u32*);
extern void fn_80144430(s32, s32);
extern void fn_8016B400(s32, s32, s32);
extern void fn_8001DA0C(void);
extern void fn_80052580(s32, s32, s32, s32, s32);
extern void fn_80052424(s32, s32, s32, s32);
extern s32 fn_80054844(s32, s32);
extern void fn_800B9454(s32, s32);
extern s32 fn_800ACFE0(void);
extern void fn_800AD430(void);

void fn_80052CC0(s32 unused0, s32 unused1)
{
    TypeDescriptor* descriptor;
    TransitionState* state;
    s16* kinds;
    s16 kind;
    s32 action;
    u8 index;
    u32 time;

    fn_80144680(lbl_8064C85C);
    fn_80132D50();
    fn_8011B740();
    fn_801453FC();

    descriptor = lbl_802417D0;
    state = &lbl_8030F540;
    descriptor = &descriptor[state->type];
    action = descriptor->action;
    if (action != -1 && state->option != 1) {
        index = (u8)descriptor->resource_index;
        if (index == 0xFF) {
            fn_801E7974(lbl_8024E388[0], action);
        } else {
            fn_801E7974(lbl_8024E388[index - 1], action);
        }
    }

    kinds = &lbl_802417D0[0].kind;
    kind = lbl_802417D0[lbl_8030F540.type].kind;
    if (kind != -1 && lbl_8030F540.suppress == 0) {
        s16 argument;
        descriptor = &lbl_802417D0[lbl_8030F540.type];
        argument = descriptor->argument;
        if (kind == 1) {
            if (lbl_802417D0[argument].value0C != -1 &&
                lbl_802417D0[argument].value0C != 0x3C) {
                fn_80237C28();
            }
        } else if (lbl_80241DE8[argument].kind != -1 &&
                   lbl_80241DE8[argument].kind != 0x3C) {
            fn_80237C28();
        }
    } else {
        fn_80237C28();
    }

    if (*(s16*)((u8*)kinds + lbl_8030F540.type * sizeof(TypeDescriptor)) != 1 &&
        lbl_8030F540.restore != 0) {
        fn_80046B68();
        fn_8015C880();
        fn_80159440(lbl_8064D18C, 0x44);
        lbl_8064B71C = fn_80008724(lbl_803003C8.object);
        fn_801387EC(fn_80008724(lbl_803003C8.object));
    }

    if (lbl_8030F540.option == 2) {
        fn_8001D9FC(3);
    } else if (lbl_8030F540.type == 0x40) {
        fn_80025A78(3);
    } else {
        fn_8001D9FC(lbl_8030F540.mode);
    }

    if (lbl_8030F540.mode != 0) {
        fn_80045A24(0, 0);
    }

    time = lbl_80651944;
    fn_801F3528(&time);
    fn_80144430(2, 0);

    if (lbl_8030F540.option == 0 && lbl_8030F540.sound != 0 &&
        lbl_802417D0[lbl_8030F540.type].sound != -1) {
        fn_8016B400(lbl_802417D0[lbl_8030F540.type].sound, 0, 0);
    } else if (lbl_8030F540.option != 0) {
        s32 byte_offset = lbl_8030F540.type * sizeof(TypeDescriptor);
        kind = *(s16*)((u8*)kinds + byte_offset);
        if (kind == 1) {
            s32 mode = lbl_8030F540.mode;
            s32 restore = lbl_8030F540.restore;
            s32 sound = lbl_8030F540.sound;
            s32 argument = *(s16*)((u8*)&lbl_802417D0[0].argument + byte_offset);
            fn_8001DA0C();
            fn_80052580(mode, argument, restore, sound, 0);
        } else if (kind == 0) {
            fn_80052424(*(s16*)((u8*)&lbl_802417D0[0].argument + byte_offset), -1, 0, 0);
        } else if (fn_80054844(1, 1) == 0) {
            if (lbl_8030F540.pending != 0) {
                fn_800B9454(0x20, 0);
                lbl_8030F540.pending = 0;
            }
            lbl_8030F540.option = 0;
        }
    }

    if (lbl_803003C8.mode == 13 && fn_800ACFE0() < 5) {
        fn_800AD430();
    }
}
