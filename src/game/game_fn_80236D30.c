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

extern Stream lbl_8064A548[2];

s32 fn_80236D30(void) {
    Stream* streams = lbl_8064A548;

    if ((s32)streams[0].flags != 0 || (s32)streams[1].flags != 0) {
        return 1;
    }
    return 0;
}
