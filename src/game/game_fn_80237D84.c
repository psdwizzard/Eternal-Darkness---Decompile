typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

typedef struct Stream {
    u32 handle;
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
extern volatile s32 lbl_8064DC38;

void fn_80237D84(void) {
    if (lbl_8064DC38 != 0) {
        lbl_8064A548[0].flags |= 8;
        lbl_8064A548[1].flags |= 8;
    }
}
