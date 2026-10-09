extern void *lbl_8064C4E0;

extern int fn_801E79FC(void *object, int value);
extern void fn_801E79A0(void *object, int value);
extern void fn_80047D14(void **first, void **second);
extern void fn_80153140(void *object, int alternate);
extern void fn_80154EC0(void *effect, int value);

void fn_80047FFC(int enabled)
{
    void *first;
    void *second;

    if (fn_801E79FC(lbl_8064C4E0, 0x467) != 0) {
        fn_80047D14(&first, &second);
        fn_80153140(first, enabled);
        fn_80154EC0(second, enabled);
        fn_801E79A0(lbl_8064C4E0, 0x467);
    }
}
