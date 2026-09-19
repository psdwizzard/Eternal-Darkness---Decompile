typedef struct Record {
    unsigned char pad[0x8F];
    signed char active;
    unsigned char tail[8];
} Record;

extern Record lbl_806080E0[];
extern void fn_801AA9FC(int);

Record* fn_801AAC10(void)
{
    Record* record;
    int i;

    record = lbl_806080E0;
    for (i = 0; i < 80; i++, record++) {
        if (record->active == 0) {
            return record;
        }
    }
    fn_801AA9FC(1);
    return 0;
}
