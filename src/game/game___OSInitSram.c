typedef int BOOL;
#define FALSE 0
typedef unsigned char u8;
typedef unsigned int u32;
typedef void (*EXICallback)(long chan, void* context);

void DCInvalidateRange(void* addr, u32 nBytes);
BOOL EXILock(long chan, u32 dev, EXICallback unlockedCallback);
BOOL EXIUnlock(long chan);
BOOL EXISelect(long chan, u32 dev, u32 freq);
BOOL EXIDeselect(long chan);
BOOL EXIImm(long chan, void* buf, long len, u32 type, EXICallback callback);
BOOL EXIDma(long chan, void* buf, long len, u32 type, EXICallback callback);
BOOL EXISync(long chan);

#define RTC_SRAM_SIZE 64
#define RTC_CMD_READ 0x20000000
#define RTC_SRAM_ADDR 0x00000100

typedef struct SramControlBlock {
    u8 sram[RTC_SRAM_SIZE];
    u32 offset;
    BOOL enabled;
    BOOL locked;
    BOOL sync;
    void (*callback)(void);
} SramControlBlock;

extern SramControlBlock Scb_80640E40;

static BOOL ReadSram(void* buffer) {
    BOOL err;
    u32 cmd;

    DCInvalidateRange(buffer, RTC_SRAM_SIZE);
    if (!EXILock(0, 1, 0)) {
        return FALSE;
    }
    if (!EXISelect(0, 1, 3)) {
        EXIUnlock(0);
        return FALSE;
    }

    cmd = RTC_CMD_READ | RTC_SRAM_ADDR;
    err = FALSE;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIDma(0, buffer, RTC_SRAM_SIZE, 0, 0);
    err |= !EXISync(0);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    return !err;
}

void __OSInitSram(void) {
    SramControlBlock* scb = &Scb_80640E40;
    Scb_80640E40.locked = Scb_80640E40.enabled = FALSE;
    scb->sync = ReadSram(Scb_80640E40.sram);
    scb->offset = RTC_SRAM_SIZE;
}
