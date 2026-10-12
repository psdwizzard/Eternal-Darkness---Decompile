typedef signed int s32;
typedef unsigned int u32;

typedef struct SoundSlot {
    s32 id;
    s32 voices[4];
    u32 handles[4];
} SoundSlot;

extern SoundSlot lbl_80303D90[20];

s32 fn_8003D69C(s32 id)
{
    s32 i;
    s32 found = -1;
    s32 count = 0;

    for (i = 0; i < 20; i++) {
        if (id == lbl_80303D90[i].id) {
            found = i;
        }
    }

    if (found != -1 && lbl_80303D90[found].handles != 0) {
        count = 4;
    }
    return count;
}
