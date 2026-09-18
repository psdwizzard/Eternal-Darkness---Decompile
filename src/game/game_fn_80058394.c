typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;

typedef struct HandlerState {
    void *linked;
    u8 pad[0x84];
    u16 values[4];
    u8 flags;
    u8 index;
} HandlerState;

#pragma use_lmw_stmw on

extern char lbl_80243A40[];
extern char lbl_8064B4E4;
extern s32 lbl_8064C864;
extern char lbl_80331748[];
extern int fn_80200C10(void *);
extern void *fn_80201BC8();
extern void *fn_80201B8C();
extern void fn_800C39D0(void *context);
extern void fn_800BEBE4(void *context, s32 value);
extern s32 fn_80035FB8(void *context, char *first, char *second, char *third,
                      char *value, char *fourth);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern s32 fn_80070A6C(s32 value);
extern int fn_80200C38();
extern u32 fn_801A7780(void *object);
extern u8 fn_801A781C(void *object);
extern s32 fn_800BF848(void *context, void *event);
extern s32 fn_800C28D8(void *context, void *event);
extern s32 fn_800C2FC4(void *context, void *event, u32 value);
extern void fn_801A742C(void *object, u32 value);
extern u32 fn_801A77D4(void *object);
extern void fn_801A7460(void *object, u32 value);
extern u16 fn_801A7434(void *object);
extern void fn_800C3514(void *context, void *event);
extern void fn_800C4AA0(void *context, void *event, u32 *result);
extern void fn_800C4B6C(void *context, void *event);
extern void *fn_8004918C(void);
extern u64 fn_802011D4(void *event);
extern void fn_800C63D8(void);
extern s32 fn_801261F4(void *object);
extern void fn_8012B344(void*);

s32 fn_80058394(void *context_arg, void *event_arg, u32 *result)
{
    void *object;
    char *strings;
    s32 kind;
    void *context = context_arg;
    void *event = event_arg;
    struct { HandlerState *ptr; } state;

    strings = lbl_80243A40;
    kind = fn_80200C10(event);
    object = fn_80201BC8(context);
    state.ptr = (HandlerState *)*(void **)fn_80201B8C(context);

    if (kind == 1) return 1;
    if (kind == 2) {
        state.ptr->linked = 0;
        fn_800C39D0(context);
        return 1;
    }
    if (kind == 3) {
        if ((state.ptr->flags & 2) != 0 && (state.ptr->flags & 8) == 0) {
            fn_800BEBE4(context, 400);
        }
        return 1;
    }
    if (kind == 12) {
        if (lbl_8064C864 == 0) {
            if (fn_80035FB8(context, strings + 0xA0, strings + 0x148,
                            strings + 0x154, &lbl_8064B4E4,
                            strings + 0xD8) == 0) {
                fn_80201D2C(context, 1);
                fn_80201D14(context, 1);
            }
        }
        return 1;
    }
    if (kind == 40) {
        if (fn_80070A6C(0x200) == 0) {
            void *linked = (void *)fn_80200C38(event);
            u32 flags = fn_801A7780(linked);
            if (fn_801A781C(linked) == 0) {
                if ((flags & 0x10018) != 0) {
                    if (fn_800BF848(context, event) == 0) {
                        fn_80201D2C(context, 1);
                        fn_80201D14(context, 1);
                    }
                } else if ((flags & 4) != 0) {
                    if (fn_800C28D8(context, event) != 0) {
                        fn_80201D2C(context, 6);
                        fn_80201D14(context, 1);
                    } else {
                        fn_80201D2C(context, 1);
                        fn_80201D14(context, 1);
                    }
                } else if ((flags & 0x80020) != 0) {
                    if (fn_800C2FC4(context, event, flags & 0x80000) == 0) {
                        fn_80201D2C(context, 1);
                        fn_80201D14(context, 1);
                    }
                }
            } else if ((state.ptr->flags & 1) == 0) {
                u32 linked_value;
                fn_801A742C(linked, 1);
                linked_value = fn_801A77D4(linked);
                fn_801A7460(linked, linked_value);
                if (fn_800C28D8(context, event) != 0) {
                    state.ptr->flags |= 1;
                    state.ptr->values[state.ptr->index] = fn_801A7434(linked);
                } else {
                    fn_80201D2C(context, 1);
                    fn_80201D14(context, 1);
                }
            } else {
                if ((state.ptr->flags & 2) == 0) {
                    fn_801A742C(linked, 8);
                    fn_801A7460(linked, fn_801A77D4(linked));
                } else {
                    fn_801A742C(linked, 0x100);
                    fn_801A7460(linked, fn_801A77D4(linked));
                }
                fn_800C3514(context, event);
            }
        }
        return 1;
    }
    if (kind == 69) {
        if (fn_80070A6C(0x200) == 0) fn_800C4AA0(context, event, result);
        return 1;
    }
    if (kind == 70) {
        if (fn_80070A6C(0x200) == 0) fn_800C4B6C(context, event);
        return 1;
    }
    if (kind == 135) {
        fn_801A742C(fn_8004918C(), 1);
        state.ptr->flags |= 8;
        if (result != 0) *result = fn_802011D4(event) & 0xFFFFFFFFULL;
        fn_800C63D8();
        return 1;
    }
    if (kind == 175) {
        if (*(void **)(lbl_80331748 + 0xAC) != 0) {
            fn_801261F4(object);
            fn_8012B344(object);
            if (result != 0) *result = 1;
            fn_80201D2C(context, 0x40);
            fn_80201D14(context, 1);
        }
        return 1;
    }
    if (kind == 52) return 1;
    if (kind == 41) return 1;
    if (kind == 42) return 1;
    if (kind == 43) return 1;
    if (kind == 45) return 1;
    if (kind == 44) return 1;
    if (kind == 46) return 1;
    if (kind == 147) return 1;
    return (u8)(kind == 31);
}
