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
extern u32 sndStreamActivate(u32 id);

void fn_802368A8(void)
{
    register StreamPair *streams;
    register StreamPair *secondStreams;
    register u32 addressHigh;
    if (lbl_8064DC38 != 0) {
        /* ASM: lis/li/addi preserve address construction around the delay
         * constant; MWCC schedules the constant after the first flags load. */
        asm {
            lis addressHigh, lbl_8064A548@ha
            li r0, 20
            addi streams, addressHigh, lbl_8064A548@l
        }
        streams->first.flags |= 0x40;
        streams->second.flags |= 0x40;
        /* ASM: stw/stw consume the delay constant in r0 after the flag
         * updates; C cannot explicitly carry a value in that register. */
        asm {
            stw r0, 0x14(streams)
            stw r0, 0x30(streams)
        }
        sndStreamActivate(streams->first.handle);
        /* ASM: lis/addi reload the stream pair address after the call;
         * MWCC otherwise retains it in a callee-saved register. */
        asm {
            lis secondStreams, lbl_8064A548@ha
            addi secondStreams, secondStreams, lbl_8064A548@l
        }
        sndStreamActivate(secondStreams->second.handle);
    }
}
