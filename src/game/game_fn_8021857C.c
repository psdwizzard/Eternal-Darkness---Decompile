typedef signed int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed char s8;

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
    s8 err;
} PadStatus;

extern u32 SIGetType(s32 chan);

extern u32 lbl_8064C42C; /* XPatchBits */
extern u32 lbl_8064C430; /* AnalogMode */
extern PadStatus lbl_80641C20[4]; /* Origin */

/* PAD UpdateOrigin */
void fn_8021857C(s32 chan)
{
    PadStatus* origin;
    u32 chanBit = 0x80000000 >> chan;

    origin = &lbl_80641C20[chan];
    switch (lbl_8064C430 & 0x700) {
    case 0x000:
    case 0x500:
    case 0x600:
    case 0x700:
        origin->triggerL &= ~15;
        origin->triggerR &= ~15;
        origin->analogA &= ~15;
        origin->analogB &= ~15;
        break;
    case 0x100:
        origin->substickX &= ~15;
        origin->substickY &= ~15;
        origin->analogA &= ~15;
        origin->analogB &= ~15;
        break;
    case 0x200:
        origin->substickX &= ~15;
        origin->substickY &= ~15;
        origin->triggerL &= ~15;
        origin->triggerR &= ~15;
        break;
    case 0x300:
        break;
    case 0x400:
        break;
    }

    origin->stickX -= 128;
    origin->stickY -= 128;
    origin->substickX -= 128;
    origin->substickY -= 128;

    if (lbl_8064C42C & chanBit) {
        if (64 < origin->stickX && (SIGetType(chan) & 0xFFFF0000) == 0x09000000) {
            origin->stickX = 0;
        }
    }
}
