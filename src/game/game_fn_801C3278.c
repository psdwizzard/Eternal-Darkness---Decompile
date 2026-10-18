typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SampleInfo {
    u16 smpID;
    u16 instID;
    u32 data[4];
} SampleInfo;

typedef struct StreamBuffer {
    u8 state;
    u8 hwId;
    u8 smpType;
    u8 voice;
    u32 last;
    u32 finalGoodSamples;
    u32 finalLast;
    SampleInfo info;
} StreamBuffer;

typedef struct VirtualSamples {
    u8 numBuffers;
    u8 pad01[3];
    u32 bufferLength;
    StreamBuffer streamBuffer[64];
    u8 voices[64];
    u16 nextInstID;
    u16 pad94A;
    u32 (*callback)(int kind, SampleInfo* info);
} VirtualSamples;

static VirtualSamples vs;
extern u32 aramGetStreamBufferAddress(u8, u32*);
extern void hwSetVirtualSampleLoopBuffer(u32, u32, u32);
extern u16 hwGetSampleID(u32);
extern u8 hwGetSampleType(u32);

static inline void vsFreeBuffer(u8 entryIndex)
{
    vs.streamBuffer[entryIndex].state = 0;
    vs.voices[vs.streamBuffer[entryIndex].voice] = 0xFF;
}

static inline u8 vsAllocateBuffer(void)
{
    u8 i;

    for (i = 0; i < vs.numBuffers; ++i) {
        if (vs.streamBuffer[i].state != 0) {
            continue;
        }
        vs.streamBuffer[i].state = 1;
        vs.streamBuffer[i].last = 0;
        return i;
    }

    return 0xFF;
}

static inline u16 vsNewInstanceID(void)
{
    u8 i;
    u16 instID;

    do {
        instID = vs.nextInstID++;
        for (i = 0; i < vs.numBuffers; ++i) {
            if (vs.streamBuffer[i].state != 0 &&
                vs.streamBuffer[i].info.instID == instID) {
                break;
            }
        }
    } while (i != vs.numBuffers);

    return instID;
}

u32 vsSampleStartNotify(u8 voiceID)
{
    u8 sb;
    u8 i;
    u32 addr;

    for (i = 0; i < vs.numBuffers; ++i) {
        if (vs.streamBuffer[i].state != 0 &&
            vs.streamBuffer[i].voice == voiceID) {
            vsFreeBuffer(i);
        }
    }

    sb = vs.voices[voiceID] = vsAllocateBuffer();
    if (sb != 0xFF) {
        addr = aramGetStreamBufferAddress(vs.voices[voiceID], 0);
        hwSetVirtualSampleLoopBuffer(voiceID, addr, vs.bufferLength);
        vs.streamBuffer[sb].info.smpID = hwGetSampleID(voiceID);
        vs.streamBuffer[sb].info.instID = vsNewInstanceID();
        vs.streamBuffer[sb].smpType = hwGetSampleType(voiceID);
        vs.streamBuffer[sb].voice = voiceID;
        if (vs.callback != 0) {
            vs.callback(0, &vs.streamBuffer[sb].info);
            return (vs.streamBuffer[sb].info.instID << 8) | voiceID;
        }
        hwSetVirtualSampleLoopBuffer(voiceID, 0, 0);
    } else {
        hwSetVirtualSampleLoopBuffer(voiceID, 0, 0);
    }

    return 0xFFFFFFFF;
}
