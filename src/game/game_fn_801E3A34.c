typedef unsigned char u8;
typedef unsigned int u32;

typedef union Color {
    u32 value;
    struct {
        u8 r;
        u8 g;
        u8 b;
        u8 a;
    } channel;
} Color;

extern Color lbl_8064D594;

u32 fn_801E3A34(Color* color)
{
    Color old = lbl_8064D594;
    lbl_8064D594 = *color;
    lbl_8064D594.channel.r = lbl_8064D594.channel.r <= 230
                                      ? lbl_8064D594.channel.r
                                      : 230;
    lbl_8064D594.channel.g = lbl_8064D594.channel.g <= 230
                                      ? lbl_8064D594.channel.g
                                      : 230;
    lbl_8064D594.channel.b = lbl_8064D594.channel.b <= 230
                                      ? lbl_8064D594.channel.b
                                      : 230;
    return old.value;
}
