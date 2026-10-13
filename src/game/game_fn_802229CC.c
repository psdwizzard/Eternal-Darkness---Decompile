/* CARDGetSerialNo: combine the four words of the card's serial number. */
typedef signed int s32;
typedef unsigned long long u64;

typedef struct CARDControl {
    unsigned char reserved00[0x80];
    void *workArea;
} CARDControl;

extern s32 fn_8021D2BC(s32 chan, CARDControl **card);
extern s32 fn_8021D374(CARDControl *card, s32 result);

s32 fn_802229CC(s32 chan, u64 *serialNo)
{
    CARDControl *card;
    s32 result;
    unsigned char *serial;
    u64 value;
    s32 i;

    if (chan < 0 || chan >= 2) {
        return -128;
    }
    result = fn_8021D2BC(chan, &card);
    if (result < 0) {
        return result;
    }

    serial = (unsigned char *)card->workArea;
    value = 0;
    for (i = 0; i < 32; i += 8) {
        value ^= *(u64 *)(serial + i);
    }
    *serialNo = value;
    return fn_8021D374(card, 0);
}
