typedef signed int s32;
typedef unsigned int u32;
typedef unsigned short u16;

typedef struct Node {
    s32 index;
    unsigned char bytes[6];
    u16 state;
    unsigned char pad[0xC];
    u32 flags;
} Node;

typedef struct State {
    unsigned char bytes[0xC];
    u32 accumulated_low;
    u32 accumulated_high;
    u32 selected_low;
    u32 selected_high;
    unsigned char pad[4];
    u32 flags;
} State;

typedef struct Owner {
    unsigned char bytes[4];
    Node *node;
    unsigned char pad[0xBC];
    State *state;
} Owner;

extern void fn_8006C9D4(Node *node, u16 state);

void fn_8006C9F0(Owner *owner)
{
    s32 index;
    u32 mask;
    State *state;

    state = owner->state;
    index = owner->node->index;

    if (index >= 32) {
        mask = 1 << (index - 32);
        state->selected_high = mask;
        state->accumulated_high |= mask;
    } else {
        mask = 1 << index;
        state->selected_low = mask;
        state->accumulated_low |= mask;
    }
    if ((owner->node->flags & 0xC0) != 0) {
        state->flags |= 3;
    }
    if ((owner->node->flags & 0x800) != 0) {
        state->flags |= 0x100;
    }
    if ((owner->node->flags & 0x80000) != 0) {
        state->flags |= 0x4000;
    }
    fn_8006C9D4(owner->node, 4);
}
