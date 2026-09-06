extern unsigned int lbl_80331738[];
extern unsigned int lbl_8024E388[];

extern int fn_80201B44();
extern void *fn_80201814();
extern unsigned int fn_8020216C(void);
extern int fn_801E8D34(unsigned int);
extern int fn_801E7B24(unsigned int*, int, int);
extern int fn_801E79FC(void*, int);

int fn_8010F8B0(int index)
{
    int value;

    fn_80201B44();
    fn_80201814();
    if (fn_8020216C() & 0x80000) {
        return 1;
    }

    value = fn_801E7B24(lbl_8024E388, 3, fn_801E8D34(lbl_80331738[2]));
    return fn_801E79FC((void *)lbl_8024E388[index], value);
}
