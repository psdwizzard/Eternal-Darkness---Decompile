typedef unsigned char u8;
typedef unsigned short u16;

typedef struct ColorChannel {
    u8 value;
} ColorChannel;
typedef struct ColorPair {
    ColorChannel channels[8];
} ColorPair;

extern u8 lbl_80607120[];

void fn_8018FFBC(u8* destination, const u8* first, const u8* second, u8 count)
{
    u16 color_buffer_offset = *(u16*)(lbl_80607120 + 2);
    u8* other = destination + color_buffer_offset * 4;
    int buffer;
    const ColorChannel* first_color = (const ColorChannel*)first;
    const ColorChannel* second_color = (const ColorChannel*)second;
    ColorPair* pair = (ColorPair*)destination;

    for (buffer = 0; buffer < 2; buffer++) {
        int i;
        for (i = 0; i < count; i++) {
            pair->channels[0] = first_color[0];
            pair->channels[1] = first_color[1];
            pair->channels[2] = first_color[2];
            pair->channels[3] = first_color[3];
            pair->channels[4] = second_color[0];
            pair->channels[5] = second_color[1];
            pair->channels[6] = second_color[2];
            pair->channels[7] = second_color[3];
            pair++;
        }
        pair = (ColorPair*)other;
    }
}
