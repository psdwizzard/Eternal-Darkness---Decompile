extern void *memset(void *, int, unsigned int);
typedef struct Entry {
    unsigned char data[32];
} Entry;
extern Entry lbl_80325C40[];

void fn_800E475C(void)
{
    Entry *entry;
    int i;

    for (i = 0; i < 5; i++) {
        entry = &lbl_80325C40[i];
        memset(entry, 0, 32);
    }
}
