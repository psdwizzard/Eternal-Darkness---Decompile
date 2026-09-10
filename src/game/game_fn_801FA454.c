typedef unsigned short u16;

extern int lbl_8064C3A0;
extern int lbl_8064D798;
extern unsigned char lbl_8063D504[];

extern void fn_801FABA4(void*, int);
extern void fn_801FAD4C(void*);

void fn_801FA454(u16 state, int token)
{
    if (state == 1) {
        if (lbl_8064C3A0 == 2 && lbl_8064D798 == 0) {
            lbl_8064D798 = token;
            lbl_8064C3A0 = 1;
            fn_801FABA4(lbl_8063D504, 0);
        }
    } else if (state == 2) {
        if (lbl_8064C3A0 == 1 && lbl_8064D798 == token) {
            fn_801FAD4C(lbl_8063D504);
            lbl_8064C3A0 = 2;
            lbl_8064D798 = 0;
        }
    }
}
