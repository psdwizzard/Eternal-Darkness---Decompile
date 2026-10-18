typedef signed int s32;
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct SIControl {
    s32 chan;
    u32 unused_04;
    u32 inputBytes;
    void* input;
    u32 unused_10;
    u32 type[4];
} SIControl;

extern SIControl Si_802FCA20;
extern u64 TypeTime_80640C88[4];
extern u64 XferTime[4];
extern u64 __OSGetSystemTime(void);

typedef struct SIRegisters {
    u32 poll[13];
    u32 status;
    u32 comcsr;
    u32 unused_3c[17];
    u32 ram[32];
} SIRegisters;

volatile SIRegisters __SIRegs : 0xCC006400;

u32 CompleteTransfer(void)
{
    u32 i;
    u32* input;
    volatile u32* inputBytes;
    u32 count;
    u32 data;
    u32 error;
    SIControl* si;

    error = __SIRegs.comcsr;
    si = &Si_802FCA20;
    __SIRegs.status = (__SIRegs.status | 0x80000000) & ~1;

    if (si->chan != -1) {
        XferTime[si->chan] = __OSGetSystemTime();
        input = si->input;
        inputBytes = &si->inputBytes;
        count = *inputBytes >> 2;

        for (i = 0; i < count; i++) {
            *input++ = __SIRegs.ram[i];
        }

        count = *inputBytes & 3;
        if (count != 0) {
            u8* bytes = (u8*)input;
            data = __SIRegs.ram[i];
            for (i = 0; i < count; i++) {
                *bytes++ = data >> ((3 - i) * 8);
            }
        }

        if (__SIRegs.status & 0x20000000) {
            error >>= (3 - si->chan) * 8;
            error &= 0xF;
            if ((error & 8) && !(si->type[si->chan] & 0x80)) {
                si->type[si->chan] = 8;
            }
            if (error == 0) {
                error = 4;
            }
        } else {
            TypeTime_80640C88[si->chan] = __OSGetSystemTime();
            error = 0;
        }
        si->chan = -1;
    }
    return error;
}
