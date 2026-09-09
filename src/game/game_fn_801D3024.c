extern void* fn_80156938(void);
extern void* fn_80201BC8(void);
extern unsigned int fn_8011FAEC(void*);
extern void fn_8011FA8C(void*, int, int);
extern void fn_8012D0D0(void*);
extern void fn_80124DBC(void*);

int fn_801D3024(void)
{
    void* object;

    fn_80156938();
    object = fn_80201BC8();
    if (object != 0) {
        if (!(fn_8011FAEC(object) & 4)) {
            fn_8011FA8C(object, 0, 4);
        }
        fn_8012D0D0(object);
        fn_80124DBC(object);
    }
    return 3;
}
