typedef signed int s32;

typedef struct Object {
    unsigned char unknown00[0x40];
    void *value40;
} Object;

typedef struct SoundSlot {
    s32 id;
    void *voices[4];
    Object *handles[4];
} SoundSlot;

extern SoundSlot lbl_80303D90[20];
extern void *fn_80156940(Object *object);
extern void fn_80154514(void *object, int enabled);

void fn_8003D7B4(s32 id)
{
    s32 i;
    s32 found = -1;
    SoundSlot *slot;

    for (i = 0; i < 20; i++) {
        if (id == lbl_80303D90[i].id) {
            found = i;
        }
    }

    if (found != -1) {
        lbl_80303D90[found].id = 0;
        slot = &lbl_80303D90[found];
        for (i = 0; i < 4; i++) {
            if (slot->handles[i] != 0 &&
                slot->voices[i] == fn_80156940(slot->handles[i])) {
                fn_80154514(slot->handles[i], 1);
            }
            slot->handles[i] = 0;
            slot->voices[i] = 0;
        }
    }
}
