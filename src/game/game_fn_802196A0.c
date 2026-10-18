typedef unsigned long u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed char s8;
typedef long s32;

typedef struct PadStatus {
    u16 button;
    s8 stickX;
    s8 stickY;
    s8 substickX;
    s8 substickY;
    u8 triggerL;
    u8 triggerR;
    u8 analogA;
    u8 analogB;
} PadStatus;

void SPEC0_MakeStatus(s32 chan, PadStatus* status, u32* data) {
    status->button = 0;
    status->button |= (data[0] >> 16) & 0x0008 ? 0x0100 : 0;
    status->button |= (data[0] >> 16) & 0x0020 ? 0x0200 : 0;
    status->button |= (data[0] >> 16) & 0x0100 ? 0x0400 : 0;
    status->button |= (data[0] >> 16) & 0x0001 ? 0x0800 : 0;
    status->button |= (data[0] >> 16) & 0x0010 ? 0x1000 : 0;

    status->stickX = (s8)(data[1] >> 16);
    status->stickY = (s8)(data[1] >> 24);
    status->substickX = (s8)data[1];
    status->substickY = (s8)(data[1] >> 8);
    status->triggerL = (u8)(data[0] >> 8);
    status->triggerR = (u8)data[0];
    status->analogA = 0;
    status->analogB = 0;

    if (status->triggerL >= 0xAA) {
        status->button |= 0x0040;
    }
    if (status->triggerR >= 0xAA) {
        status->button |= 0x0020;
    }

    status->stickX -= 128;
    status->stickY -= 128;
    status->substickX -= 128;
    status->substickY -= 128;
}
