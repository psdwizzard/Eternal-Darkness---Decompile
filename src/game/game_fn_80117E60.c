extern void *memset(void *, int, unsigned long);

extern unsigned int lbl_80332140[];
extern unsigned int lbl_8064CDAC;
extern unsigned int lbl_8064CDA8;
extern unsigned int lbl_8064CDA4;
extern unsigned int lbl_8064CDA0;
extern unsigned int lbl_8064CD7C;
extern unsigned int lbl_8064CD80;
extern unsigned int lbl_8064CDE0;
extern unsigned int lbl_8064CD00;
extern unsigned int lbl_8064B994;
extern unsigned int lbl_8064CE44;
extern int lbl_8064CDC8;

void fn_80117E60(void)
{
    memset(lbl_80332140, 0, 0x18);
    lbl_8064CDAC = 0;
    lbl_8064CDA8 = 0;
    lbl_8064CDA4 = 0;
    lbl_8064CDA0 = 0;
    lbl_8064CD7C = 0;
    lbl_8064CD80 = 0;
    lbl_8064CDE0 = 0;
    lbl_8064CD00 = 0;
    lbl_8064B994 = 1;
    lbl_8064CE44 = 0;
    lbl_8064CDC8 = -1;
}
