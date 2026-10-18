typedef int BOOL;
typedef int s32;
typedef unsigned int u32;

typedef struct EXIControl {
    void *exiCallback;
    void *tcCallback;
    char pad_08[0x18];
    s32 idTime;
    char pad_24[0x1C];
} EXIControl;

extern EXIControl Ecb_80640AA8[3];
extern BOOL __EXIProbe_80206F50(s32 chan);
extern BOOL EXIGetID(s32 chan, u32 dev, u32 *id);

volatile s32 __OSDeviceCode[3] : 0x800030C0;

s32 EXIProbeEx(s32 chan)
{
    EXIControl *exi = &Ecb_80640AA8[chan];
    u32 id;
    BOOL result;

    result = __EXIProbe_80206F50(chan);
    if (result && !exi->idTime) {
        if (EXIGetID(chan, 0, &id)) {
            result = 1;
        } else {
            result = 0;
        }
    }

    if (result) {
        return 1;
    }
    if (__OSDeviceCode[chan] != 0) {
        return 0;
    }
    return -1;
}
