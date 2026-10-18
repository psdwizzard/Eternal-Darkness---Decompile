typedef unsigned char u8;

extern u8 midi_lastNote[];
extern u8 fx_lastNote[];

u8 inpGetMidiLastNote(int index, int layer)
{
    u8* source;

    if ((u8)layer != 0xFF) {
        source = midi_lastNote + (u8)layer * 16 + (u8)index;
        return *source;
    }
    source = fx_lastNote + (u8)index;
    return *source;
}
