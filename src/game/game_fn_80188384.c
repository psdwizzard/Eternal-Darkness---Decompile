typedef unsigned short u16;
typedef unsigned char u8;

extern u8 lbl_80606780[];
extern u8 lbl_80606AE0[];
extern void* lbl_8064D24C;
extern void* lbl_8064D250;

extern void fn_801ECC4C(void);
extern void fn_8022B2AC(void*, u16);
extern void fn_80226AB4(int, int, u16);
extern void fn_80188578(u16);
extern void fn_8018856C(u16);
extern void fn_80188560(u16);
extern void fn_8018855C(void);
extern void* fn_8022B374(void);

void fn_80188384(u8* input)
{
    int count2;
    int i2;
    u16 count;
    int i;

    fn_801ECC4C();
    count = *(u16*)(input + 2);
    fn_8022B2AC(lbl_80606780, *(u16*)(input + 6));
    fn_80226AB4(0x80, 5, count);
    for (i = 0; (u16)i < count; i++) {
        u16 index = i;
        fn_80188578(index);
        fn_8018856C(index);
        fn_80188560(index);
    }
    fn_8018855C();
    lbl_8064D250 = fn_8022B374();

    fn_801ECC4C();
    count2 = *(u16*)(input + 2);
    fn_8022B2AC(lbl_80606AE0, *(u16*)(input + 8));
    fn_80226AB4(0x80, 5, (u16)(((count2 - 4) * 2) + 4));
    fn_80188578(1);
    fn_8018856C(1);
    fn_80188560(1);
    fn_80188578(0);
    fn_8018856C(0);
    fn_80188560(0);
    count2 -= 2;
    for (i2 = 2; (u16)i2 < count2; i2 += 2) {
        u16 index = i2;
        u16 next = i2 + 1;
        fn_80188578(index);
        fn_8018856C(index);
        fn_80188560(index);
        fn_80188578(next);
        fn_8018856C(next);
        fn_80188560(next);
        fn_80188578(next);
        fn_8018856C(next);
        fn_80188560(next);
        fn_80188578(index);
        fn_8018856C(index);
        fn_80188560(index);
    }
    {
        u16 index = i2;
        fn_80188578(index);
        fn_8018856C(index);
        fn_80188560(index);
        index = i2 + 1;
        fn_80188578(index);
        fn_8018856C(index);
        fn_80188560(index);
    }
    fn_8018855C();
    lbl_8064D24C = fn_8022B374();
}
