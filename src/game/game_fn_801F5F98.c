typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Animation {
    u16 flags;
    unsigned char pad_2[0x10E];
} Animation;

extern u32 fn_801E741C(void*);

#pragma use_lmw_stmw on

int fn_801F5F98(u32 key, u32 clear, u16 set, u16 count, Animation* animation)
{
    if (animation != 0) {
        u32 clear_mask = ~(u16)clear;
        int matches = 0;
        u16 i;
        Animation* current = animation;

        for (i = 0; i < count; i++, current++) {
            if (fn_801E741C((char*)current + 2) == key) {
                current->flags &= clear_mask;
                matches++;
                current->flags |= set;
            }
        }
        return matches;
    }
    return 0;
}
