typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void hwDisableIrq(void);
extern void hwEnableIrq(void);
extern void synthVolume(u8, u16, u8, u8, u32);

void sndVolume(u8 volume, u16 time, u8 volume_group)
{
    hwDisableIrq();
    synthVolume(volume, time, volume_group, 0, -1);
    hwEnableIrq();
}
