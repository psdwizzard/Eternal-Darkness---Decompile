extern void* lbl_8064C4E4;
extern void fn_801FA4F0(int, int);
extern void fn_801F6ED0(void*, void*);
extern void fn_8013B83C(int);
extern int fn_801261F4(void*);
extern void fn_8011F7E0(void*, int);

void fn_800A5330(int object)
{
    fn_801FA4F0(2, 1);
    fn_801F6ED0(lbl_8064C4E4, (void*)object);
    lbl_8064C4E4 = (void*)object;
    fn_8013B83C(object);
    fn_801261F4(lbl_8064C4E4);
    fn_8011F7E0(lbl_8064C4E4, 0);
}
