typedef unsigned int u32;
typedef unsigned char u8;

typedef struct TRKEvent {
    u8 type;
    u8 pad[3];
    unsigned id;
    int buffer;
} TRKEvent;

typedef struct TRKCPUState {
    u32 GPR[32];
    u32 PC;
} TRKCPUState;

extern TRKCPUState gTRKCPUState;

extern void TRKConstructEvent(TRKEvent *event, u8 type);
extern int TRKPostEvent(const TRKEvent *event);
extern int HandleOpenFileSupportRequest(const char *name, u8 kind, u32 *value, u8 *status);
extern int HandleCloseFileSupportRequest(u32 handle, u8 *status);
extern int HandlePositionFileSupportRequest(u32 handle, u32 *position, u8 mode, u8 *status);
extern int TRKSuppAccessFile(u32 file_handle, u8 *data, u32 *count, u8 *io_result, int need_reply, int read);
extern void TRK_flush_cache(void *address, unsigned int length);

#define DSMSG_ReadFile     0xD1
#define DSMSG_WriteFile    0xD0
#define DSMSG_OpenFile     0xD2
#define DSMSG_CloseFile    0xD3
#define DSMSG_PositionFile 0xD4

int TRKTargetSupportRequest(void)
{
    int error;
    u8 command;
    u32 *length;
    TRKEvent event;
    u8 io_result;

    command = gTRKCPUState.GPR[3];

    if (command != DSMSG_ReadFile && command != DSMSG_WriteFile
        && command != DSMSG_OpenFile && command != DSMSG_CloseFile
        && command != DSMSG_PositionFile) {
        TRKConstructEvent(&event, 4);
        TRKPostEvent(&event);
        return 0;
    }

    if (command == DSMSG_OpenFile) {
        error = HandleOpenFileSupportRequest((const char *)gTRKCPUState.GPR[4], gTRKCPUState.GPR[5],
                            (u32 *)gTRKCPUState.GPR[6], &io_result);
        if (io_result == 0 && error != 0) {
            io_result = 1;
        }
        gTRKCPUState.GPR[3] = io_result;
    } else if (command == DSMSG_CloseFile) {
        error = HandleCloseFileSupportRequest(gTRKCPUState.GPR[4], &io_result);
        if (io_result == 0 && error != 0) {
            io_result = 1;
        }
        gTRKCPUState.GPR[3] = io_result;
    } else if (command == DSMSG_PositionFile) {
        u32 position = *(u32 *)gTRKCPUState.GPR[5];
        error = HandlePositionFileSupportRequest(gTRKCPUState.GPR[4], &position, gTRKCPUState.GPR[6], &io_result);
        if (io_result == 0 && error != 0) {
            io_result = 1;
        }
        gTRKCPUState.GPR[3] = io_result;
        *(u32 *)gTRKCPUState.GPR[5] = position;
    } else {
        length = (u32 *)gTRKCPUState.GPR[5];
        error = TRKSuppAccessFile((u8)gTRKCPUState.GPR[4], (u8 *)gTRKCPUState.GPR[6], length,
                            &io_result, 1, command == DSMSG_ReadFile);
        if (io_result == 0 && error != 0) {
            io_result = 1;
        }
        gTRKCPUState.GPR[3] = io_result;
        if (command == DSMSG_ReadFile) {
            TRK_flush_cache((void *)gTRKCPUState.GPR[6], *length);
        }
    }
    gTRKCPUState.PC += 4;
    return error;
}
