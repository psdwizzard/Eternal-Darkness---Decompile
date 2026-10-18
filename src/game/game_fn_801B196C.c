typedef unsigned char u8;
typedef unsigned int u32;

extern u8 __DTKVolumeL;
extern u8 __DTKVolumeR;
extern u32 __DTKState;
extern void AISetStreamVolLeft(u32);
extern void AISetStreamVolRight(u32);

void DTKSetVolume(u32 first, u32 second)
{
    __DTKVolumeL = (u8)first;
    __DTKVolumeR = (u8)second;
    if (__DTKState == 1) {
        AISetStreamVolLeft(first);
        AISetStreamVolRight(second);
    }
}
