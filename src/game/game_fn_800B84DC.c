typedef signed short s16;

extern void *lbl_80320B48[3];
extern int lbl_8064CDC8;
extern int lbl_8064C2C4;
extern float lbl_8064F070;
extern float lbl_8064F01C;
extern int fn_800B8F38(void);
extern int fn_8017BB60(void);
extern int fn_80220234(int, int *, int *);
extern int fn_800B194C(void);
extern int fn_801E6350(void *);
extern int fn_801E6380(void *);
extern int fn_801E63F0(void *);
extern int fn_801E6420(void *);
extern void fn_801A8974(int, s16, s16, s16, int, int);
extern void fn_801A872C(int, s16, s16, s16, int, int, int*);
extern void fn_801ED5F4(int, int, int, int, int, float);

void fn_800B84DC(void)
{
    s16 third;
    s16 fourth;
    int first;
    s16 second;
    int index;
    int output1;
    int output2;

    index = fn_800B8F38();
    if (fn_8017BB60() == 0) {
        fn_80220234(0, &output1, &output2);
        fn_80220234(1, &output1, &output2);
    }
    if (fn_800B194C() == 12) {
        if (index == 0) {
            second = 334;
            third = 227;
            fourth = 44;
            first = 207;
        } else {
            second = 378;
            third = 272;
            fourth = 48;
            first = 184;
        }
    } else {
        first = fn_801E6350(lbl_80320B48[index]);
        second = fn_801E6380(lbl_80320B48[index]) + 8;
        third = fn_801E63F0(lbl_80320B48[index]) + 7;
        fourth = fn_801E6420(lbl_80320B48[index]) - 6;
    }
    if (lbl_8064CDC8 == 3) {
        fn_801A8974(first, second, third, fourth, -1, 3);
    } else {
        int value;
        fn_801ED5F4(1, 0x482, 1, 0, 0, lbl_8064F070);
        value = lbl_8064C2C4;
        fn_801A872C(first, second, third, fourth, -1, 3, &value);
        fn_801ED5F4(0, 2, 1, 0, 0, lbl_8064F01C);
    }
}
