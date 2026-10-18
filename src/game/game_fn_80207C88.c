typedef signed int s32;
typedef unsigned int u32;

typedef struct EXIControl {
    void *exiCallback;
    void *tcCallback;
    void *extCallback;
    volatile u32 state;
    void *immBuf;
    s32 immLen;
    u32 dev;
    u32 id;
    s32 idTime;
    s32 queueLength;
    u32 queue[6];
} EXIControl;

extern EXIControl Ecb_80640AA8[3];

u32 EXIGetState(s32 chan)
{
    u32 offset = chan << 6;
    return *(volatile u32 *)((char *)Ecb_80640AA8 + offset + 0xC);
}
