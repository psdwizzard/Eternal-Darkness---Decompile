extern void *fn_80200C40(void);
extern void *fn_80200C4C(void *);

void fn_802007DC(void)
{
    void *node = fn_80200C40();

    while (node != 0) {
        node = fn_80200C4C(node);
    }
}
