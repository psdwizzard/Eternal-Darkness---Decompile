typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void fn_801CA7C0(u8, u8, u8, u8);

void fn_801CAD90(u8 control, u8 channel, u8 set, u16 value)
{
    if (channel != 0xFF) {
        if (control < 0x40) {
            fn_801CA7C0(control & 0x1F, channel, set, (value >> 7) & 0xFF);
            fn_801CA7C0((control & 0x1F) + 0x20, channel, set, value & 0x7F);
        } else if (control == 0x80 || control == 0x81) {
            fn_801CA7C0(control & 0xFE, channel, set, (value >> 7) & 0xFF);
            fn_801CA7C0((control & 0xFE) + 1, channel, set, value & 0x7F);
        } else if (control == 0x84 || control == 0x85) {
            fn_801CA7C0(control & 0xFE, channel, set, (value >> 7) & 0xFF);
            fn_801CA7C0((control & 0xFE) + 1, channel, set, value & 0x7F);
        } else {
            fn_801CA7C0(control, channel, set, (value >> 7) & 0xFF);
        }
    }
}
