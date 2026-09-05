typedef struct Entry {
    unsigned char prefix[80];
    void* handle;
    unsigned char remainder[48];
} Entry;

extern Entry lbl_8060B430;
extern int lbl_8064D308;
extern void fn_801BAF90(void*);

void fn_801ADCF8(void)
{
    Entry* entry;
    unsigned int index;

    if (lbl_8064D308 == 1) {
        index = 0;
        do {
            entry = &lbl_8060B430 + index;
            fn_801BAF90(entry->handle);
            index++;
        } while (index < 3);
        lbl_8064D308 = 0;
    }
}
