extern void *fn_80155DB4(void *);
extern void fn_800DAFCC(void *);
extern void fn_800DB874(void *);
extern void fn_800DB660(void *, void *);
extern void fn_800DBF44(void);
extern void fn_800DB4F4(void *, void *);
extern void fn_800DB150(void *);

int fn_800DCFE0(void *object, void *mode)
{
    register unsigned long object_r = (unsigned long)object;
    void *saved_mode;
    void *saved_object;

    fn_80155DB4((void *)object_r);
    saved_object = (void *)object_r;
    saved_mode = mode;
    fn_800DAFCC(saved_object);
    fn_800DB874(saved_object);
    fn_800DB660(saved_object, saved_mode);
    fn_800DBF44();
    fn_800DB4F4(saved_object, saved_mode);
    fn_800DB150(saved_object);
    return 1;
}
