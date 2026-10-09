extern void fn_801EC9A8(void);
extern void fn_80121114(void *, int, int, int, int, int);

void fn_8010E3DC(void *object)
{
    fn_801EC9A8();
    if (object != 0) {
        fn_80121114(object, 0, 30000, 0, 0, 1);
        fn_80121114(object, 0, 30000, 1, 0, 1);
    }
}
