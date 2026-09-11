typedef struct Entry80201890 {
    struct Entry80201890 *prev;
    struct Entry80201890 *next;
    int unk8;
    int unkC;
    int id;
    unsigned char unk14[0x20];
    void *value;
} Entry80201890;

typedef struct Manager80201890 {
    int unk0;
    Entry80201890 *head;
} Manager80201890;

extern Manager80201890 *fn_802014AC(void);
extern int fn_80201B44(void);
extern void *lbl_8064C4E4;

void *fn_80201890(int id)
{
    Entry80201890 *entry;
    Manager80201890 *manager = fn_802014AC();

    if (id == fn_80201B44()) {
        return lbl_8064C4E4;
    }

    if (id != 0) {
        for (entry = manager->head; entry != 0; entry = entry->next) {
            if (entry->id == id) {
                return entry->value;
            }
        }
    }

    return 0;
}
