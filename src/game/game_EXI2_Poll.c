/* EXI2_Poll (0x8022E248, 264 bytes). */

typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;
typedef struct OSContext OSContext;
typedef void (*EXICallback)(s32, OSContext *);

extern int fn_8022DF68(int clock);
extern int fn_8022DAE0(void *buffer, s32 length, u32 type, EXICallback callback);
extern void fn_8022DD24(void);
extern int fn_800F9FE4(const char *format, ...);
extern char lbl_802FF820[];
extern u8 *lbl_8064C4C0;
extern int lbl_8064DBFC;

volatile u32 __PIRegs[12] : 0xCC003000;

static inline void EXI2_WriteCmd(u32 cmd)
{
    fn_8022DAE0(&cmd, 2, 1, 0);
    fn_8022DD24();
}

static inline int EXI2_Select(void)
{
    int result = 0;
    while (result == 0) {
        result = fn_8022DF68(5);
    }
    return result;
}

/* Select the debug port and consume its initial status word once. */
static inline int EXI2_Begin(void)
{
    int ok;
    u32 status;

    if (lbl_8064DBFC != 0) {
        ok = 1;
    } else {
        if (EXI2_Select() == 0) {
            fn_800F9FE4(lbl_802FF820);
            ok = 0;
        } else {
            ok = 1;
            lbl_8064DBFC = 1;
            EXI2_WriteCmd(0);
            fn_8022DAE0(&status, 2, 0, 0);
            fn_8022DD24();
        }
    }
    return ok;
}

/* Latch the pending input and acknowledge the PI debug interrupt. */
static inline void EXI2_Acknowledge(void)
{
    if (*lbl_8064C4C0 == 0) {
        u32 interrupts = __PIRegs[0] & 0x1000;
        *lbl_8064C4C0 = 1;
        __PIRegs[0] = interrupts;
    }
}

u32 EXI2_Poll(void)
{
    u32 data;

    if (!(__PIRegs[0] & 0x1000) && *lbl_8064C4C0 == 0) {
        data = 0;
    } else {
        EXI2_Begin();
        fn_8022DAE0(&data, 4, 0, 0);
        fn_8022DD24();
        EXI2_Acknowledge();
    }
    return data;
}
