typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef int BOOL;

typedef struct CardControl {
    s32 attached;
    u8 reserved04[4];
    u16 size;
    u16 reserved0A;
    s32 sectorSize;
    u8 reserved10[0x14];
    s32 mountStep;
    u8 reserved28[0xE8];
} CardControl;

extern CardControl __CARDBlock[];
extern s32 SectorSizeTable[];
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern s32 EXIProbeEx(s32 channel);
extern u32 EXIGetState(s32 channel);
extern s32 EXIGetID(s32 channel, u32 device, u32 *id);
extern s32 IsCard(u32 id);

/* CARDProbeEx */
s32 CARDProbeEx(s32 chan, s32 *memSize, s32 *sectorSize)
{
    CardControl *card;
    BOOL enabled;
    s32 result;
    s32 probe;
    u32 id;

    if (chan < 0 || chan >= 2) {
        return -128;
    }
    if (*(u8 *)0x800030E3 & 0x80) {
        return -3;
    }

    card = &__CARDBlock[chan];
    enabled = OSDisableInterrupts();

    probe = EXIProbeEx(chan);
    if (probe == -1) {
        result = -3;
    } else if (probe == 0) {
        result = -1;
    } else if (card->attached) {
        if (card->mountStep < 1) {
            result = -1;
        } else {
            if (memSize) {
                *memSize = card->size;
            }
            if (sectorSize) {
                *sectorSize = card->sectorSize;
            }
            result = 0;
        }
    } else if (EXIGetState(chan) & 8) {
        result = -2;
    } else if (!EXIGetID(chan, 0, &id)) {
        result = -1;
    } else if (IsCard(id)) {
        if (memSize) {
            *memSize = (s32)(id & 0xFC);
        }
        if (sectorSize) {
            *sectorSize = SectorSizeTable[(id & 0x00003800) >> 11];
        }
        result = 0;
    } else {
        result = -2;
    }

    OSRestoreInterrupts(enabled);
    return result;
}
