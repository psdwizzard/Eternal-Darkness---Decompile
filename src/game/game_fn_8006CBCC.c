typedef signed int s32;
typedef unsigned int u32;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;

/* This is the same Entry definition used by fn_8006D1DC. */
typedef struct Entry {
    s32 kind;
    unsigned char pad_4[32];
} Entry;

typedef struct Node {
    s32 kind;
    u8 category;
    u8 pad_5[3];
    s16 level;
    u16 state;
    u8 pad_c[4];
    u32 timer;
    u32 work;
    u32 flags;
    u8 pad_1c[8];
} Node;

typedef struct State {
    u8 pad_0[12];
    u32 active_low;
    u32 active_high;
    u8 pad_14[16];
    u32 required3_low;
    u32 required3_high;
    u32 required2_low;
    u32 required2_high;
} State;

typedef struct Owner {
    u8 pad_0[16];
    Node *nodes;
    u8 pad_14[0xB0];
    State *state;
} Owner;

extern Entry *fn_8006D1DC(s32 kind);
extern s32 lbl_8064C8CC;
extern s32 lbl_8064CBC0;

static inline void expire(Node *node, State *state)
{
    node->timer = 0;
    node->state = 1;
    if (node->kind >= 32) {
        state->active_high &= ~(1 << (node->kind - 32));
    } else {
        state->active_low &= ~(1 << node->kind);
    }
}

void fn_8006CBCC(Owner *owner)
{
    s32 complete3 = 0;
    s32 complete2 = 0;
    State *state = owner->state;
    u32 active_high;
    u32 active_low;
    u32 required3_low;
    u32 required3_high;
    u32 required2_low;
    u32 required2_high;
    u32 matched3_low;
    u32 matched2_low;
    u32 matched3_high;
    u32 matched2_high;
    s32 i;
    Node *node;
    s16 level;

    active_low = state->active_low;
    required3_low = state->required3_low;
    required2_low = state->required2_low;
    required3_high = state->required3_high;
    active_high = state->active_high;
    required2_high = state->required2_high;
    matched3_low = required3_low & active_low;
    matched2_low = required2_low & active_low;
    matched3_high = required3_high & active_high;
    matched2_high = required2_high & active_high;

    if (required3_low == matched3_low && required3_high == matched3_high) {
        complete3 = 1;
    }
    if (required2_low == matched2_low && required2_high == matched2_high) {
        complete2 = 1;
    }
    if (lbl_8064CBC0 != 0) {
        node = owner->nodes;
        for (i = 0; i < 44; node++, i++) {
            if (node->state == 2) {
                node->timer -= lbl_8064C8CC;
                if ((s32)(node->timer >> 16) < 5) {
                    expire(node, state);
                }
            }
        }
    } else {
        level = *(s16 *)(void *)&fn_8006D1DC(12)->pad_4[4];
        node = owner->nodes;
        if (level < 4) {
            complete3 = 0;
            complete2 = 0;
        }
        for (i = 0; i < 44; i++, node++) {
            if (node->state == 2) {
                if (!(node->flags & 1)) {
                    node->timer -= lbl_8064C8CC;
                    if ((s32)(node->timer >> 16) < 5) {
                        expire(node, state);
                    }
                } else if ((node->flags & 1) && !(node->flags & 0x400)) {
                    if (complete3 && node->category == 3) {
                        expire(node, state);
                    } else if (complete2 && node->category == 2) {
                        expire(node, state);
                    }
                }
            }
        }
    }
}
