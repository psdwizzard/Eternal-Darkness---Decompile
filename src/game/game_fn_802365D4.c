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

typedef struct StreamPair {
    Stream first;
    Stream second;
} StreamPair;
extern StreamPair lbl_8064A548;
extern s32 lbl_8064C64C;
extern volatile s32 lbl_8064DC38;
extern s32 lbl_8064DC40;
extern s32 lbl_8064DC44;
extern s32 lbl_8064DC58;
extern s32 lbl_8064DC5C;

extern void fn_801BB3A0(u32);
extern u32 fn_801BB1A0(u32);
extern u8 fn_801A9B94(u8, s32);
extern void fn_801BA94C(u32, u8, u8, u8, u8, u8);

static s32 fn_IsStreamActive(void) {
    s32 active = lbl_8064DC38 == 1;
    return active;
}

static inline StreamPair *streamPair(void)
{
    register StreamPair *streams;
    /* ASM: lis/addi prevent MWCC from retaining the global address across calls,
     * which plain C address expressions are optimized to do. */
    asm {
        lis streams, lbl_8064A548@ha
        addi streams, streams, lbl_8064A548@l
    }
    return streams;
}

static inline void fn_PauseStreams(void)
{
    register StreamPair *streams;
    u8 volume;
    register u32 current;
    register u32 zero;

    if (lbl_8064DC38 != 0) {
        streams = streamPair();
        fn_801BB3A0(streams->first.handle);
        streams = streamPair();
        fn_801BB3A0(streams->second.handle);
        /* ASM: lis/li/addi/stb/stb/lbz/stb/lbz keep the address and zero
         * setup local; C retains the address across calls and reorders setup. */
        asm {
            lis current, lbl_8064A548@ha
            li zero, 0
            addi streams, current, lbl_8064A548@l
            stb zero, 0x19(streams)
            stb zero, 0x35(streams)
            lbz zero, 0x19(streams)
            stb zero, 0x1a(streams)
            lbz current, 0x18(streams)
        }
        if (current != streams->first.newVolume) {
            volume = fn_801A9B94(streams->first.newVolume, 2);
            streams = streamPair();
            fn_801BA94C(streams->first.handle, volume, streams->first.pan, 0, 0, 0);
        }
        streams = streamPair();
        streams->first.curVolume = streams->first.newVolume;
        streams->second.newVolume = streams->second.volume;
        if (streams->second.curVolume != streams->second.newVolume) {
            volume = fn_801A9B94(streams->second.newVolume, 2);
            streams = streamPair();
            fn_801BA94C(streams->second.handle, volume, streams->second.pan, 0, 0, 0);
        }
        streams = streamPair();
        streams->second.curVolume = streams->second.newVolume;
    }
}

static inline void fn_ResumeStreams(void) {
    register s32 delay;
    register StreamPair* streams;
    register u32 flags;
    if (lbl_8064DC38 != 0) {
        /* ASM: lis/li/addi/lwz/ori preserve the address, delay and flags
         * setup order and register reuse that MWCC changes for plain C. */
        asm {
            lis flags, lbl_8064A548@ha
            li delay, 20
            addi streams, flags, lbl_8064A548@l
            lwz flags, 8(streams)
            ori flags, flags, 0x40
        }
        streams->first.flags = flags;
        flags = streams->second.flags;
        flags |= 0x40;
        streams->second.flags = flags;
        streams->first.delay = delay;
        streams->second.delay = delay;
        fn_801BB1A0(streams->first.handle);
        streams = streamPair();
        fn_801BB1A0(streams->second.handle);
    }
}

s32 fn_802365D4(void) {
    s32 pos;
    s32 seconds;
    s32 quotient;

    pos = lbl_8064DC58 + lbl_8064DC5C;
    /* Signed division by 735, with the correction for truncation to zero. */
    quotient = __mulhw(0x164A893B, pos) >> 6;
    seconds = quotient + ((u32)quotient >> 31);
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
