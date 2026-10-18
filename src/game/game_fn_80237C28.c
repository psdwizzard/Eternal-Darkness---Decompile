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
typedef struct OSThread OSThread;
extern OSThread lbl_8064A1F8;
extern volatile s32 lbl_8064DC38;
extern s32 lbl_8064DC6C;

extern s32 fn_802101F4(OSThread*, s32);
extern void fn_801BB3A0(u32);
extern void fn_801BAF90(u32);
extern void fn_80217324(void);
extern void fn_801ADC50(void);

void fn_80237C28(void) {
    /* Preserve the retail stack frame's unused local area. */
    u8 stackPadding[4];
    register Stream* stream;
    register s32 i;
    register u32 address;
    register OSThread *thread;
    register s32 priority;

    thread = &lbl_8064A1F8;
    priority = 0x12;
    fn_802101F4(thread, priority);
    /* ASM: lis/li/mr/addi reload the thread address and prepare the priority;
     * C retains the address across calls and changes the argument order. */
    asm {
        lis thread, lbl_8064A1F8@ha
        li r4, 0x12
        mr priority, r4
        addi thread, thread, lbl_8064A1F8@l
    }
    fn_802101F4(thread, priority);
    lbl_8064DC6C = 0x12;
    if (lbl_8064DC38 != 0) {
        lbl_8064A548[0].flags |= 8;
        lbl_8064A548[1].flags |= 8;
    } else {
        /* ASM: lis/li/addi initialize the counter between the address halves;
         * C builds the address in a temporary and introduces a move. */
        asm {
            lis address, lbl_8064A548@ha
            li i, 0
            addi stream, address, lbl_8064A548@l
        }
    stop_stream:
        if ((s32)stream->flags != 0) {
            fn_801BB3A0(stream->handle);
            fn_801BAF90(stream->handle);
            stream->flags = 0;
        }
        /* ASM: addi/addi/cmpwi/blt advance both loop variables before
         * testing the count; C schedules the comparison between increments. */
        asm {
            addi i, i, 1
            addi stream, stream, 0x1C
            cmpwi i, 2
            blt stop_stream
        }
    }
    while ((s32)lbl_8064A548[0].flags != 0 || (s32)lbl_8064A548[1].flags != 0 ||
           lbl_8064DC38 != 0) {
        fn_80217324();
    }
    fn_801ADC50();
}
