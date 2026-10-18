typedef unsigned char u8;
typedef unsigned long u32;
typedef long s32;
typedef struct OSContext OSContext;
typedef void (*EXICallback)(s32, OSContext *);

extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int enabled);
extern int AmcEXISelect(int clock);
extern int AmcEXIImm(void *buffer, s32 length, u32 type, EXICallback callback);
extern void AmcEXISync(void);
extern int AmcEXIDeselect(void);
extern void AmcEXIInit(void);
extern u8 *pucEXI2InputPending;
extern EXICallback TRK_Callback;

static inline void EXI2_WriteImmediate(u32 data, s32 length)
{
    AmcEXIImm(&data, length, 1, 0);
    AmcEXISync();
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
        selected = AmcEXISelect(5);
    }
    return selected;
}

void EXI2_Init(u8 **inputPending, EXICallback callback)
{
    u32 data;
    u32 configuration;
    u32 command;
    int enabled;

    *inputPending = pucEXI2InputPending;
    enabled = OSDisableInterrupts();
    TRK_Callback = callback;
    OSRestoreInterrupts(enabled);
    AmcEXIInit();

    data = 0;
    configuration = 0x01000003;
    EXI2_Select();
    command = 0x80000000;
    EXI2_WriteCmd(command);
    AmcEXIImm(&configuration, 4, 1, 0);
    AmcEXISync();
    AmcEXIImm(&data, 4, 1, 0);
    AmcEXISync();
    AmcEXIDeselect();
}
