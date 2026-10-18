typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

extern u8* synthVoice;
extern u32 vidGetInternalId(u32);
extern void inpSetMidiCtrl14(u8, u8, u8, u16);

u32 synthFXSetCtrl14(u32 handle, u8 control, u16 value)
{
    u32 result = 0;
    u32 voice = vidGetInternalId(handle);

    while (voice != 0xFFFFFFFF) {
        u32 index = voice & 0xFF;
        u32 offset = index * 0x404;

        if (voice == *(u32*)(synthVoice + offset + 0xF4)) {
            u8* state = synthVoice + offset;

            if ((*(u64*)(state + 0x114) & 2) != 0) {
                inpSetMidiCtrl14(control, index, state[0x20B], value);
            } else {
                inpSetMidiCtrl14(control, index, state[0x122], value);
            }

            result = 1;
            voice = *(u32*)(synthVoice + offset + 0xEC);
        } else {
            return result;
        }
    }
    return result;
}
