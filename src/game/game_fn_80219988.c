typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct PackedInput {
    u32 w0;
    u32 w1;
} PackedInput;

typedef struct DecodedInput {
    u16 buttons;
    s8 stickX;
    s8 stickY;
    s8 substickX;
    s8 substickY;
    u8 triggerL;
    u8 triggerR;
    u8 analogA;
    u8 analogB;
} DecodedInput;

typedef struct InputOrigin {
    u16 buttons;
    s8 stickX;
    s8 stickY;
    s8 substickX;
    s8 substickY;
    u8 triggerL;
    u8 triggerR;
    u8 pad[4];
} InputOrigin;

extern u32 lbl_8064C430;
extern InputOrigin lbl_80641C20[];

static inline s8 ClampStick(s8 origin, s8 value) {
    s8 limit;

    if (origin > 0) {
        limit = origin - 0x80;
        if (value < limit) {
            value = limit;
        }
    } else if (origin < 0) {
        limit = origin + 0x7F;
        if (limit < value) {
            value = limit;
        }
    }
    value -= origin;
    return value;
}

#define CLAMP_STICK(field) out->field = ClampStick(org->field, out->field);

static inline u8 ClampTrigger(u8 value, u8 origin) {
    if (value < origin) {
        value = origin;
    }
    value -= origin;
    return value;
}

#define CLAMP_TRIGGER(field) out->field = ClampTrigger(out->field, org->field);

void fn_80219988(int chan, DecodedInput* out, PackedInput* in) {
    InputOrigin* org;

    out->buttons = (in->w0 >> 16) & 0x3FFF;
    out->stickX = in->w0 >> 8;
    out->stickY = in->w0;

    switch (lbl_8064C430 & 0x700) {
    case 0x000:
    case 0x500:
    case 0x600:
    case 0x700:
        out->substickX = in->w1 >> 24;
        out->substickY = in->w1 >> 16;
        out->triggerL = (in->w1 >> 8) & 0xF0;
        out->triggerR = (in->w1 >> 4) & 0xF0;
        out->analogA = in->w1 & 0xF0;
        out->analogB = (in->w1 << 4) & 0xF0;
        break;
    case 0x100:
        out->substickX = (in->w1 >> 28) << 4;
        out->substickY = ((in->w1 >> 24) & 0xF) << 4;
        out->triggerL = in->w1 >> 16;
        out->triggerR = in->w1 >> 8;
        out->analogA = in->w1 & 0xF0;
        out->analogB = (in->w1 << 4) & 0xF0;
        break;
    case 0x200:
        out->substickX = (in->w1 >> 28) << 4;
        out->substickY = ((in->w1 >> 24) & 0xF) << 4;
        out->triggerL = (in->w1 >> 16) & 0xF0;
        out->triggerR = (in->w1 >> 12) & 0xF0;
        out->analogA = in->w1 >> 8;
        out->analogB = in->w1;
        break;
    case 0x300:
        out->substickX = in->w1 >> 24;
        out->substickY = in->w1 >> 16;
        out->triggerL = in->w1 >> 8;
        out->triggerR = in->w1;
        out->analogA = 0;
        out->analogB = 0;
        break;
    case 0x400:
        out->substickX = in->w1 >> 24;
        out->substickY = in->w1 >> 16;
        out->triggerL = 0;
        out->triggerR = 0;
        out->analogA = in->w1 >> 8;
        out->analogB = in->w1;
        break;
    }

    out->stickX -= 0x80;
    org = &lbl_80641C20[chan];
    out->stickY -= 0x80;
    out->substickX -= 0x80;
    out->substickY -= 0x80;

    CLAMP_STICK(stickX)
    CLAMP_STICK(stickY)
    CLAMP_STICK(substickX)
    CLAMP_STICK(substickY)
    CLAMP_TRIGGER(triggerL)
    CLAMP_TRIGGER(triggerR)
}
