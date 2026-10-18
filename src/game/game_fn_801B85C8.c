typedef unsigned char u8;

extern u8 sndActive;
extern u8 synthMasterFader[];

void synthSetMusicVolumeType(u8 index, u8 value)
{
    if (sndActive != 0) {
        synthMasterFader[index * 0x30 + 0x2D] = value;
    }
}
