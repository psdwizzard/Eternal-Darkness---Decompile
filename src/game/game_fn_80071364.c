/* Restores saved entry and owner state. The body matches retail; the fixed
 * compiler settings emit GPR save/restore helpers instead of stmw/lmw. */
typedef unsigned char u8;
typedef short s16;
typedef unsigned int u32;

typedef struct State {
    u32 low;
    u32 high;
    u8 count;
    u8 enabled;
    s16 mode;
    u32 value;
} State;

typedef struct Entry {
    int kind;
    char pad_04[4];
    s16 count;
    char pad_0A[0xE];
    u32 flags;
    char pad_1C[8];
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
extern void *fn_80204844(void *, int);
extern void *fn_8006D444(void *);
extern int fn_8006CB30(int *);
extern void fn_8006CAE4(Entry *, u32, u32);
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
        int kind = entry->kind;
        if (kind >= 32) {
            selected = state->high & (1U << (kind - 32));
        } else {
            selected = state->low & (1U << kind);
        }
        if (selected != 0) {
            fn_8006CAE4(entry, fn_8006CB30(&entry->kind), 0);
            switch (entry->kind) {
            case 15:
                entry->flags |= 0x401;
                break;
            }
        }
        switch (entry->kind) {
        case 12:
            entry->count = state->count;
            if (entry->count >= 4) {
                entry->flags |= 0x401;
                fn_8006CAE4(entry, fn_8006CB30(&entry->kind), 0);
            } else if (selected != 0) {
                fn_8006CAE4(entry, fn_8006CB30(&entry->kind), 0);
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
