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
extern u8 lbl_80648198[];
extern volatile s32 lbl_8064DC34;
extern volatile s32 lbl_8064DC38;
extern s32 lbl_8064DC58;
extern s32 lbl_8064DC5C;

extern void VIWaitForRetrace(void);
extern int OSReceiveMessage(void*, void*, int);
extern u32 sndStreamActivate(u32);

static inline void receiveStreamMessage(void)
{
    register void *queue;
    register void *message;
    /* ASM: lis/addi/addi keep the null message argument between the
     * two queue-address instructions; C schedules it after both. */
    asm {
        lis queue, lbl_80648198@ha
        addi message, 0, 0
        addi queue, queue, lbl_80648198@l
    }
    OSReceiveMessage(queue, message, 1);
}

void fn_80236A1C(void)
{
    register u32 addressHigh;
    register u32 flags;
    register StreamPair *streams;
    register s32 zero;
    register StreamPair *secondStreams;
    while (lbl_8064DC34 == 2) {
        VIWaitForRetrace();
    }
    if (lbl_8064DC38 == 0 && lbl_8064DC34 == 1) {
        receiveStreamMessage();
        receiveStreamMessage();
        if (lbl_8064DC38 == 0) {
            /* ASM: lis/addi/addi/li preserve address and constant ordering.
             * The zero-base addi prevents MWCC from rematerializing zero
             * for the byte stores; C also schedules the fade constant later. */
            asm {
                lis addressHigh, lbl_8064A548@ha
                addi zero, 0, 0
                addi streams, addressHigh, lbl_8064A548@l
                li r0, -4000
            }
            streams->first.volume = zero;
            streams->second.volume = zero;
            streams->first.curVolume = zero;
            streams->second.curVolume = zero;
            flags = streams->first.flags;
            flags |= 4;
            streams->first.flags = flags;
            flags = streams->second.flags;
            flags |= 4;
            streams->second.flags = flags;
            lbl_8064DC58 = zero;
            /* ASM: stw consumes the fade constant carried in r0; C cannot
             * reference that register directly. */
            asm { stw r0, lbl_8064DC5C }
            sndStreamActivate(streams->first.handle);
            /* ASM: lis/addi reload the stream address after the call; C
             * instead shares the earlier pointer in a saved register. */
            asm {
                lis secondStreams, lbl_8064A548@ha
                addi secondStreams, secondStreams, lbl_8064A548@l
            }
            sndStreamActivate(secondStreams->second.handle);
            /* ASM: li/stw use r0 for the final state update; C avoids r0
             * because the address-setup blocks explicitly reference it. */
            asm {
                li r0, 1
                stw r0, lbl_8064DC38
            }
        }
    }
}
