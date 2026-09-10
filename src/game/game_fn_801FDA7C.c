typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct Entry {
    u32 id;
    unsigned char pad04[4];
    s32 increment;
    s32 maximum;
    unsigned char pad10[0xC];
    s16 decrement;
    unsigned char pad1E[4];
    u16 state;
    u16 threshold;
    s16 current;
    unsigned char pad28[0x1C];
    s32 value;
    unsigned char pad48[0x28];
    u16 type;
} Entry;

extern Entry* fn_801FD6F4(u32);

int fn_801FDA7C(u32 id)
{
    Entry* entry = fn_801FD6F4(id);
    if (entry != 0) {
        if (entry->type == 1 || entry->current >= entry->threshold) {
            entry->value -= entry->decrement;
            if (entry->value <= 0) {
                entry->value = 0;
                entry->state = 2;
            }
        } else if (entry->value < entry->maximum) {
            entry->value += entry->increment;
        }
    }
    return 0;
}
