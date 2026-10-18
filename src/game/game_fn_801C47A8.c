typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct InputState {
    u8 pad00[0xC];
    u16 flags;
    u16 reset;
    u8 pad10[0x42];
    s16 value52;
    s16 value54;
    s16 value56;
    s16 value58;
    s16 value5A;
    s16 value5C;
    s16 value5E;
    s16 value60;
    s16 value62;
} InputState;

typedef struct InputOwner {
    InputState* state;
    u8 pad04[0xE9];
    u8 active;
} InputOwner;

typedef struct Accumulator {
    int unused;
    int values[9];
} Accumulator;

#define CLAMP(value, low, high) \
    ((value) > (high) ? (high) : ((value) < (low) ? (low) : (value)))

void HandleDepopVoice(Accumulator* accumulator, InputOwner* owner)
{
    InputState* state;

    owner->active = 0;
    owner->state->reset = 0;
    state = owner->state;

    accumulator->values[0] += state->value52;
    accumulator->values[0] = CLAMP(accumulator->values[0], -0x7FFFFF, 0x7FFFFF);
    accumulator->values[1] += state->value58;
    accumulator->values[1] = CLAMP(accumulator->values[1], -0x7FFFFF, 0x7FFFFF);

    if (state->flags & 4) {
        accumulator->values[2] += state->value5E;
        accumulator->values[2] = CLAMP(accumulator->values[2], -0x7FFFFF, 0x7FFFFF);
    }
    if (state->flags & 1) {
        accumulator->values[3] += state->value54;
        accumulator->values[3] = CLAMP(accumulator->values[3], -0x7FFFFF, 0x7FFFFF);
        accumulator->values[4] += state->value5A;
        accumulator->values[4] = CLAMP(accumulator->values[4], -0x7FFFFF, 0x7FFFFF);
        if (state->flags & 0x14) {
            accumulator->values[5] += state->value60;
            accumulator->values[5] = CLAMP(accumulator->values[5], -0x7FFFFF, 0x7FFFFF);
        }
    }
    if (state->flags & 0x12) {
        accumulator->values[6] += state->value56;
        accumulator->values[6] = CLAMP(accumulator->values[6], -0x7FFFFF, 0x7FFFFF);
        accumulator->values[7] += state->value5C;
        accumulator->values[7] = CLAMP(accumulator->values[7], -0x7FFFFF, 0x7FFFFF);
        if (state->flags & 4) {
            accumulator->values[8] += state->value62;
            accumulator->values[8] = CLAMP(accumulator->values[8], -0x7FFFFF, 0x7FFFFF);
        }
    }
}
