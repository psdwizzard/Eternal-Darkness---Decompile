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
extern s32 lbl_8064C64C;
extern volatile s32 lbl_8064DC38;
extern s32 lbl_8064DC40;
extern s32 lbl_8064DC44;
extern s32 lbl_8064DC58;
extern s32 lbl_8064DC5C;

extern void fn_801BB3A0(s32);
extern void fn_801BB1A0(s32);
extern s32 fn_801A9B94(u8, s32);
extern void fn_801BA94C(s32, s32, u8, s32, s32, s32);

static s32 fn_IsStreamActive(void) {
    s32 active = lbl_8064DC38 == 1;
    return active;
}

static void fn_PauseStreams(void) {
    if (lbl_8064DC38 != 0) {
        fn_801BB3A0(lbl_8064A548[0].handle);
        fn_801BB3A0(lbl_8064A548[1].handle);
        lbl_8064A548[0].volume = 0;
        lbl_8064A548[1].volume = 0;

        lbl_8064A548[0].newVolume = lbl_8064A548[0].volume;
        if (lbl_8064A548[0].curVolume != lbl_8064A548[0].newVolume) {
            fn_801BA94C(lbl_8064A548[0].handle, fn_801A9B94(lbl_8064A548[0].newVolume, 2),
                        lbl_8064A548[0].pan, 0, 0, 0);
        }
        lbl_8064A548[0].curVolume = lbl_8064A548[0].newVolume;

        lbl_8064A548[1].newVolume = lbl_8064A548[1].volume;
        if (lbl_8064A548[1].curVolume != lbl_8064A548[1].newVolume) {
            fn_801BA94C(lbl_8064A548[1].handle, fn_801A9B94(lbl_8064A548[1].newVolume, 2),
                        lbl_8064A548[1].pan, 0, 0, 0);
        }
        lbl_8064A548[1].curVolume = lbl_8064A548[1].newVolume;
    }
}

static void fn_ResumeStreams(void) {
    if (lbl_8064DC38 != 0) {
        lbl_8064A548[0].flags |= 0x40;
        lbl_8064A548[1].flags |= 0x40;
        lbl_8064A548[0].delay = 20;
        lbl_8064A548[1].delay = 20;
        fn_801BB1A0(lbl_8064A548[0].handle);
        fn_801BB1A0(lbl_8064A548[1].handle);
    }
}

s32 fn_802365D4(void) {
    s32 pos;
    s32 seconds;

    pos = lbl_8064DC58 + lbl_8064DC5C;
    seconds = pos / 735;
    if (lbl_8064DC44 == pos && fn_IsStreamActive() && lbl_8064DC40 + 30 < lbl_8064C64C) {
        fn_PauseStreams();
        fn_ResumeStreams();
    }
    if (lbl_8064DC44 != pos) {
        lbl_8064DC40 = lbl_8064C64C;
    }
    lbl_8064DC44 = pos;
    return seconds;
}
