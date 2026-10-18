typedef signed int s32;
typedef unsigned int u32;

typedef void (*SITypeCallback)(s32 chan, u32 type);

extern u32 Type_802FCA34[4];
extern SITypeCallback TypeCallback[4][4];

extern u32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(u32 enabled);
extern u32 SIGetType(s32 chan);

u32 SIGetTypeAsync(s32 chan, SITypeCallback callback)
{
    u32 enabled;
    u32 type;
    s32 i;

    enabled = OSDisableInterrupts();
    type = SIGetType(chan);

    if (Type_802FCA34[chan] & 0x80) {
        for (i = 0; i < 4; i++) {
            if (TypeCallback[chan][i] == callback) {
                break;
            }
            if (TypeCallback[chan][i] == 0) {
                TypeCallback[chan][i] = callback;
                break;
            }
        }
    } else {
        callback(chan, type);
    }

    OSRestoreInterrupts(enabled);
    return type;
}
