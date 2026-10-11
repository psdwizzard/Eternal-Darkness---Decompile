typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

typedef struct Context {
    u8 pad00[8];
    s16 counter;
    u8 pad0A[0xE];
    u32 flags;
} Context;

typedef struct Work {
    u8 pad00[0x20];
    u32 flags;
} Work;

typedef struct Slot {
    u8 pad00[0x20];
    u16 timers[4];
    u8 count;
    u8 pad29[3];
} Slot;

typedef struct State {
    u8 pad00[0x38];
    int object_id;
    u8 pad3C[4];
    Slot slots[3];
    Work *work;
} State;

typedef struct Resources {
    u8 pad00[0x44];
    int object_id;
} Resources;

typedef struct ObjectInfo {
    u8 pad00[0x8C];
    Resources *resources;
} ObjectInfo;

typedef struct ModeState {
    u8 pad00[8];
    int mode;
} ModeState;

extern Context *fn_8006ED3C(State *, int, int *);
extern void fn_8006DEF8(State *, u32, u32, u32, u16);
extern void *fn_80201814(int);
extern void *fn_80201B8C(void *);
extern void *fn_80036D38(void *);
extern void fn_802020B4(void *, int);
extern void fn_801A5C30(int);
extern void fn_801E7974(u8 *, u32);
extern void fn_8020104C(int, int, int, int, float);
extern ModeState lbl_803003C8;
extern u8 *lbl_8064C4E0;
extern float lbl_8064EDBC;

int fn_8009E130(State *state)
{
    int index;
    int i;
    Context *context;
    Work *work;
    u8 slot;
    u8 *entry;
    void *object;
    ObjectInfo *info;

    context = fn_8006ED3C(state, 0xD, &index);
    if (context != 0) {
        work = state->work;
        if (!(work->flags & 0x10)) {
            return 0;
        }
        if (!(work->flags & 4)) {
            work->flags |= 1;
        }
        context->counter++;
        if (context->counter >= 3) {
            u8 count = state->slots[index].count;
            context->flags |= 0x100;
            /* Select the next timer slot, wrapping after slot three. */
            slot = 4 > (u8)(count + 1) ? count + 1 : 0;
            entry = (u8 *)state + index * 0x2C;
            entry += slot * 2;
            *(u16 *)(entry + 0x60) = 180;
        }
        if (context->counter >= 4 && !(work->flags & 8)) {
            work->flags |= 8;
            for (i = 0; i < 3; i++) {
                state->slots[index].count = i;
                fn_8006DEF8(state, 0xD, 0, 0, 0);
            }
            object = fn_80201814(state->object_id);
            info = fn_80201B8C(object);
            if (lbl_803003C8.mode == 0) {
                fn_801E7974(lbl_8064C4E0, 0x463);
            } else {
                fn_801E7974(lbl_8064C4E0, 0x464);
            }
            fn_8020104C(0x51, 0, info->resources->object_id, 0, lbl_8064EDBC);
            fn_802020B4(fn_80201814(((Resources *)fn_80036D38(object))->object_id), 0);
            fn_801A5C30(0);
            return 1;
        }
    }
    return 0;
}
