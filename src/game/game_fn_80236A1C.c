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
extern u8 lbl_80648198[];
extern volatile s32 lbl_8064DC34;
extern volatile s32 lbl_8064DC38;
extern s32 lbl_8064DC58;
extern s32 lbl_8064DC5C;

extern void fn_80217324(void);
extern int fn_8020D318(void*, void*, int);
extern u32 fn_801BB1A0(u32);

void fn_80236A1C(void) {
    while (lbl_8064DC34 == 2) {
        fn_80217324();
    }
    if (lbl_8064DC38 == 0 && lbl_8064DC34 == 1) {
        fn_8020D318(lbl_80648198, 0, 1);
        fn_8020D318(lbl_80648198, 0, 1);
        if (lbl_8064DC38 == 0) {
            lbl_8064A548[0].volume = 0;
            lbl_8064A548[1].volume = 0;
            lbl_8064A548[0].curVolume = 0;
            lbl_8064A548[1].curVolume = 0;
            lbl_8064A548[0].flags |= 4;
            lbl_8064A548[1].flags |= 4;
            lbl_8064DC58 = 0;
            lbl_8064DC5C = -4000;
            fn_801BB1A0(lbl_8064A548[0].handle);
            fn_801BB1A0(lbl_8064A548[1].handle);
            lbl_8064DC38 = 1;
        }
    }
}
