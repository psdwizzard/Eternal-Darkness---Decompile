typedef unsigned char u8;
typedef signed int s32;

typedef struct RuntimeSlot {
    u8 data[0xF8];
    s32 object_id;
    u8 tail[0x14];
} RuntimeSlot;

typedef struct ObjectState {
    s32 unused;
    RuntimeSlot **installed;
    u8 pad[0x8C];
    s32 mode;
    u8 pad98[7];
    u8 kind;
} ObjectState;

extern RuntimeSlot lbl_8030FBF8[12];
extern s32 lbl_8064D18C;
extern void *fn_80201814();
extern void *fn_80201B8C();
extern int fn_80201EB8();

s32 fn_80067858(s32 object_id)
{
    ObjectState *state;
    s32 free_slot;
    void *object;
    s32 found;
    RuntimeSlot **installed;
    s32 result;
    s32 i;

    object = fn_80201814(object_id);
    found = 0;
    result = -1;
    free_slot = -1;
    state = fn_80201B8C(object);
    if (state->kind == 3 && state->mode == 2 &&
        fn_80201EB8(object) == lbl_8064D18C && state->installed != 0 &&
        *state->installed == 0) {
        installed = state->installed;
        for (i = 0; i < 12; i++) {
            if (lbl_8030FBF8[i].object_id == object_id) {
                result = i;
                found++;
            } else if (lbl_8030FBF8[i].object_id == 0 && free_slot == -1) {
                free_slot = i;
            }
        }

        if (found == 0 && free_slot == -1) {
            return result;
        }
        if (found > 1) {
            return result;
        }
        if (free_slot != -1 && found != 1) {
            result = free_slot;
            lbl_8030FBF8[free_slot].object_id = object_id;
            *installed = &lbl_8030FBF8[free_slot];
        }
    }
    return result;
}
