typedef signed int s32;
typedef unsigned int u32;

typedef struct SoundSlot {
    s32 id;
    s32 voices[4];
    u32 handles[4];
} SoundSlot;

extern SoundSlot lbl_80303D90[20];
extern void* memset(void*, int, u32);

s32 fn_8003D4F0(s32 id) {
    s32 i;
    s32 count = 0;
    s32 freeSlot = -1;
    s32 found = -1;

    for (i = 0; i < 20; i++) {
        if (id == lbl_80303D90[i].id) {
            found = i;
            count++;
        } else if (lbl_80303D90[i].id == 0 && freeSlot == -1) {
            freeSlot = i;
        }
    }

    if (count == 0 && freeSlot == -1) {
        /* no matching slot and no free slot */
    } else if (count > 1) {
        /* duplicate registrations: leave as-is */
    } else if (freeSlot != -1 && count != 1) {
        found = freeSlot;
        memset(&lbl_80303D90[freeSlot], 0, sizeof(SoundSlot));
        lbl_80303D90[freeSlot].id = id;
    }
    return found;
}
