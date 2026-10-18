typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void hwDisableIrq(void);
extern void hwEnableIrq(void);
extern void synthVolume(u8, u16, u8, u8, u32);

void sndMasterVolume(u8 volume, u16 time, u8 music, u8 effects)
{
    hwDisableIrq();
    if (music) {
        synthVolume(volume, time, 0x15, 0, -1);
    }
    if (effects) {
        synthVolume(volume, time, 0x16, 0, -1);
    }
    hwEnableIrq();
}
