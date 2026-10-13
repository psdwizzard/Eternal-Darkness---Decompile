typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;
typedef struct OSContext OSContext;
typedef void (*EXICallback)(s32, OSContext *);

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int enabled);
extern int fn_8022DF68(int clock);
extern int fn_8022DAE0(void *buffer, s32 length, u32 type, EXICallback callback);
extern void fn_8022DD24(void);
extern int fn_8022DFE8(void);
extern void fn_8022E0E0(void);
extern u8 *lbl_8064C4C0;
extern EXICallback lbl_8064DC00;

static inline void EXI2_WriteImmediate(u32 data, s32 length)
{
    fn_8022DAE0(&data, length, 1, 0);
    fn_8022DD24();
}

static inline void EXI2_WriteCmd(u32 command)
{
    u32 data = command;
    EXI2_WriteImmediate(data, 2);
}

static inline int EXI2_Select(void)
{
    int selected = 0;
    while (selected == 0) {
        selected = fn_8022DF68(5);
    }
    return selected;
}

void EXI2_Init(u8 **inputPending, EXICallback callback)
{
    u32 data;
    u32 configuration;
    u32 command;
    int enabled;

    *inputPending = lbl_8064C4C0;
    enabled = OSDisableInterrupts();
    lbl_8064DC00 = callback;
    OSRestoreInterrupts(enabled);
    fn_8022E0E0();

    data = 0;
    configuration = 0x01000003;
    EXI2_Select();
    command = 0x80000000;
    EXI2_WriteCmd(command);
    fn_8022DAE0(&configuration, 4, 1, 0);
    fn_8022DD24();
    fn_8022DAE0(&data, 4, 1, 0);
    fn_8022DD24();
    fn_8022DFE8();
}
