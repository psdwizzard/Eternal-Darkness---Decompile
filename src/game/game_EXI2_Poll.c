/* EXI2_Poll (0x8022E248, 264 bytes). */

typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;
typedef struct OSContext OSContext;
typedef void (*EXICallback)(s32, OSContext *);

extern int AmcEXISelect(int clock);
extern int AmcEXIImm(void *buffer, s32 length, u32 type, EXICallback callback);
extern void AmcEXISync(void);
extern int printf(const char *format, ...);
extern char lbl_802FF820[];
extern u8 *pucEXI2InputPending;
extern int fExi2Selected;

volatile u32 __PIRegs[12] : 0xCC003000;

static inline void EXI2_WriteCmd(u32 cmd)
{
    AmcEXIImm(&cmd, 2, 1, 0);
    AmcEXISync();
}

static inline int EXI2_Select(void)
{
    int result = 0;
    while (result == 0) {
        result = AmcEXISelect(5);
    }
    return result;
}

/* Select the debug port and consume its initial status word once. */
static inline int EXI2_Begin(void)
{
    int ok;
    u32 status;

    if (fExi2Selected != 0) {
        ok = 1;
    } else {
        if (EXI2_Select() == 0) {
            printf(lbl_802FF820);
            ok = 0;
        } else {
            ok = 1;
            fExi2Selected = 1;
            EXI2_WriteCmd(0);
            AmcEXIImm(&status, 2, 0, 0);
            AmcEXISync();
        }
    }
    return ok;
}

/* Latch the pending input and acknowledge the PI debug interrupt. */
static inline void EXI2_Acknowledge(void)
{
    if (*pucEXI2InputPending == 0) {
        u32 interrupts = __PIRegs[0] & 0x1000;
        *pucEXI2InputPending = 1;
        __PIRegs[0] = interrupts;
    }
}

u32 EXI2_Poll(void)
{
    u32 data;

    if (!(__PIRegs[0] & 0x1000) && *pucEXI2InputPending == 0) {
        data = 0;
    } else {
        EXI2_Begin();
        AmcEXIImm(&data, 4, 0, 0);
        AmcEXISync();
        EXI2_Acknowledge();
    }
    return data;
}
