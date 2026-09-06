typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Position {
    u32 x;
    u32 y;
    u32 z;
} Position;

typedef struct EffectState {
    u8 pad0[4];
    int duration;
    int owner;
    int lower;
    int upper;
    int kind;
    int mode;
    Position position;
    int value;
    u16 sequence;
    u16 flags;
    u16 count;
    s16 step;
    s16 object_id;
    u8 pad36;
    u8 active;
    u8 type;
    u8 pad39[0xf];
    void (*update)(void);
    u8 pad4c[0x18];
    int source;
    void (*finish)(void);
} EffectState;

extern void fn_8014CBC0(EffectState *);
extern void *fn_80201814();
extern int fn_80201EB8();
extern int fn_801D39E0(int);
extern void fn_801FDC24(void);
extern void fn_8014C5D4(void);

void fn_800DC3A0(EffectState *state, int owner, Position *position, int value,
                 int count_arg, int sequence_arg)
{
    u8 count;

    if (state != 0) {
        void *object;

        fn_8014CBC0(state);
        object = fn_80201814(owner);
        state->object_id = object != 0 ? (s16)fn_80201EB8(object) : 0;
        state->position = *position;
        state->value = fn_801D39E0(value);
        count = count_arg;
        state->duration = count * 100;
        state->update = fn_801FDC24;
        state->sequence = (s16)sequence_arg;
        state->kind = 3;
        state->mode = 15;
        state->source = owner;
        state->owner = owner;
        state->lower = state->duration - 100;
        state->upper = state->duration + 100;
        state->count = count - 1;
        state->step = (u16)sequence_arg / (state->duration - 100);
        state->active = 0;
        state->flags |= 8;
        state->flags |= 0x10;
        state->flags |= 0x40;
        state->type = 6;
        state->finish = fn_8014C5D4;
    }
}
