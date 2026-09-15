typedef unsigned char u8;
typedef unsigned short u16;

extern u8 lbl_80607120[];

void fn_8019753C(u8* destination, const u8* first, const u8* second,
                 u16 dimensions)
{
    u8 split = (dimensions >> 1) & 0x7f;
    u8* second_row = destination + *(u16*)(lbl_80607120 + 2) * 4;
    int width = dimensions & 0xff;
    int row = 0;

    for (; row < 2; row++) {
        int x;
        for (x = 0; x < split; x++) {
            destination[0] = first[0];
            destination[1] = first[1];
            destination[2] = first[2];
            destination[3] = first[3];
            destination[4] = first[0];
            destination[5] = first[1];
            destination[6] = first[2];
            destination[7] = first[3];
            destination += 8;
        }
        x = split;
        for (; x < width; x++) {
            destination[0] = first[0];
            destination[1] = first[1];
            destination[2] = first[2];
            destination[3] = first[3];
            destination[4] = second[0];
            destination[5] = second[1];
            destination[6] = second[2];
            destination[7] = second[3];
            destination += 8;
        }
        destination = second_row;
    }
}
