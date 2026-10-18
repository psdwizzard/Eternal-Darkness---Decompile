typedef signed int s32;

extern s32 Packet_80640B68[][8];
extern s32 Si_802FCA20[5];

s32 SIIsChanBusy(s32 chan)
{
    s32 result = 1;

    if (Packet_80640B68[chan][0] == -1 && Si_802FCA20[0] != chan) {
        result = 0;
    }
    return result;
}
