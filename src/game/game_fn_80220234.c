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

extern CardControl lbl_80641C60[];
extern s32 lbl_802FECE0[];
extern BOOL OSDisableInterrupts(void);
extern BOOL OSRestoreInterrupts(BOOL level);
extern s32 fn_80207144(s32 channel);
extern u32 fn_80207C88(s32 channel);
extern s32 fn_80207CC8(s32 channel, u32 device, u32 *id);
extern s32 fn_80220130(u32 id);

/* CARDProbeEx */
s32 fn_80220234(s32 chan, s32 *memSize, s32 *sectorSize)
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

    card = &lbl_80641C60[chan];
    enabled = OSDisableInterrupts();

    probe = fn_80207144(chan);
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
    } else if (fn_80207C88(chan) & 8) {
        result = -2;
    } else if (!fn_80207CC8(chan, 0, &id)) {
        result = -1;
    } else if (fn_80220130(id)) {
        if (memSize) {
            *memSize = (s32)(id & 0xFC);
        }
        if (sectorSize) {
            *sectorSize = lbl_802FECE0[(id & 0x00003800) >> 11];
        }
        result = 0;
    } else {
        result = -2;
    }

    OSRestoreInterrupts(enabled);
    return result;
}
