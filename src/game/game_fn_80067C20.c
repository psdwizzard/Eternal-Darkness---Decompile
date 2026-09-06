typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned short u16;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct RuntimeSlot {
    u8 data[0xFC];
    s32 sound;
    u8 reserved[10];
    u8 kind;
    u8 active;
    u8 tail[4];
} RuntimeSlot;

typedef struct ObjectState {
    s32 unused;
    RuntimeSlot **installed;
} ObjectState;

extern s32 lbl_8064C548;
extern u16 lbl_8064DC88[2];
extern void *fn_80201B8C();
#define FN_80201E78_RETURN void
#define FN_80201E78_PARAMETERS Vec3 *out, void *object
extern FN_80201E78_RETURN fn_80201E78(FN_80201E78_PARAMETERS);extern void fn_801AC980(s32 handle, s32 fade);
extern s32 fn_801AC908(s32 handle, s32 arg, s32 volume);
extern s32 fn_801AC8AC(u16 id, s32 volume, s32 time, Vec3 *position);

void fn_80067C20(void *object)
{
    ObjectState *state;
    RuntimeSlot **installed;
    Vec3 position;
    Vec3 source;
    RuntimeSlot *slot;

    state = fn_80201B8C(object);
    installed = state != 0 ? state->installed : 0;
    fn_80201E78(&source, object);
    position = source;
    slot = *installed;

    if ((u32)(slot->sound + 0x10000) == 0xFFFF) {
        slot->active = lbl_8064C548;
        lbl_8064C548 = (lbl_8064C548 >= 2) ? 0 : lbl_8064C548 + 1;
    } else {
        fn_801AC980(slot->sound, 30);
        (*installed)->sound = 0;
        (*installed)->active = 0;
    }

    if (fn_801AC908((*installed)->sound, 0, 100) == 0) {
        (*installed)->sound = fn_801AC8AC(lbl_8064DC88[lbl_8064C548], 100,
                                         5000, &position);
    }
}
