typedef unsigned char u8;

extern volatile u8 lbl_8064C368;

extern void PERFEventStart(int);

void fn_80024434(void)
{
    lbl_8064C368;
    if (lbl_8064C368 == 0) {
        PERFEventStart(0);
    }
}
