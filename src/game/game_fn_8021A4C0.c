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
extern void fn_8021A384(u32 sampleRate);
extern void fn_8021A290(u32 sampleRate);
extern void fn_8021A624(s16, OSContext*);
extern void fn_8021A6A0(s16, OSContext*);
extern AIStreamCallback lbl_8064DAD8;
extern AIDMACallback lbl_8064DADC;
extern void* lbl_8064DAE0;
extern int lbl_8064DAE8;
extern OSTime lbl_8064DAF0; /* 32 kHz period bound */
extern OSTime lbl_8064DAF8; /* 48 kHz period bound */
extern OSTime lbl_8064DB00; /* minimum SRC settling time */
extern OSTime lbl_8064DB08; /* maximum SRC settling time */
extern OSTime lbl_8064DB10; /* period tolerance */

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

void fn_8021A4C0(void* stack)
{
    if (lbl_8064DAE8 == 1) {
        return;
    }

    /* Convert nanoseconds using the bus clock divided by four. */
    lbl_8064DAF0 = (31524 * ((__OSBusClock / 4) / 125000)) / 8000;
    lbl_8064DAF8 = (42024 * ((__OSBusClock / 4) / 125000)) / 8000;
    lbl_8064DB00 = (42000 * ((__OSBusClock / 4) / 125000)) / 8000;
    lbl_8064DB08 = (63000 * ((__OSBusClock / 4) / 125000)) / 8000;
    lbl_8064DB10 = (3000 * ((__OSBusClock / 4) / 125000)) / 8000;

    /* Reset the sample counter, mute both channels, and clear its interrupt. */
    ((u32*)__AIRegs)[0] = (((u32*)__AIRegs)[0] & ~0x20) | 0x20;
    SetVolumeRight(0);
    SetVolumeLeft(0);
    __AIRegs[3] = 0;
    fn_8021A384(1);
    fn_8021A290(0);
    lbl_8064DAD8 = 0;
    lbl_8064DADC = 0;
    lbl_8064DAE0 = stack;
    __OSSetInterruptHandler(5, fn_8021A6A0);
    __OSUnmaskInterrupts(0x04000000);
    __OSSetInterruptHandler(8, fn_8021A624);
    __OSUnmaskInterrupts(0x00800000);
    lbl_8064DAE8 = 1;
}
