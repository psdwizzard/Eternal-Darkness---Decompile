typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct Channel { float value, upper, lower, rise, fall, delta; s32 repeats, delay, timer; u32 flags; } Channel;
typedef struct Table { u8 pad[0xC]; u16 count; u8 padE[0x1A]; u8* entries; } Table;
typedef struct Owner { u8 pad[0x3C]; Table* table; u8 pad40[0x25C]; Channel* channels; u8 pad2A0[0x24]; u32 active; } Owner;

void fn_80124750(Owner* owner, s32 index, s32 delay, s32 repeats, u32 flags,
                  float value, float upper, float rise, float fall)
{
    u32 one;
    s32 offset;
    u8* entry_index;
    s32 channel_offset;
    u32 bit;
    u32 new_flags;
    Table* table;
    u16 count;
    Channel* channel;
    s32 i;

    one = 1;
    new_flags = flags | 9;
    entry_index = (u8*)(index * 8);
    channel_offset = index * 0x28;
    bit = one << index;
    table = owner->table;
    offset = 0;
    count = table->count;

    for (i = 0; i < count; i++) {
        u8* entry = table->entries + offset + 0x14;
        if (entry != 0 && *(u32*)(entry_index + (u32)entry) != 0xFFFFFFFF) {
            channel = (Channel*)((u8*)owner->channels + channel_offset);
            owner->active |= bit;
            channel->value = value;
            channel->upper = upper;
            channel->lower = value;
            channel->rise = rise;
            channel->fall = fall;
            channel->delta = rise;
            channel->repeats = repeats;
            channel->delay = delay;
            channel->timer = 0;
            channel->flags = new_flags;
        }
        offset += 0x114;
    }
}
