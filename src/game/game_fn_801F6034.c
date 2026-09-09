typedef unsigned short u16;

typedef struct Animation {
    u16 flags;
    unsigned char pad_2[0x100];
    u16 frame_count;
    u16* values;
    u16* delays;
    u16* sounds;
} Animation;

typedef struct Slot {
    u16 active;
    u16 delay;
    u16 frame;
    u16 pad;
    Animation* animation;
} Slot;

u16 fn_801F6034(int index, Slot* slots)
{
    Slot* slot = &slots[index];
    return slot->animation->values[slot->frame];
}
