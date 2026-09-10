extern int lbl_8064D184;
typedef struct Entry {
    short x0, y0, x1, y1;
    unsigned char pad8;
    unsigned char value;
    unsigned char pad10[2];
} Entry;
extern Entry *lbl_8064CDE4;
extern int lbl_8064CDE8;
extern int lbl_8064CE00;
extern int lbl_8064CDFC;
extern void fn_80144C40(void);

void fn_80119DB4(void)
{
    int index = lbl_8064D184;

    if (index >= 400 && index <= 411) {
        index -= 164;
    }
    if (index >= 0) {
        Entry *table = lbl_8064CDE4;
        lbl_8064CDE8 = table[index].value;
        lbl_8064CE00 = ((table[index].x0 + table[index].x1) >> 1) - 360;
        lbl_8064CDFC = ((table[index].y0 + table[index].y1) >> 1) - 240;
    }
    fn_80144C40();
}
