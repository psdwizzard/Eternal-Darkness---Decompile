typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Animation {
    u16 flags;
    unsigned char pad_2[0x100];
    u16 frame_count;
    u16* values;
    u16* delays;
    u16* sounds;
} Animation;

extern u32 fn_801E741C(void*);

#pragma use_lmw_stmw on

int fn_801F5EFC(u32 key, int frame, u16 value, u16 count, Animation* animation)
{
    int matches = 0;
    u16 i;

    if (animation != 0) {
        Animation* current = animation;
        for (i = 0; i < count; i++, current++) {
            if (fn_801E741C((char*)current + 2) == key) {
                if (frame < current->frame_count) {
                    current->sounds[frame] = value;
                    matches++;
                } else {
                    return -1;
                }
            }
        }
    }
    return matches;
}
