typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct Channel { float value, upper, lower, rise, fall, delta; s32 repeats, delay, timer; u32 flags; } Channel;
typedef struct Table { u8 pad[0xC]; u16 count; u8 padE[0x1A]; u8* entries; } Table;
typedef struct Owner { u8 pad[0x3C]; Table* table; u8 pad40[0x25C]; Channel* channels; u8 pad2A0[0x24]; u32 active; } Owner;

extern const float lbl_80650110;
extern const float lbl_80650114;

void fn_801247F8(Owner* owner, s32 index, s32 frames, float target)
{
    u32 one = 1;
    s32 offset = 0;
    s32 entry_index = index * 8;
    s32 channel_offset;
    u32 bit;
    Table* table;
    s32 count;
    s32 i;
    table = owner->table;
    channel_offset = index * 0x28;
    bit = one << index;
    count = table->count;

    for (i = 0; i < count; i++) {
        u8* entry = table->entries + offset + 0x14;
        if (entry != 0 && *(u32*)(entry + entry_index) != 0xFFFFFFFF) {
            Channel* channel = (Channel*)((u8*)owner->channels + channel_offset);
            if (channel->value != target) {
                if (frames == 0) {
                    channel->value = target;
                } else {
                    float delta;
                    owner->active |= bit;
                    delta = (target - channel->value) / frames;
                    if (delta < lbl_80650110) {
                        channel->upper = lbl_80650114;
                        channel->lower = target;
                    } else {
                        channel->upper = target;
                        channel->lower = lbl_80650110;
                    }
                    channel->rise = lbl_80650110;
                    channel->fall = lbl_80650110;
                    channel->delta = delta;
                    channel->repeats = 1;
                    channel->delay = 0;
                    channel->timer = 0;
                    channel->flags = 9;
                }
            }
        }
        offset += 0x114;
    }
}
