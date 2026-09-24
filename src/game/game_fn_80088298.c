typedef unsigned char u8;

typedef struct EventState {
    int mode;
} EventState;

typedef struct Owner {
    u8 pad[0x159];
    u8 active;
} Owner;

typedef struct Work {
    u8 pad38[0x38];
    int object_id;
    u8 pad3C[0xC4 - 0x3C];
    Owner *owner;
} Work;

typedef struct Object44 {
    u8 pad[0x44];
    int object_id;
} Object44;

typedef struct Object8C {
    u8 pad[0x8C];
    Object44 *object;
} Object8C;

typedef struct Slot {
    u8 state;
    u8 pad01;
    u8 field02;
    u8 field03;
    u8 pad04[0x28];
} Slot;

typedef struct SlotView {
    u8 pad[0x68];
    Slot slots[1];
} SlotView;

extern EventState *fn_8006ED98(Work *);
extern void *fn_8006ED3C(void *, int, int *);
extern int fn_8006ECD4(Work *, int);
extern void fn_8006DEF8(Work *, int, void *, void *, int);
extern void fn_8006EA4C(void);
extern void fn_8006BEE4(void *, void (*)(void));
extern Object44 *fn_80036D38(void);
extern void *fn_80201814(int);
extern void *fn_80201B8C(u8 *);
extern void fn_802020B4(void *, int);
extern void fn_8020104C(int, int, int, int, float);
extern int lbl_8064C824;
extern int fn_801A6D94(int);
extern void fn_801A6E04(int);
extern void fn_801A5C30(int);
extern void fn_8015C8A4(int, int);
extern void fn_801B08BC(int, int, int);
extern float lbl_8064EB78;
extern u8 lbl_8064C91D;

int fn_80088298(void *argument) {
    Work *work = (Work *)argument;
    void *object;
    Owner *owner;
    EventState *state;
    Object44 *current;
    void *other;
    SlotView *slots;
    Object8C *info;
    Owner *notification_owner;

    state = fn_8006ED98(work);
    owner = work->owner;
    object = fn_80201814(work->object_id);
    current = fn_80036D38();
    slots = (SlotView *)work;
    other = fn_80201814(current->object_id);
    info = fn_80201B8C(object);
    notification_owner = work->owner;
    if (state->mode == 6) {
        int index;
        int callback_index;
        u8 *bytes = (u8 *)work;
        int i;

        fn_8006ED3C(work, 6, &index);
        if (fn_801A6D94(lbl_8064C824)) {
            callback_index = fn_8006ECD4(work, 6);
            fn_8006BEE4(state, fn_8006EA4C);
            slots->slots[callback_index].state = 4;
            fn_8006DEF8(work, 6, 0, 0, 0);
            callback_index *= 0x2C;
            callback_index += 0x68;
            for (i = 0; i < 4; i++) {
                bytes[callback_index] = i;
                fn_8006DEF8(work, 6, 0, 0, 0);
            }

            owner->active = 0;
        }
        fn_801A6E04(lbl_8064C824);
        fn_801A5C30(1);
        fn_802020B4(other, 1);
    } else if (state->mode == 7) {
        int index;

        fn_801A5C30(1);
        fn_802020B4(other, 1);
        fn_8006ED3C(work, 7, &index);
        slots->slots[index].field02 = 3;
        slots->slots[index].field03 = 3;
        slots->slots[index].state = 4;
        fn_8006DEF8(work, 7, 0, 0, 0);
        slots->slots[index].state = 0;
        fn_8006DEF8(work, 7, 0, 0, 0);
        slots->slots[index].state = 1;
        fn_8006DEF8(work, 7, 0, 0, 0);
        slots->slots[index].state = 2;
        fn_8006DEF8(work, 7, 0, 0, 0);
        if ((*(unsigned int *)((u8 *)notification_owner + 0x20) & 0x20) == 0) {
            fn_8020104C(0x51, 0, info->object->object_id, 0,
                        lbl_8064EB78);
        }
        fn_8015C8A4(2, 0);
        fn_801B08BC(-1, 0x1B, 0);
        fn_801A6E04(lbl_8064C824);
        lbl_8064C91D |= 4;
    }
    return 1;
}
