typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TRKEvent {
    u8 type;
    u8 pad[3];
    u32 id;
    int buffer;
} TRKEvent;

extern u8 gTRKState[];
extern u8 gTRKCPUState[];

extern void fn_800EEF1C(TRKEvent *event, u8 type);
extern int fn_800EEF34(const TRKEvent *event);
extern int fn_800F4CC0(void *data, u32 start, u32 *length,
                       int accessOptions, int read);

void TRKPostInterruptEvent(void)
{
    TRKEvent event;
    u32 instruction;
    u32 length;
    u8 type;

    if (*(int *)(gTRKState + 0x9C) != 0) {
        *(int *)(gTRKState + 0x9C) = 0;
        return;
    }

    switch ((u16)*(u32 *)(gTRKCPUState + 0x2F8)) {
    case 0x700:
    case 0xD00:
        length = sizeof(instruction);
        fn_800F4CC0(&instruction, *(u32 *)(gTRKCPUState + 0x80),
                    &length, 0, 1);
        if (instruction == 0x0FE00000) {
            type = 5;
        } else {
            type = 3;
        }
        break;
    default:
        type = 4;
        break;
    }

    fn_800EEF1C(&event, type);
    fn_800EEF34(&event);
}
