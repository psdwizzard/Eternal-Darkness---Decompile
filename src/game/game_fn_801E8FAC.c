typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

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
    signed char ready_a;
    signed char ready_b;
} State;

extern State* fn_8015C28C(int);
extern void* memcpy(void*, const void*, unsigned long);

u16 fn_801E8FAC(u8* destination)
{
    u16 offset = 0;
    State* state = fn_8015C28C(2);

    if (state != 0 && state->ready_a != 0 && state->ready_b != 0) {
        u16 i;
        Entry* entry;
        entry = state->entries;
        i = 0;
        while (i < state->count) {
            u32 value;
            *(u8*)&value = entry->flags;
            memcpy(destination + offset, &value, 4);
            offset += 4;
            i++;
            entry++;
        }
    }
    return (offset + 31) & ~31;
}
