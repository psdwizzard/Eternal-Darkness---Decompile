typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 lbl_8023B078[4];
extern u16 lbl_80607120[];
extern u32 fn_800FBFB0(void);

void fn_8018CEC0(u32* dest, u8 count)
{
    u32 values[4];
    int i;
    u32* first;
    u32* second;

    values[0] = lbl_8023B078[0];
    values[1] = lbl_8023B078[1];
    values[2] = lbl_8023B078[2];
    values[3] = lbl_8023B078[3];
    second = dest + lbl_80607120[1];
    first = dest;
    for (i = 0; i < count; i++) {
        u32 random = fn_800FBFB0() & 3;
        first[0] = values[random];
        second[0] = first[0];
        random = (random + 1) & 3;
        first[1] = values[random];
        second[1] = first[1];
        random = (random + 1) & 3;
        first[2] = values[random];
        second[2] = first[2];
        random = (random + 1) & 3;
        first[3] = values[random];
        second[3] = first[3];
        first += 4;
        second += 4;
    }
}
