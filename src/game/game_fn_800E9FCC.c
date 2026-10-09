typedef struct Entry {
    int unused;
    int handle;
    int unused8;
    int context;
} Entry;

extern Entry *lbl_80325F1C[6];
extern int fn_800EA27C(int *);
extern void fn_800EA4D0(void *, int);
extern unsigned long long fn_8020123C(int, int, int, int);

void fn_800E9FCC(void)
{
    int index;
    Entry *entry;

    if (fn_800EA27C(&index) == 0) {
        entry = lbl_80325F1C[index];
        if (entry->context != 0) {
            fn_800EA4D0((void *)entry->context, entry->handle);
        } else {
            fn_8020123C(0x39, entry->handle, entry->handle, 0);
        }
    }
}
