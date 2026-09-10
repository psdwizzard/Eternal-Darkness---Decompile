typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct Entry {
    u32 id;
    unsigned char pad04[4];
    s32 lower;
    s32 upper;
    unsigned char pad10[0xC];
    s16 scale;
    unsigned char pad1E[2];
    s16 velocity;
    unsigned char pad22[0x22];
    s32 value;
} Entry;

extern Entry* fn_801FD6F4(u32);

s32 fn_801FDE24(u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0) {
        entry->value -= entry->velocity * entry->scale;
        if (entry->value <= entry->lower) {
            int velocity = entry->velocity;
            if ((s16)velocity < 0) {
                velocity = (u32)-velocity;
            }
            entry->velocity = -velocity;
        } else if (entry->value >= entry->upper) {
            int velocity = entry->velocity;
            if ((s16)velocity < 0) {
                velocity = (u32)-velocity;
            }
            entry->velocity = velocity;
        }
    }
    return entry->value;
}
