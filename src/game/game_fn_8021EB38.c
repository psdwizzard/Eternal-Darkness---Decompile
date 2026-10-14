/* Return the current memory card file allocation table. */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct CARDControl {
    u8 pad00[0x88];
    u16 *currentFat;
    u8 pad8C[0x110 - 0x8C];
} CARDControl;

u16 *fn_8021EB38(CARDControl *card)
{
    return card->currentFat;
}
