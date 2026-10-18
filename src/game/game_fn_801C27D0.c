typedef unsigned char u8;
typedef unsigned int u32;

extern u8 synth_last_started[8][16];
extern u8 synth_last_fxstarted[64];

void voiceInitLastStarted(void)
{
    u32 i;
    u32 j;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 16; j++) {
            synth_last_started[i][j] = 0xFF;
        }
    }
    for (i = 0; i < 64; i++) {
        synth_last_fxstarted[i] = 0xFF;
    }
}
