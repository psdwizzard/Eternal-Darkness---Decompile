extern void fn_80155D9C(int);
extern void *fn_80155D78(void);
extern int fn_80117EC8(void *, void *);
extern void fn_80157360(int (*)(void *, void *), void *, int, int);

void fn_80117EF0(void)
{
    int (*callback)(void *, void *);

    fn_80155D9C(1);
    callback = fn_80117EC8;
    fn_80157360(callback, fn_80155D78(), 0, 4);
}
