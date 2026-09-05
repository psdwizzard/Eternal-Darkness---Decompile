typedef struct Entry {
    void *object;
    int owner;
} Entry;

extern Entry **fn_801FD240(void *);
extern int fn_80201B54();
extern void **fn_80047D6C(void);
extern void fn_801FD534(void *);

void fn_800DAFCC(void *context)
{
    Entry **entries = fn_801FD240(context);
    int owner = fn_80201B54(context);
    void **active = fn_80047D6C();
    void *active_object = active != 0 ? *active : 0;
    int i;

    for (i = 0; i < 12; i++) {
        Entry *entry = entries[i];
        if (entry != 0 && entry->owner == owner && entry->object != active_object) {
            fn_801FD534(entry->object);
            break;
        }
    }
}
