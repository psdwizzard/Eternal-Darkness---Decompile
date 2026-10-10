typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;

typedef struct Vec {
    f32 x;
    f32 y;
    f32 z;
} Vec;

typedef struct Definition {
    u8 pad0[0x884];
    u8 kind;
} Definition;

typedef struct Mode {
    u8 pad0[0xD];
    u8 type;
} Mode;

typedef struct Runtime {
    u8 pad0[0xB8];
    Mode* mode;
} Runtime;

typedef struct Key {
    u32 time;
    s16 value[3];
} Key;

typedef struct TrackState {
    u8 pad0[4];
    s32 direction;
    s32 blend;
    s32 posTime;
    s32 posLength;
    Key* posFrom;
    Key* posTo;
    u8 pad1C[0x48 - 0x1C];
} TrackState;

typedef struct TrackSlot {
    u32 header;
    TrackState state;
} TrackSlot;

typedef struct Owner {
    u8 pad0[0x40];
    Definition* definition;
    u8 pad44[0x160 - 0x44];
    TrackSlot* trackStates;
} Owner;

extern u16 fn_8012927C(Owner* owner);
extern Runtime* fn_80128E30(Owner* owner);
extern void fn_801270DC(f32* output, s16* input);
extern void fn_8017970C(Vec* first, Vec* second, Vec* output, f32 amount);

extern Vec lbl_8023A6B8;
extern f32 lbl_80650100;
extern f32 lbl_80650104;

Vec fn_801231D8(Owner* owner, s32 time)
{
    TrackState* state;
    Key* to;
    u16 track;
    f32 scale;
    s32 skip;
    u8 type;
    Vec result;
    Vec from;
    Vec mixed;

    track = fn_8012927C(owner);
    if (track == 0xFFFF) {
        return lbl_8023A6B8;
    }

    state = &owner->trackStates[track].state;
    to = state->posTo;
    if (state->posLength == 0) {
        state->posLength = 0x10000;
    }
    scale = (f32)time / (f32)state->posLength;
    fn_801270DC(&result.x, to->value);

    if (state->blend != 0) {
        fn_801270DC(&from.x, state->posFrom->value);
        type = fn_80128E30(owner)->mode->type;
        skip = 0;
        if ((type == 0x10 || type == 0x40) && owner->definition->kind == 0x20) {
            skip = 1;
        }
        if (skip == 0) {
            fn_8017970C(&from, &result, &mixed, (f32)state->posTime / (f32)state->posLength);
            scale = (lbl_80650100 * (f32)time) / lbl_80650104;
            result.x = mixed.x * scale;
            result.y = mixed.y * scale;
            result.z = mixed.z * scale;
        }
    } else {
        result.x *= scale;
        result.y *= scale;
        result.z *= scale;
    }

    if (state->direction == -1) {
        result.x = -result.x;
        result.y = -result.y;
        result.z = -result.z;
    }
    return result;
}
