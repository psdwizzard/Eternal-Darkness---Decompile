/* Return the number of bytes transferred on a memory card channel. */

typedef unsigned char u8;
typedef signed int s32;

/* Memory card control block; one per EXI channel (0x110 bytes). */
typedef struct CardControl {
    u8 pad00[0xB8];
    s32 xferred;
    u8 padBC[0x110 - 0xBC];
} CardControl;

extern CardControl __CARDBlock[];

s32 CARDGetXferredBytes(s32 channel)
{
    return __CARDBlock[channel].xferred;
}
