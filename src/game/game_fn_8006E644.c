typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    unsigned char pad_00[0x0C];
    u16 value;
    unsigned char pad_0e[2];
    u32 first;
    u32 second;
} Entry;

typedef struct State {
    unsigned char pad_00[0x0C];
    u32 low_flags;
    u32 high_flags;
} State;

typedef struct Owner {
    unsigned char pad_00[0xC4];
    State *state;
} Owner;

extern Entry *fn_8006D1DC(int index);
extern void fn_8006C9D4(Entry *entry, int value);

void fn_8006E644(int index, Owner *owner)
{
    Entry *entry;
    u32 *state;
    int mask;
    int value;

    entry = fn_8006D1DC(index);
    if (entry != 0 && owner != 0) {
        state = (u32 *)owner->state;
        if (index >= 0x20) {
            mask = 1 << (index - 0x20);
            state[4] &= ~mask;
        } else {
            mask = 1 << index;
            state[3] &= ~mask;
        }
        fn_8006C9D4(entry, 1);
        entry->second = 0;
        entry->first = 0;
        entry->value = 0;
    }
}
