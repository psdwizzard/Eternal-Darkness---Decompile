typedef struct Entry802016CC {
    struct Entry802016CC *prev;
    struct Entry802016CC *next;
    int unk8;
    int unkC;
    int unk10;
    int unk14;
    int unk18;
    int flags;
    unsigned char unk20;
    unsigned char pad21[0x17];
    int unk38;
} Entry802016CC;

extern void *lbl_8064D880;

extern void *fn_8017CDB4(void *);
extern Entry802016CC *fn_802014AC(void);
extern int fn_80201624(void);
extern void fn_802014C8(Entry802016CC *, int);

Entry802016CC *fn_802016CC(void)
{
    Entry802016CC *entry = fn_8017CDB4(lbl_8064D880);

    if (entry != 0) {
        Entry802016CC *head = fn_802014AC();
        Entry802016CC *next;

        fn_802014C8(entry, fn_80201624());
        entry->unk38 = -1;
        next = head->next;
        entry->prev = head;
        entry->next = next;
        head->next = entry;
        if (next != 0) {
            next->prev = entry;
        }
        return entry;
    }
    return 0;
}
