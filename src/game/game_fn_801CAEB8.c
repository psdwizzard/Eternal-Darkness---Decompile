typedef unsigned char u8;
typedef unsigned int u32;

extern u8 inpColdMIDIDefaults[];
extern u8 inpWarmMIDIDefaults[];
extern u8 midi_ctrl[];
extern u8 fx_ctrl[];
extern void* memcpy(void*, const void*, u32);
extern void inpSetMidiLastNote(u8, u8, u8);

void inpResetMidiCtrl(u8 channel, u8 set, u32 cold_reset)
{
    u8* source = cold_reset != 0 ? inpColdMIDIDefaults : inpWarmMIDIDefaults;
    u8* destination;

    if (set != 0xFF) {
        destination = midi_ctrl + set * 2144 + channel * 134;
    } else {
        destination = fx_ctrl + channel * 134;
    }

    if (cold_reset != 0) {
        memcpy(destination, source, 134);
    } else {
        u32 i;
        for (i = 0; i < 134; i++) {
            if (source[i] != 0xFF) {
                destination[i] = source[i];
            }
        }
    }

    inpSetMidiLastNote(channel, set, 0xFF);
}
