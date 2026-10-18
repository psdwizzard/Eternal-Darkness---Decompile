typedef unsigned char u8;
typedef unsigned int u32;

typedef struct StreamSlot {
    u32 id;
    u32 flags;
    u8 state;
    u8 pad09[0x3F];
    u32 voice;
    u8 pad4C[0x11];
    u8 hwStreamHandle;
    u8 pad5E[2];
    unsigned long cache;
} StreamSlot;

static StreamSlot streamInfo[64];
extern void hwDisableIrq(void);
extern void hwEnableIrq(void);
extern int GetPrivateIndex(u32);
extern void sndStreamDeactivate(u32);
extern void hwExitStream(u8);
void sndStreamFree(u32 id);

static inline u32 find_stream(u32 id)
{
    u32 i;

    for (i = 0; i < 64; i++) {
        if (streamInfo[i].state != 0 && id == streamInfo[i].id) {
            return i;
        }
    }
    return -1;
}

static inline void free_linked(u32 id)
{
    u32 i;

    hwDisableIrq();
    i = GetPrivateIndex(id);
    if (i != -1) {
        sndStreamDeactivate(id);
        hwExitStream(streamInfo[i].hwStreamHandle);
        if (streamInfo[i].cache != 0xFFFFFFFF) {
            sndStreamFree(streamInfo[i].cache);
        }
        streamInfo[i].state = 0;
    }
    hwEnableIrq();
}

void sndStreamFree(u32 id)
{
    u32 i;

    hwDisableIrq();
    i = find_stream(id);
    if (i != -1) {
        sndStreamDeactivate(id);
        hwExitStream(streamInfo[i].hwStreamHandle);
        if (streamInfo[i].cache != 0xFFFFFFFF) {
            free_linked(streamInfo[i].cache);
        }
        streamInfo[i].state = 0;
    }
    hwEnableIrq();
}
