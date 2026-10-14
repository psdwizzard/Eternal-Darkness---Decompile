/* PADSetSpec: select the decoder for the controller's data format. */
typedef unsigned long u32;
typedef signed long s32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed char s8;

typedef struct PadStatus {
    u16 button;
    s8 stickX, stickY;
    s8 substickX, substickY;
    u8 triggerL, triggerR;
    u8 analogA, analogB;
} PadStatus;

typedef struct PadOut {
    u16 button;
    s8 stickX, stickY;
    s8 substickX, substickY;
    u8 triggerL, triggerR;
    u8 analogA, analogB;
} PadOut;

typedef struct DecodedInput {
    u16 buttons;
    s8 stickX, stickY;
    s8 substickX, substickY;
    u8 triggerL, triggerR;
    u8 analogA, analogB;
} DecodedInput;

typedef struct PackedInput {
    unsigned int w0, w1;
} PackedInput;

typedef void (*PadDecoder)(s32, PadStatus*, u32*);
extern void fn_802196A0(s32 chan, PadStatus* status, u32* data);
extern void fn_80219814(s32 chan, PadOut* status, u32* data);
extern void fn_80219988(int chan, DecodedInput* out, PackedInput* in);
extern unsigned int __PADSpec;
extern unsigned int lbl_8064C434;
extern PadDecoder lbl_8064C438;

void fn_80219640(unsigned int spec) {
    __PADSpec = 0;
    switch (spec) {
    case 0:
        lbl_8064C438 = fn_802196A0;
        break;
    case 1:
        lbl_8064C438 = (PadDecoder)fn_80219814;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        lbl_8064C438 = (PadDecoder)fn_80219988;
        break;
    }
    lbl_8064C434 = spec;
}
