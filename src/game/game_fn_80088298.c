typedef unsigned char u8;

typedef struct EventState { int mode; } EventState;
typedef struct Owner { u8 pad[0x159]; u8 active; } Owner;
typedef struct Work {
    u8 pad38[0x38]; int object_id; u8 pad3C[0xC4 - 0x3C]; Owner* owner;
} Work;
typedef struct Object44 { u8 pad[0x44]; int object_id; } Object44;
typedef struct Object8C { u8 pad[0x8C]; Object44* object; } Object8C;
typedef struct SlotView {
    u8 pad[0x68];
    u8 state;
    u8 pad69;
    u8 field6A;
    u8 field6B;
} SlotView;

extern EventState* fn_8006ED98(Work*);
extern void fn_8006ED3C(Work*, int, int*);
extern int fn_8006ECD4(Work*, int);
extern void fn_8006DEF8(Work*, int, void*, void*, int);
extern void fn_8006EA4C(void);
extern void fn_8006BEE4(void*, void (*)(void));
extern Object44* fn_80036D38(void);
extern void *fn_80201814(int);
extern void *fn_80201B8C(void*);
extern void fn_802020B4(void*, int);
extern void fn_8020104C(int, void*, int, int, float);
extern int lbl_8064C824;
extern int fn_801A6D94(int);
extern void fn_801A6E04(int);
extern void fn_801A5C30(int);
extern void fn_8015C8A4(int, int);
extern void fn_801B08BC(int, int, int);
extern float lbl_8064EB78;
extern u8 lbl_8064C91D;

int fn_80088298(Work* work)
{
    Owner* owner;
    EventState* state;
    void* object_or_owner;
    Object44* current;
    void* other;
    Object8C* info;
    int mode6_index;
    int index;
    int callback_index;
    unsigned int slot_address;
    int i;
    SlotView* slot;

    state = fn_8006ED98(work);
    owner = work->owner;
    object_or_owner = fn_80201814(work->object_id);
    current = fn_80036D38();
    other = fn_80201814(current->object_id);
    info = fn_80201B8C(object_or_owner);
    object_or_owner = work->owner;

    if (state->mode == 6) {
        fn_8006ED3C(work, 6, &mode6_index);
        if (fn_801A6D94(lbl_8064C824)) {
            callback_index = fn_8006ECD4(work, 6);
            fn_8006BEE4(state, fn_8006EA4C);
            callback_index *= 0x2C;
            ((u8*)work)[callback_index + 0x68] = 4;
            fn_8006DEF8(work, 6, 0, 0, 0);
            for (i = 0; i < 4; i++) {
                ((u8*)work)[callback_index + 0x68] = i;
                fn_8006DEF8(work, 6, 0, 0, 0);
            }
            owner->active = 0;
        }
        fn_801A6E04(lbl_8064C824);
        fn_801A5C30(1);
        fn_802020B4(other, 1);
    } else if (state->mode == 7) {
        fn_801A5C30(1);
        fn_802020B4(other, 1);
        fn_8006ED3C(work, 7, &index);
        slot_address = index * 0x2C;
        slot_address += (unsigned int)work;
        slot = (SlotView*)slot_address;
        slot->field6A = 3;
        slot_address = index * 0x2C;
        slot_address += (unsigned int)work;
        slot = (SlotView*)slot_address;
        slot->field6B = 3;
        slot_address = index * 0x2C;
        slot_address += (unsigned int)work;
        slot = (SlotView*)slot_address;
        slot->state = 4;
        fn_8006DEF8(work, 7, 0, 0, 0);
        slot_address = index * 0x2C;
        slot_address += (unsigned int)work;
        slot = (SlotView*)slot_address;
        slot->state = 0;
        fn_8006DEF8(work, 7, 0, 0, 0);
        slot_address = index * 0x2C;
        slot_address += (unsigned int)work;
        slot = (SlotView*)slot_address;
        slot->state = 1;
        fn_8006DEF8(work, 7, 0, 0, 0);
        slot_address = index * 0x2C;
        slot_address += (unsigned int)work;
        slot = (SlotView*)slot_address;
        slot->state = 2;
        fn_8006DEF8(work, 7, 0, 0, 0);
        if ((*(unsigned int*)((u8*)object_or_owner + 0x20) & 0x20) == 0)
            fn_8020104C(0x51, 0, info->object->object_id, 0, lbl_8064EB78);
        fn_8015C8A4(2, 0);
        fn_801B08BC(-1, 0x1B, 0);
        fn_801A6E04(lbl_8064C824);
        lbl_8064C91D |= 4;
    }
    return 1;
}
