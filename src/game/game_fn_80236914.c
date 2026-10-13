typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

typedef struct Stream {
    u32 handle;
    u8 *buffer;
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
extern s32 lbl_8064DC38;

extern void fn_801BB3A0(u32 id);
extern u8 fn_801A9B94(u8 value, int mode);
extern void fn_801BA94C(u32 id, u8 volume, u8 left, u8 right, u8 aux_left, u8 aux_right);

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

void fn_80236914(void)
{
    register StreamPair *streams;
    u8 volume;

    if (lbl_8064DC38 != 0) {
        streams = streamPair();
        fn_801BB3A0(streams->first.handle);
        streams = streamPair();
        fn_801BB3A0(streams->second.handle);
        streams = streamPair();
        streams->first.volume = 0;
        streams->second.volume = 0;
        streams->first.newVolume = streams->first.volume;
        if (streams->first.curVolume != streams->first.newVolume) {
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
