typedef unsigned char u8;
typedef unsigned int u32;

extern u32 lbl_80619860[][16];

#pragma optimization_level 1
void fn_801B5B20(u32 value, u8 owner, u8 channel)
{
    u32 result;
    u32 scaled;

    if (owner == 0xFF) {
        owner = 8;
    }
    scaled = value << 3;
    scaled *= 0x600;
    result = scaled / 0xF0;
    lbl_80619860[owner][channel] = result;
}
#pragma optimization_level reset
