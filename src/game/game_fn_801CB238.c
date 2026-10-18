typedef unsigned char u8;

extern u8 inpChannelDefaults[];
extern u8 inpFXChannelDefaults[];

u8* inpGetChannelDefaults(int index, int layer)
{
    if ((u8)layer == 0xFF) {
        return inpFXChannelDefaults + (u8)index;
    }
    return inpChannelDefaults + (u8)layer * 16 + (u8)index;
}
