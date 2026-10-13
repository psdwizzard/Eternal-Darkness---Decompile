typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef int BOOL;
typedef int DSError;

/* MetroTRK: TRKTargetAddStopInfo */

typedef struct TRKBuffer {
    u32 unk0;
    u32 unk4;
    u32 length;
    u32 position;
    u8 data[1];
} TRKBuffer;

typedef struct TRKCPUState {
    u32 GPR[32];        /* 0x000 */
    u32 PC;             /* 0x080 */
    u8 pad84[0x14];     /* 0x084 */
    u64 FPR[32];        /* 0x098 */
    u8 pad198[0x160];   /* 0x198 */
    u32 exceptionID;    /* 0x2F8 */
} TRKCPUState;

extern TRKCPUState gTRKCPUState;

extern int fn_800EFA84(TRKBuffer *buffer, u32 value);
extern int fn_800EFAE8(TRKBuffer *buffer, u16 value);
extern void fn_800EF9FC(TRKBuffer *buffer, u64 value);
extern DSError fn_800F4CC0(void *data, u32 start, u32 *length, int accessOptions, BOOL read);

#define DS_InvalidMemory 0x700

void fn_800F4080(TRKBuffer *buffer)
{
    DSError error;
    u32 instruction;
    u32 length;
    int i;

    error = fn_800EFA84(buffer, gTRKCPUState.PC);
    if (error == 0) {
        /* Inlined TRKTargetReadInstruction */
        length = sizeof(instruction);
        error = fn_800F4CC0(&instruction, gTRKCPUState.PC, &length, 0, 1);
        if (error == 0 && length != sizeof(instruction)) {
            error = DS_InvalidMemory;
        }
    }
    if (error == 0) {
        error = fn_800EFA84(buffer, instruction);
    }
    if (error == 0) {
        error = fn_800EFAE8(buffer, gTRKCPUState.exceptionID);
    }
    if (error == 0) {
        for (i = 0; i < 32; i++) {
            fn_800EFA84(buffer, (u16)gTRKCPUState.GPR[i]);
        }
        for (i = 0; i < 32; i++) {
            fn_800EF9FC(buffer, (u16)gTRKCPUState.FPR[i]);
        }
    }
}
