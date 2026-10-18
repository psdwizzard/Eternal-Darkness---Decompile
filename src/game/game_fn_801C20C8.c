typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Voice {
    u8 pad_000[0xF4];
    u32 index;
    u8 pad_0F8[0x24];
    u8 flag_11C;
    u8 pad_11D[0x2E7];
} Voice;

extern Voice* synthVoice;
extern u32 hwIsActive(u32);
extern void hwBreak(u32);
extern void voiceFree(Voice*);

void voiceUnblock(u32 index)
{
    u32 offset;

    if (index != (u32)-1) {
        if (hwIsActive(index) != 0) {
            hwBreak(index);
        }
        offset = index * 0x404;
        synthVoice[index].index = index;
        voiceFree(&synthVoice[index]);
        synthVoice[index].flag_11C = 0;
    }
}
