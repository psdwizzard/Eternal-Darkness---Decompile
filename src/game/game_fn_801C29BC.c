typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern float toneup_tab[];
extern float tonedown_tab[];
typedef struct AudioState {
    u32 rate;
    u8 pad_004[0x210];
} AudioState;

extern AudioState synthInfo;
extern float lbl_80650F58;
extern float fn_800F5C54(float);

float sndGetPitch(u32 target, u32 value)
{
    u32 high;
    float amount;

    if (value == (u32)-1) {
        value = 0x40005622;
    }
    high = value >> 24;
    if ((u8)target != high) {
        if (high < (u8)target) {
            amount = toneup_tab[(u8)target - high];
        } else {
            amount = tonedown_tab[high - (u8)target];
        }
        amount = (value & 0xFFFFFF) * amount;
    } else {
        amount = value & 0xFFFFFF;
    }
    return fn_800F5C54((lbl_80650F58 * amount) / synthInfo.rate);
}
