typedef unsigned char u8;

extern char lbl_8064D32D;
extern char lbl_8064D32C;
extern void* lbl_8064D330;
extern void fn_8021A468(int);
extern void fn_8021A494(int);
extern void fn_8021A184(void);
extern void fn_8021A19C(void*);
extern void fn_8021A1A8(int);

#pragma optimization_level 1
void fn_801B1028(void)
{
    fn_8021A468((u8)lbl_8064D32D);
    fn_8021A494((u8)lbl_8064D32C);
    fn_8021A184();
    fn_8021A19C(lbl_8064D330);
    fn_8021A1A8(1);
}
#pragma optimization_level reset
