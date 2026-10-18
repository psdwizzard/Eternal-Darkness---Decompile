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
extern void SPEC0_MakeStatus(s32 chan, PadStatus* status, u32* data);
extern void SPEC1_MakeStatus(s32 chan, PadOut* status, u32* data);
extern void SPEC2_MakeStatus(int chan, DecodedInput* out, PackedInput* in);
extern unsigned int __PADSpec;
extern unsigned int Spec;
extern PadDecoder MakeStatus;

void PADSetSpec(unsigned int spec) {
    __PADSpec = 0;
    switch (spec) {
    case 0:
        MakeStatus = SPEC0_MakeStatus;
        break;
    case 1:
        MakeStatus = (PadDecoder)SPEC1_MakeStatus;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        MakeStatus = (PadDecoder)SPEC2_MakeStatus;
        break;
    }
    Spec = spec;
}
