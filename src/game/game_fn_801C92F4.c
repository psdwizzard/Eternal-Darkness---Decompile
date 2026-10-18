typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 sndActive;
extern int AddEmitter(void*, void*, void*, u32, u16, u32, u32, u32,
                       void*, void*, u8);

int sndAddEmitter(void* object, void* position, void* velocity, u32 flags,
                u16 sound_id, u32 first, u32 second, void* owner)
{
    if (sndActive != 0) {
        return AddEmitter(object, position, velocity, flags, sound_id,
                           (sound_id & 0xFFFF) | 0x80000000, first, second,
                           owner, 0, 0);
    }
    return -1;
}
