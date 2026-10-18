typedef unsigned char u8;

extern u8 inpChannelDefaults[];
extern u8 inpFXChannelDefaults[];

void inpResetChannelDefaults(int index, int layer)
{
    u8* value;

    if ((u8)layer != 0xFF) {
        value = inpChannelDefaults + (u8)layer * 16 + (u8)index;
    } else {
        value = inpFXChannelDefaults + (u8)index;
    }
    *value = 2;
}
