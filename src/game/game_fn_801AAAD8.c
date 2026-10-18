extern unsigned char lbl_80608020[];
extern unsigned char lbl_806080E0[];

extern void fn_801AB048(void*);
extern void sndRemoveListener(void*);

void fn_801AAAD8(void)
{
    unsigned char* record;
    int i;

    record = lbl_806080E0;
    i = 0;
    do {
        fn_801AB048(record);
        i++;
        record += 0x98;
        if (i >= 80) {
            break;
        }
    } while (1);
    sndRemoveListener(lbl_80608020);
}
