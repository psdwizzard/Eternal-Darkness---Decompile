typedef unsigned char u8;
typedef unsigned int u32;

extern u8 lbl_8023B348[];
extern u8 lbl_8023B3D0[];
extern u8 lbl_8062A2F0[];
extern u8 lbl_8062E5F0[];
extern void* memcpy(void*, const void*, u32);
extern void fn_801CB470(u8, u8, u8);

void fn_801CAEB8(u8 channel, u8 set, u32 cold_reset)
{
    u8* source = cold_reset != 0 ? lbl_8023B348 : lbl_8023B3D0;
    u8* destination;

    if (set != 0xFF) {
        destination = lbl_8062A2F0 + set * 2144 + channel * 134;
    } else {
        destination = lbl_8062E5F0 + channel * 134;
    }

    if (cold_reset != 0) {
        memcpy(destination, source, 134);
    } else {
        u32 i;
        for (i = 0; i < 134; i++) {
            if (source[i] != 0xFF) {
                destination[i] = source[i];
            }
        }
    }

    fn_801CB470(channel, set, 0xFF);
}
