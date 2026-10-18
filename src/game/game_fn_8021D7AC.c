typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef int BOOL;

/* Memory card control block; one per EXI channel (0x110 bytes). */
typedef struct CardControl {
    u8 pad00[0x14];
    s32 latency;
    u8 pad18[0x80 - 0x18];
    u8 *workArea;
    u8 pad84[0x110 - 0x84];
} CardControl;

extern CardControl __CARDBlock[];
extern BOOL EXISelect(s32 chan, u32 dev, u32 freq);
extern BOOL EXIDeselect(s32 chan);
extern BOOL EXIImmEx(s32 chan, void *buf, s32 len, u32 type);
extern void *memset(void *, int, unsigned long);

/* Issue a card read-array command (0x52) and read rlen bytes into rbuf. */
s32 ReadArrayUnlock(s32 chan, u32 data, void *rbuf, s32 rlen, BOOL mode) {
    CardControl *card;
    BOOL err;
    u8 cmd[5];

    card = &__CARDBlock[chan];
    if (!EXISelect(chan, 0, 4)) {
        return -3;
    }

    data &= 0xFFFFF000;
    memset(cmd, 0, 5);
    cmd[0] = 0x52;
    if (mode == 0) {
        cmd[1] = (u8)((data >> 29) & 3);
        cmd[2] = (u8)(data >> 21);
        cmd[3] = (u8)((data >> 19) & 3);
        cmd[4] = (u8)((data >> 12) & 0x7F);
    } else {
        cmd[1] = (u8)(data >> 24);
        cmd[2] = (u8)((data & 0x00FF0000) >> 16);
    }

    err = 0;
    err |= !EXIImmEx(chan, cmd, 5, 1);
    err |= !EXIImmEx(chan, card->workArea + 0x200, card->latency, 1);
    err |= !EXIImmEx(chan, rbuf, rlen, 0);
    err |= !EXIDeselect(chan);

    return err ? -3 : 0;
}
