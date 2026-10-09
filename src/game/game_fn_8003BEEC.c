extern void *fn_80201BC8();
extern int fn_8012A100(void *, int);
extern int fn_8012A1BC(void *, int);
extern void *fn_801294DC(void *, int, int, int);
extern void fn_80128A84(void *, int, int);

void fn_8003BEEC(void)
{
    void *object;
    int slot;

    object = fn_80201BC8();
    if (fn_8012A100(object, 0x18) != 0) {
        slot = fn_8012A1BC(object, 0x18);
        fn_80128A84(fn_801294DC(object, 0x18, 0x30, 0xA), 0, slot);
    }
}
