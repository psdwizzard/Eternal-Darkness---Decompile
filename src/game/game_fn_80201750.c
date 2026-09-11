typedef struct Entry80201750 {
    struct Entry80201750 *prev;
    struct Entry80201750 *next;
    int unk8;
    int unkC;
    int unk10;
    int unk14;
    int unk18;
    int flags;
    unsigned char unk20;
    unsigned char pad21[3];
    void *unk24;
    int unk28;
    void *unk2C;
    int unk30;
    void *unk34;
    int unk38;
} Entry80201750;

extern char lbl_802FC954[];
extern void *lbl_8064D874;
extern void *lbl_8064D880;

extern void fn_800EB504(const char *, ...);
extern void fn_8017CE74(void *, void *);
extern void fn_8011FD64(void *);
extern void fn_801577E0(void *);
extern void *memset(void *, int, unsigned long);

void fn_80201750(Entry80201750 *entry)
{
    if (entry != 0) {
        fn_800EB504(lbl_802FC954);
        if (entry->unk24 != 0) {
            fn_8017CE74(lbl_8064D874, entry->unk24);
            entry->unk24 = 0;
        }
        if (entry->unk34 != 0) {
            fn_8011FD64(entry->unk34);
            entry->unk34 = 0;
        }
        if (entry->unk2C != 0) {
            fn_801577E0(entry->unk2C);
            entry->unk2C = 0;
        }
        entry->prev->next = entry->next;
        if (entry->next != 0) {
            entry->next->prev = entry->prev;
        }
        memset(entry, 0, sizeof(*entry));
        fn_8017CE74(lbl_8064D880, entry);
    }
}
