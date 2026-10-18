typedef unsigned char u8;
typedef unsigned int u32;

extern u8 synthInfo[];
extern u32 synthAuxACallback[];
extern u32 synthAuxBCallback[];
extern u8 synthAuxAMIDI;
extern u8 synthAuxBMIDI;
extern u8* synthVoice;
extern u32 hwIsActive(int);
extern void hwOff(int);
extern void voiceKillSound(u32);
extern void hwDisableIrq(void);
extern void hwEnableIrq(void);
extern void hwDeactivateStudio(int);

void synthDeactivateStudio(int arg0)
{
    int offset;
    u32 i;

    for (i = 0, offset = 0; i < synthInfo[0x210]; offset += 0x404, i++) {
        u8* entry = synthVoice + offset;
        if ((u8)arg0 == entry[0x11F]) {
            if (*(u32*)(entry + 0xF4) != (u32)-1) {
                voiceKillSound(*(u32*)(*(u8**)(entry + 0xF8) + 8));
            } else if (hwIsActive(i)) {
                hwOff(i);
            }
        }
    }

    hwDisableIrq();
    {
        u32 word_offset;
        u8 index = (u8)arg0;
        word_offset = (u32)index * 4;
        *(u32*)((u8*)synthAuxACallback + word_offset) = 0;
        *(u32*)((u8*)synthAuxBCallback + word_offset) = 0;
        (&synthAuxAMIDI)[index] = 0xFF;
        (&synthAuxBMIDI)[index] = 0xFF;
    }
    hwEnableIrq();
    hwDeactivateStudio(arg0);
}
