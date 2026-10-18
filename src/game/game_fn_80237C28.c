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
typedef struct StreamThread StreamThread;
extern StreamThread lbl_8064A1F8;
extern volatile s32 lbl_8064DC38;
extern s32 lbl_8064DC6C;

extern void OSSetThreadPriority(void*, s32);
extern void sndStreamDeactivate(u32);
extern void sndStreamFree(u32);
extern void VIWaitForRetrace(void);
extern void fn_801ADC50(void);

void fn_80237C28(void) {
    /* Preserve the retail stack frame's unused local area. */
    u8 stackPadding[8];
    Stream* stream;
    s32 i;

    OSSetThreadPriority(&lbl_8064A1F8, 0x12);
    OSSetThreadPriority(&lbl_8064A1F8, 0x12);
    lbl_8064DC6C = 0x12;
    if (lbl_8064DC38 != 0) {
        lbl_8064A548[0].flags |= 8;
        lbl_8064A548[1].flags |= 8;
    } else {
        i = 0;
        do {
            stream = &lbl_8064A548[i];
            if ((s32)stream->flags != 0) {
                sndStreamDeactivate(stream->handle);
                sndStreamFree(stream->handle);
                stream->flags = 0;
            }
            i++;
        } while (i < 2);
    }
    while ((s32)lbl_8064A548[0].flags != 0 || (s32)lbl_8064A548[1].flags != 0 ||
           lbl_8064DC38 != 0) {
        VIWaitForRetrace();
    }
    fn_801ADC50();
}
