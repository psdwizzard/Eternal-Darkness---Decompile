typedef unsigned int u32;
extern u32 lbl_8064EEE0, lbl_8064EEE4, lbl_8064EEE8, lbl_8064EEEC, lbl_8064EEF0;
extern u32 lbl_80651A2C, lbl_80651A30, lbl_80651A34;
extern u32 lbl_802396F0[];
extern void fn_8012C62C(void *, int, u32 *, u32 *, u32 *, int);
extern void fn_8012CBE8(void *, int, u32 *, u32 *, u32 *, int, u32, u32);
extern void fn_8012C478(void *, int, int);
void fn_800A4AC4(void *object, int selector, int mode, int alternate)
{
    u32 v[13];
    u32 a, b, c;
    v[0]=lbl_8064EEE0; v[1]=lbl_80651A2C;
    v[2]=lbl_802396F0[3]; v[3]=lbl_802396F0[4]; v[4]=lbl_802396F0[5];
    v[5]=lbl_802396F0[6]; v[6]=lbl_802396F0[7]; v[7]=lbl_802396F0[8];
    v[8]=lbl_802396F0[9]; v[9]=lbl_802396F0[10]; v[10]=lbl_802396F0[11];
    v[11]=lbl_802396F0[12]; v[12]=lbl_802396F0[14];
    if (mode == 2) {
        if (alternate == 0) {
            v[2]=lbl_802396F0[9]; v[3]=lbl_802396F0[10]; v[4]=lbl_802396F0[11];
            v[5]=lbl_802396F0[12]; v[6]=lbl_802396F0[13]; v[7]=lbl_802396F0[14];
            v[8]=lbl_802396F0[12]; v[9]=lbl_802396F0[13]; v[10]=lbl_802396F0[14];
        }
        a=v[8]; b=v[9]; c=v[10];
        fn_8012CBE8(object, selector, &v[2], &v[5], &v[8], 0, v[3], v[2]);
    } else if (mode == 1) {
        a=lbl_8064EEE0; b=lbl_80651A2C; c=lbl_8064EEE0;
        fn_8012C62C(object, selector, &c, &b, &a, 2);
    } else if (mode == 3) {
        fn_8012C478(object, 0, 0);
    } else if (alternate == 0) {
        a=lbl_8064EEE8; b=lbl_80651A30; c=lbl_8064EEE4;
        fn_8012C62C(object, selector, &c, &b, &a, 4);
    } else {
        a=lbl_80651A34; b=lbl_8064EEF0; c=lbl_8064EEEC;
        fn_8012C62C(object, selector, &c, &b, &a, 4);
    }
}
