typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;

typedef struct DirectionState {
    unsigned char pad00[0x8C];
    struct DirectionRuntime *runtime;
} DirectionState;

typedef struct DirectionRuntime {
    unsigned char pad00[0x64];
    s32 first_direction;
    s32 second_direction;
} DirectionRuntime;

extern s32 fn_801A6DA4(void *value);
extern s32 fn_801A6DAC(void *value);
extern s32 fn_801A6DB4(void *value);
extern s32 fn_801A6DBC(void *value);
extern s32 fn_80063C78(s32 x, s32 y);
extern void fn_801441C0(u16 count, s32 zero, u16 count_again);

s32 fn_80063D60(void *value, DirectionState *state, u16 count)
{
    s32 direction;
    s32 doubled_count;
    s16 x;
    s32 index;
    s32 changed;
    s32 next;

    doubled_count = count * 2;
    changed = 0;
    for (index = 0; index < 2; index++) {
        s16 y;

        x = index != 0 ? fn_801A6DB4(value) : fn_801A6DA4(value);
        y = index != 0 ? fn_801A6DBC(value) : fn_801A6DAC(value);
        if (index != 0) {
            direction = state->runtime->second_direction;
        } else {
            direction = state->runtime->first_direction;
        }

        next = fn_80063C78(x, y);
        if (direction != next && next != 8) {
            direction = next;
            changed++;
            fn_801441C0(doubled_count, 0, doubled_count);
        } else if (next != 8) {
            direction = next;
        }

        if (index != 0) {
            state->runtime->second_direction = direction;
        } else {
            state->runtime->first_direction = direction;
        }
    }
    return changed;
}
