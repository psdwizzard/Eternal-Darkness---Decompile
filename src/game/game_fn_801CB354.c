typedef unsigned char u8;
typedef unsigned int u32;

typedef struct SYNTH_VOICE {
    u8 pad[0xF4];
    u32 id;
} SYNTH_VOICE;

extern u8 lbl_8062A230[];

#define INP_MIDI_CTRL_GLOBAL_OFFSET 0x43C0
#define INP_MIDI_CTRL_BANK_SIZE 0x86

void fn_801CB354(u8 controller, SYNTH_VOICE* dstState, SYNTH_VOICE* srcState)
{
    u32 ctrl;
    u32 dstVoice;
    u32 srcVoice;
    u8* stateBase;
    u8* bank;

    ctrl = controller & 0xff;
    stateBase = lbl_8062A230;
    dstVoice = dstState->id & 0xff;
    srcVoice = srcState->id & 0xff;

    if (ctrl < 0x40) {
        ctrl = controller & 0x1f;
        *(stateBase + INP_MIDI_CTRL_GLOBAL_OFFSET + dstVoice * INP_MIDI_CTRL_BANK_SIZE + ctrl) =
            *(stateBase + INP_MIDI_CTRL_GLOBAL_OFFSET + srcVoice * INP_MIDI_CTRL_BANK_SIZE + ctrl);
        bank = stateBase + INP_MIDI_CTRL_GLOBAL_OFFSET + 0x20;
        *(bank + dstVoice * INP_MIDI_CTRL_BANK_SIZE + ctrl) = *(bank + srcVoice * INP_MIDI_CTRL_BANK_SIZE + ctrl);
        return;
    }
    if (controller == 0x80 || controller == 0x81) {
        ctrl = controller & 0xfe;
        *(stateBase + INP_MIDI_CTRL_GLOBAL_OFFSET + dstVoice * INP_MIDI_CTRL_BANK_SIZE + ctrl) =
            *(stateBase + INP_MIDI_CTRL_GLOBAL_OFFSET + srcVoice * INP_MIDI_CTRL_BANK_SIZE + ctrl);
        bank = stateBase + INP_MIDI_CTRL_GLOBAL_OFFSET + 1;
        *(bank + dstVoice * INP_MIDI_CTRL_BANK_SIZE + ctrl) = *(bank + srcVoice * INP_MIDI_CTRL_BANK_SIZE + ctrl);
        return;
    }
    if (controller == 0x84 || controller == 0x85) {
        ctrl = controller & 0xfe;
        *(stateBase + INP_MIDI_CTRL_GLOBAL_OFFSET + dstVoice * INP_MIDI_CTRL_BANK_SIZE + ctrl) =
            *(stateBase + INP_MIDI_CTRL_GLOBAL_OFFSET + srcVoice * INP_MIDI_CTRL_BANK_SIZE + ctrl);
        bank = stateBase + INP_MIDI_CTRL_GLOBAL_OFFSET + 1;
        *(bank + dstVoice * INP_MIDI_CTRL_BANK_SIZE + ctrl) = *(bank + srcVoice * INP_MIDI_CTRL_BANK_SIZE + ctrl);
        return;
    }
    *(stateBase + INP_MIDI_CTRL_GLOBAL_OFFSET + dstVoice * INP_MIDI_CTRL_BANK_SIZE + ctrl) =
        *(stateBase + INP_MIDI_CTRL_GLOBAL_OFFSET + srcVoice * INP_MIDI_CTRL_BANK_SIZE + ctrl);
}
