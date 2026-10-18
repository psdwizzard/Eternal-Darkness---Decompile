/* AIInit: initialize the audio interface and its interrupt callbacks. */
typedef unsigned char u8;
typedef short s16;
typedef unsigned int u32;
typedef long long OSTime;
typedef struct OSContext OSContext;
typedef void (*OSInterruptHandler)(s16, OSContext*);
typedef void (*AIStreamCallback)(u32 sampleCount);
typedef void (*AIDMACallback)(void);

extern OSInterruptHandler __OSSetInterruptHandler(s16, OSInterruptHandler);
extern u32 __OSUnmaskInterrupts(u32);
extern void __AI_set_stream_sample_rate(u32 sampleRate);
extern void AISetDSPSampleRate(u32 sampleRate);
extern void __AISHandler(s16, OSContext*);
extern void __AIDHandler(s16, OSContext*);
extern AIStreamCallback __AIS_Callback;
extern AIDMACallback __AID_Callback;
extern void* __CallbackStack;
extern int __AI_init_flag;
extern OSTime bound_32KHz; /* 32 kHz period bound */
extern OSTime bound_48KHz; /* 48 kHz period bound */
extern OSTime min_wait; /* minimum SRC settling time */
extern OSTime max_wait; /* maximum SRC settling time */
extern OSTime buffer; /* period tolerance */

u32 __OSBusClock : 0x800000F8;

volatile u32 __AIRegs[8] : 0xCC006C00;

static inline void SetVolumeRight(u8 volume)
{
    __AIRegs[1] = (__AIRegs[1] & ~0xFF00) | (volume << 8);
}

static inline void SetVolumeLeft(u8 volume)
{
    __AIRegs[1] = (__AIRegs[1] & ~0xFF) | volume;
}

void AIInit(void* stack)
{
    if (__AI_init_flag == 1) {
        return;
    }

    /* Convert nanoseconds using the bus clock divided by four. */
    bound_32KHz = (31524 * ((__OSBusClock / 4) / 125000)) / 8000;
    bound_48KHz = (42024 * ((__OSBusClock / 4) / 125000)) / 8000;
    min_wait = (42000 * ((__OSBusClock / 4) / 125000)) / 8000;
    max_wait = (63000 * ((__OSBusClock / 4) / 125000)) / 8000;
    buffer = (3000 * ((__OSBusClock / 4) / 125000)) / 8000;

    /* Reset the sample counter, mute both channels, and clear its interrupt. */
    ((u32*)__AIRegs)[0] = (((u32*)__AIRegs)[0] & ~0x20) | 0x20;
    SetVolumeRight(0);
    SetVolumeLeft(0);
    __AIRegs[3] = 0;
    __AI_set_stream_sample_rate(1);
    AISetDSPSampleRate(0);
    __AIS_Callback = 0;
    __AID_Callback = 0;
    __CallbackStack = stack;
    __OSSetInterruptHandler(5, __AIDHandler);
    __OSUnmaskInterrupts(0x04000000);
    __OSSetInterruptHandler(8, __AISHandler);
    __OSUnmaskInterrupts(0x00800000);
    __AI_init_flag = 1;
}
