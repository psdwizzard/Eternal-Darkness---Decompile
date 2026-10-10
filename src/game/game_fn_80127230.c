typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

typedef struct RangeState {
    int distance;
    int span;
    void* previous;
    void* current;
    u32 kind;
    s16 vector[4];
} RangeState;

typedef struct ChannelState {
    int time;
    int value;
    int wrapped;
    RangeState translation;
    RangeState rotation;
    u8 pad44[8];
} ChannelState;

typedef struct Channel {
    u16 translation_count;
    u16 pad2;
    void* translations;
    u16 rotation_count;
    u16 padA;
    void* rotations;
} Channel;

typedef struct ChannelTable {
    Channel* channels;
} ChannelTable;

typedef struct Animation {
    u8 pad0[4];
    ChannelTable* table;
} Animation;

typedef struct Runtime {
    u8 pad0[0xB8];
    Animation* animation;
    u8 padBC[0x38];
    u32 flags;
    u8 padF8[8];
    u8 reserved : 7;
    u8 active : 1;
    u8 scale;
} Runtime;

typedef struct VertexData {
    char data[0xE];
    signed char active;
    char pad_F;
} VertexData;

typedef struct VertexAttribute {
    unsigned int words[4];
} VertexAttribute;

typedef struct Owner {
    u8 pad0[0x154];
    float (*vectors)[3];
    VertexAttribute* packed_vectors;
    u8 pad15C[4];
    void* states;
    u8 pad164[0xF0];
    u32 flags;
    u8 pad258[0x50];
    u8* channel_flags;
} Owner;

extern Runtime* fn_80128E30(Owner*);
extern void fn_8012744C(Owner*, int, RangeState*, int);
extern void fn_801274F4(void*, u16, Runtime*, RangeState*, int, int, int*, int*);
extern void fn_801270DC(float*, s16*);
extern unsigned fn_801285CC(const unsigned*);
extern void fn_8012811C(VertexData*, VertexAttribute*);

void fn_80127230(register Owner* input_owner, register int input_index,
                 register int input_value, register int input_update)
{
    register ChannelState* state;
    Channel* channel;
    Runtime* runtime;
    register int update;
    register int value;
    register int index;
    register Owner* owner;
    register int offset;

    /* ASM: mr/mulli/addi preserve the input-save and address-calculation order.
     * MWCC reorders the equivalent C assignments and folds the header offset. */
    asm {
        mr index, input_index
        mulli offset, index, 0x4C
        mr owner, input_owner
        mr value, input_value
        mr update, input_update
        addi state, offset, 4
    }
    state = (ChannelState*)((u8*)input_owner->states + (int)state);
    runtime = fn_80128E30(owner);
    channel = &runtime->animation->table->channels[index];

    state->wrapped = 0;
    owner->channel_flags[index] = 0;
    if (channel->translation_count != 0) {
        if (update != 0 && state->translation.previous != 0) {
            fn_8012744C(owner, index, &state->translation, 2);
        }
        fn_801274F4(channel->translations, channel->translation_count,
                     runtime, &state->translation, value, update,
                     &state->time, &state->wrapped);
        if (state->wrapped != 0) {
            state->translation.previous = &state->translation.kind;
            if ((owner->flags & 0x1000) && !(runtime->flags & 0x20000)) {
                runtime->active = 1;
                state->translation.span = (runtime->scale + 0x10) << 16;
            }
        }
        {
            void* previous = state->translation.previous;
            owner->channel_flags[index] |= 2;
            fn_801270DC(owner->vectors[index], (s16*)((u8*)previous + 4));
        }
    }
    if (channel->rotation_count != 0) {
        if (update != 0) {
            fn_8012744C(owner, index, &state->rotation, 1);
        }
        fn_801274F4(channel->rotations, channel->rotation_count,
                     runtime, &state->rotation, value, update,
                     &state->time, &state->wrapped);
        if (state->wrapped != 0) {
            state->rotation.previous = &state->rotation.kind;
            if ((owner->flags & 0x1000) && !(runtime->flags & 0x20000)) {
                runtime->active = 1;
                state->rotation.span = (runtime->scale + 0x10) << 16;
            }
        }
        {
            unsigned* previous = state->rotation.previous;
            owner->channel_flags[index] |= 1;
            if ((int)fn_801285CC(previous) != 3 && (int)fn_801285CC(previous) == 2) {
                fn_8012811C((VertexData*)(previous + 1), &owner->packed_vectors[index]);
            }
        }
    }
    state->value = value;
}
