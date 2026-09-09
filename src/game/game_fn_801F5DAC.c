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

extern void fn_8016B400(u16, int, int);

#pragma use_lmw_stmw on

void fn_801F5DAC(Slot* slot)
{
    Animation* animation = slot->animation;
    u16 flags = animation->flags;

    if (!(flags & 2) && !(flags & 0x10)) {
        slot->delay++;
        if (slot->delay >= animation->delays[slot->frame]) {
            slot->delay = 0;
            slot->frame++;
            if (slot->frame >= animation->frame_count) {
                if (flags & 4) {
                    slot->frame = animation->frame_count - 1;
                    animation->flags |= 2;
                } else {
                    if (flags & 0x20) {
                        slot->frame = 1;
                    } else {
                        slot->frame = 0;
                    }
                    slot->delay = 0;
                }
            }
            if (animation->sounds[slot->frame] != 0) {
                fn_8016B400(animation->sounds[slot->frame], 0, 0);
            }
        }
    }
    if (flags & 1) {
        animation->flags &= ~1;
        slot->frame = 0;
        slot->delay = 0;
    }
    if (flags & 8) {
        animation->flags &= ~8;
        animation->flags = 2;
        slot->frame = animation->frame_count - 1;
        slot->delay = 0;
    }
}
