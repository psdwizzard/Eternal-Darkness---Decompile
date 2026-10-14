typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

typedef struct Stream {
    s32 handle;
    u8* buffer;
    volatile u32 flags;
    s32 half;
    s32 lastHalf;
    volatile s32 delay;
    volatile u8 curVolume;
    volatile u8 volume;
    volatile u8 newVolume;
    u8 pan;
} Stream;

extern Stream lbl_8064A548[];
extern volatile s32 lbl_8064DC38;

static s32 fn_IsStreamActive(void) {
    s32 active = lbl_8064DC38 == 1;
    return active;
}

s32 fn_8023657C(void) {
    if (fn_IsStreamActive() &&
        (lbl_8064A548[0].delay != 0 || lbl_8064A548[1].delay != 0)) {
        return 1;
    }
    return 0;
}
