typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct {
    u8 pad0[0x38];
    s32 command;
    u8 pad3C[0x60 - 0x3C];
    s16 channels[4];
} EventState;

typedef struct {
    u8 pad0[0x15];
    u8 level;
    u8 pad16[0x38 - 0x16];
    s32 objectId;
    u8 pad3C[0xC4 - 0x3C];
    EventState *event;
} Owner;

extern void *fn_80201B9C(void);
extern void *fn_80204844(void *, s32);
extern Owner *fn_8006D444(void);
extern s32 fn_80070A6C(s32);
extern s32 fn_80201B54(void *);
extern s32 fn_801207F0(void *);
extern s32 fn_80128328(void);
extern s32 fn_80070CD8(s32);
extern s32 fn_800462C8(s32);
extern s32 fn_801E79FC(void *, s32);
extern u64 fn_8020123C(s32, s32, s32, void *);
extern void *fn_80201814(s32);
extern void *fn_80201BC8(void *);
extern s32 fn_80038308(void *, s32, s16 *);
extern void *lbl_8064C4E0;
extern void *lbl_8064C4E4;

s32 fn_800A09D8(void)
{
    s32 result = 0;
    void *object;
    union {
        Owner *owner;
        EventState *event;
    } state;
    s32 handle;
    s32 ready;
    void *target;

    object = fn_80204844(fn_80201B9C(), 0x20);
    state.owner = fn_8006D444();
    ready = 1;
    if (fn_80070A6C(0x20) == 0) {
        handle = fn_80201B54(object);
        if ((lbl_8064C4E4 != 0 && fn_801207F0(lbl_8064C4E4) == 0) ||
            fn_80128328() == 0) {
            ready = 0;
        }
        if (ready != 0 && fn_80070CD8(1) != 0 && fn_800462C8(0) == 0 &&
            fn_801E79FC(lbl_8064C4E0, 0x3AA) != 0 && state.owner->level >= 2) {
            fn_8020123C(0x52, 0, handle, 0);
            state.owner->event->command = 0x24;
            if ((u32)(fn_8020123C(0x53, 0, handle, &state.owner->event->command) & 0xFFFFFFFFULL) == 1) {
                target = fn_80201814(state.owner->objectId);
                fn_80201BC8(target);
                state.event = state.owner->event;
                fn_80038308(target, 0, &state.event->channels[0]);
                fn_80038308(target, 2, &state.event->channels[1]);
                fn_80038308(target, 3, &state.event->channels[2]);
                fn_80038308(target, 1, &state.event->channels[3]);
                result = 1;
            }
        }
    }
    return result;
}
