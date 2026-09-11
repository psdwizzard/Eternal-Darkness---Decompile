typedef unsigned char u8;
typedef unsigned short u16;

void fn_8017FA14(u8* destination, const u8* first, const u8* second,
                 u8 count, int repetitions, unsigned int row_length)
{
    u8* second_row;
    int i;
    int j;
    int row;
    int pair;

    row_length = (u16)row_length * 4;
    count /= 2;
    second_row = destination + row_length;
    for (row = 0; row < 2; row++) {
        for (pair = 0; pair < count; pair++) {
            for (i = 0; i < repetitions; i++) {
                destination[0] = first[0];
                destination[1] = first[1];
                destination[2] = first[2];
                destination[3] = first[3];
                destination += 4;
            }
            for (j = 0; j < repetitions; j++) {
                destination[0] = second[0];
                destination[1] = second[1];
                destination[2] = second[2];
                destination[3] = second[3];
                destination += 4;
            }
        }
        destination = second_row;
    }
}
