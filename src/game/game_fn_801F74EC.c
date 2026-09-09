extern int lbl_8064D7B8;
extern int lbl_8064D7B4;
extern int lbl_8064D7B0;
extern unsigned char lbl_8063D400[];

void fn_801F76EC(void);

void fn_801F74EC(int first, int second, int third)
{
    lbl_8064D7B8 = first;
    lbl_8064D7B4 = second;
    lbl_8064D7B0 = third;
    *(void (**)(void))(lbl_8063D400 + 0x6C) = fn_801F76EC;
}
