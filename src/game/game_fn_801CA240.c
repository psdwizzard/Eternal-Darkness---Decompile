typedef unsigned char u8;
typedef unsigned int u32;

extern void* s3dEmitterRoot;
extern void* s3dListenerRoot;
extern void* s3dRoomRoot;
extern void* s3dDoorRoot;
extern void* snd_used_studios;
extern u8 snd_base_studio;
extern u8 snd_max_studios;
extern u8 s3dCallCnt;
extern u8 s3dUseMaxVoices;

void s3dInit(u32 flags)
{
    s3dEmitterRoot = 0;
    s3dListenerRoot = 0;
    s3dRoomRoot = 0;
    s3dDoorRoot = 0;
    snd_used_studios = 0;
    snd_base_studio = 1;
    snd_max_studios = 3;
    s3dCallCnt = 0;
    s3dUseMaxVoices = (flags & 2) != 0;
}
