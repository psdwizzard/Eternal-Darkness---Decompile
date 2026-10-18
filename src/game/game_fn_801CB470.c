typedef unsigned char u8;

extern u8 midi_lastNote[];
extern u8 fx_lastNote[];

void inpSetMidiLastNote(int index, int layer, u8 value)
{
    u8* destination;

    if ((u8)layer != 0xFF) {
        destination = midi_lastNote + (u8)layer * 16 + (u8)index;
        *destination = value;
        return;
    }
    destination = fx_lastNote + (u8)index;
    *destination = value;
}
