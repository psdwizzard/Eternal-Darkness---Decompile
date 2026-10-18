/* Restores saved entry and owner state. */
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct State {
    u32 low;
    u32 high;
    u8 count;
    u8 enabled;
    s16 mode;
    u32 value;
} State;

/* Compatible with the object search and node state helpers. */
typedef struct Object {
    unsigned char pad[8];
    int type;
} Object;

typedef struct Node {
    unsigned char pad[0xC];
    u16 state;
    unsigned char pad_e[2];
    u32 fixed_value;
    u32 work;
    u32 flags;
} Node;

/* Entries expose their kind/count in the node's opaque prefix and occupy
 * 0x24 bytes in the table. */
typedef union Entry {
    Node node;
    struct {
        int kind;
        char pad_04[4];
        s16 count;
        char pad_0A[0x1A];
    } data;
} Entry;

typedef struct Config {
    char pad_00[0xC];
    u32 low;
    u32 high;
    char pad_14[8];
    u32 value;
} Config;

typedef struct Owner {
    char pad_00[0x15];
    u8 enabled;
    char pad_16[0xAE];
    Config *config;
} Owner;

extern Entry *lbl_8064C8D4;
extern void *fn_80201B9C(void);
extern Object *fn_80204844(Object *, int);
extern void *fn_8006D444(void *);
extern int fn_8006CB30(int *);
extern void fn_8006CAE4(Node *, u32, u32);
extern void fn_800891F4(int);

void fn_80071364(State *state)
{
    Entry *entries = lbl_8064C8D4;
    Owner *owner;
    Entry *entry;
    int i;
    u32 selected;

    owner = fn_8006D444(fn_80204844(fn_80201B9C(), 0x20));
    entry = entries + 1;
    i = 1;
    do {
        int kind = entry->data.kind;
        if (kind >= 32) {
            selected = state->high & (1U << (kind - 32));
        } else {
            selected = state->low & (1U << kind);
        }
        if (selected != 0) {
            fn_8006CAE4(&entry->node, fn_8006CB30(&entry->data.kind), 0);
            switch (entry->data.kind) {
            case 15:
                entry->node.flags |= 0x401;
                break;
            }
        }
        switch (entry->data.kind) {
        case 12:
            entry->data.count = state->count;
            if (entry->data.count >= 4) {
                entry->node.flags |= 0x401;
                fn_8006CAE4(&entry->node, fn_8006CB30(&entry->data.kind), 0);
            } else if (selected != 0) {
                fn_8006CAE4(&entry->node, fn_8006CB30(&entry->data.kind), 0);
            }
            break;
        }
        i++;
        entry++;
    } while (i < 44);
    if (owner != 0) {
        Config *config = owner->config;
        config->low = state->low;
        config->high = state->high;
        config->value = state->value;
        owner->enabled = state->enabled;
        fn_800891F4(state->mode);
    }
}
