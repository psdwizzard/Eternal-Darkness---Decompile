typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Entry {
    u8 pad[5];
    u8 flags;
    u8 tail[2];
} Entry;

typedef struct State {
    u8 pad0[0xDC];
    u16 count;
    u8 padDE[2];
    Entry* entries;
    u8 padE4[0x805E];
    volatile signed char ready_a;
    volatile signed char ready_b;
} State;

extern State* fn_8015C28C(int);

void fn_801E8EFC(u8 clear_mask, u8 set_mask)
{
    State* state = fn_8015C28C(2);
    u16 i;

    if (state != 0 && state->ready_a != 0 && state->ready_b != 0) {
        Entry* entry = state->entries;
        unsigned int inverted = ~clear_mask;
        for (i = 0; i < state->count; i++, entry++) {
            entry->flags &= inverted;
            entry->flags |= set_mask;
        }
    }
}
